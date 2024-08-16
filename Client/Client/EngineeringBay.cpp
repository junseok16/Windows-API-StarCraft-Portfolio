#include "pch.h"
#include "EngineeringBay.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "PropertyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

#include "RectangleColliderComponent.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Command.h"
#include "Scene.h"
#include "Unit.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
using namespace std;

CEngineeringBay::CEngineeringBay(CBuildingProperty& _buildingProperty)
    : CBuilding(_buildingProperty) { }

void CEngineeringBay::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 엔지니어링 베이에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 98, 64 });

	pRectCollider->SetCollisionType(ECollisionType::BUILDING);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
	pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);

	/********************
		AnimationObject 클래스
	********************/
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"EngnrByCnstrctn");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"EngnrByLand");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"EngnrByUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"EngnrByBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_INFANTRY_WEAPONS);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_INFANTRY_ARMOR);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_G].push_back(ECommandType::CANCEL_UPGRADE);


	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct8"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(64.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);


	/********************
		Building 클래스
	********************/
	SetCurHP(m_buildingProperty.GetMaxHP());
	SetCurMP(m_buildingProperty.GetMaxMP());
	SetCurShield(m_buildingProperty.GetMaxShield());
	SetTerranBuildingType(ETerranBuildingType::ENGINEERING_BAY);

	/********************
		EngineeringBay 클래스
	********************/
	SetEngineeringBayState(EEngineeringBayState::CONSTRUCTION);
	SetAnimation(m_pCnstrctnAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pInfWeaponProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_1);
	m_pInfWeaponProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_2);
	m_pInfWeaponProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_3);
	m_pInfArmorProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_1);
	m_pInfArmorProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_2);
	m_pInfArmorProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_3);
}

void CEngineeringBay::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CEngineeringBay::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CEngineeringBay::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CEngineeringBay::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CEngineeringBay::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CEngineeringBay::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CEngineeringBay::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CEngineeringBay::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetEngineeringBayState(EEngineeringBayState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::UPGRADE_INFANTRY_WEAPONS:
	{
		if (m_queUpgrades.size() >= 1) { break; }

		if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_1) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfWeaponProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfWeaponProperty[0]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_WEAPONS_1);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_2) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfWeaponProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfWeaponProperty[1]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_WEAPONS_2);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_3) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfWeaponProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfWeaponProperty[2]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_WEAPONS_3);
		}
	}
	break;

	case ECommandType::UPGRADE_INFANTRY_ARMOR:
	{
		if (m_queUpgrades.size() >= 1) { break; }

		if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_1) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfArmorProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfArmorProperty[0]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_ARMOR_1);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_2) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfArmorProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfArmorProperty[1]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_ARMOR_2);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_3) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pInfArmorProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pInfArmorProperty[2]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::INFANTRY_ARMOR_3);
		}
	}
	break;

	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }

		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::INFANTRY_WEAPONS_1:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfWeaponProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfWeaponProperty[0]->GetGas());
		}
		break;

		case ETerranUpgradeType::INFANTRY_WEAPONS_2:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfWeaponProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfWeaponProperty[1]->GetGas());
		}
		break;

		case ETerranUpgradeType::INFANTRY_WEAPONS_3:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfWeaponProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfWeaponProperty[2]->GetGas());
		}
		break;

		case ETerranUpgradeType::INFANTRY_ARMOR_1:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfArmorProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfArmorProperty[0]->GetGas());
		}
		break;

		case ETerranUpgradeType::INFANTRY_ARMOR_2:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfArmorProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfArmorProperty[1]->GetGas());
		}
		break;

		case ETerranUpgradeType::INFANTRY_ARMOR_3:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pInfArmorProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pInfArmorProperty[2]->GetGas());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetEngineeringBayState(EEngineeringBayState::LAND);
		}
	}
	break;

	default:
		break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CEngineeringBay::ExecuteCommand()
{
	switch (m_eEngineeringBayState)
	{
	case EEngineeringBayState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::ENGINEERING_BAY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetEngineeringBayState(EEngineeringBayState::LAND);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EEngineeringBayState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EEngineeringBayState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case EEngineeringBayState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CEngineeringBay::Upgrade()
{
	if (GetDead() == true)
	{
		SetEngineeringBayState(EEngineeringBayState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetEngineeringBayState(EEngineeringBayState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::INFANTRY_WEAPONS_1:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pInfWeaponProperty[0]->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_1, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			UpgradeInfantyWeapon();

			SetEngineeringBayState(EEngineeringBayState::LAND);
			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;

	case ETerranUpgradeType::INFANTRY_ARMOR_1:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pInfArmorProperty[0]->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_1, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			UpgradeInfantyArmor();

			SetEngineeringBayState(EEngineeringBayState::LAND);
			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;
	}
}

void CEngineeringBay::UpgradeInfantyWeapon()
{
	CUnitProperty* pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
	pMarineProperty->SetAttackPoint(pMarineProperty->GetAttackPoint() + 1);

	CUnitProperty* pFirebatProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
	pFirebatProperty->SetAttackPoint(pFirebatProperty->GetAttackPoint() + 2);

	CUnitProperty* pGhostProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GHOST);
	pGhostProperty->SetAttackPoint(pGhostProperty->GetAttackPoint() + 1);
}

void CEngineeringBay::UpgradeInfantyArmor()
{
	CUnitProperty* pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
	pMarineProperty->SetDefensePoint(pMarineProperty->GetDefensePoint() + 1);

	CUnitProperty* pFirebatProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
	pFirebatProperty->SetDefensePoint(pFirebatProperty->GetDefensePoint() + 1);

	CUnitProperty* pGhostProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GHOST);
	pGhostProperty->SetDefensePoint(pGhostProperty->GetDefensePoint() + 1);
}
