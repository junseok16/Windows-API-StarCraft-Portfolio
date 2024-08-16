#include "pch.h"
#include "Armory.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "PropertyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

#include "RectangleColliderComponent.h"
#include "Command.h"
#include "Scene.h"
#include "Unit.h"

#include "UnitProperty.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
using namespace std;

CArmory::CArmory(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CArmory::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 아머리에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 64, 48 });

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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"ArmryCnstrctn");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"ArmryIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"ArmryUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"ArmryBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_VIHICLE_WEAPONS);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_VIHICLE_PLATING);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_G].push_back(ECommandType::CANCEL_UPGRADE);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct6"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(48.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	/********************
		Building 클래스
	********************/
	SetCurHP(m_buildingProperty.GetMaxHP());
	SetCurMP(m_buildingProperty.GetMaxMP());
	SetCurShield(m_buildingProperty.GetMaxShield());
	SetTerranBuildingType(ETerranBuildingType::ARMORY);

	/********************
		Academy 클래스
	********************/
	SetArmoryState(EArmoryState::CONSTRUCTION);
	SetAnimation(m_pCnstrctnAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pVhclWeaponProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_1);
	m_pVhclWeaponProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_2);
	m_pVhclWeaponProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_3);

	m_pVhclPlatingProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_1);
	m_pVhclPlatingProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_2);
	m_pVhclPlatingProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_3);
}

void CArmory::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CArmory::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CArmory::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CArmory::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CArmory::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CArmory::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CArmory::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CArmory::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetArmoryState(EArmoryState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::UPGRADE_VIHICLE_WEAPONS:
	{
		if (m_queUpgrades.size() >= 1) { break; }

		if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_1) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclWeaponProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclWeaponProperty[0]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_WEAPONS_1);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_2) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclWeaponProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclWeaponProperty[1]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_WEAPONS_2);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_3) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclWeaponProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclWeaponProperty[2]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_WEAPONS_3);
		}
	}
	break;

	case ECommandType::UPGRADE_VIHICLE_PLATING:
	{
		if (m_queUpgrades.size() >= 1) { break; }

		if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_1) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclPlatingProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclPlatingProperty[0]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_PLATING_1);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_2) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclPlatingProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclPlatingProperty[1]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_PLATING_2);
		}
		else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_3) == false)
		{
			CGameManager::GetManager()->IncreaseProducedMineral(-m_pVhclPlatingProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pVhclPlatingProperty[2]->GetGas());
			m_queUpgrades.push_back(ETerranUpgradeType::VIHICLE_PLATING_3);
		}
	}
	break;

	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }

		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::VIHICLE_PLATING_1:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclPlatingProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclPlatingProperty[0]->GetGas());
		}
		break;

		case ETerranUpgradeType::VIHICLE_PLATING_2:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclPlatingProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclPlatingProperty[1]->GetGas());
		}
		break;

		case ETerranUpgradeType::VIHICLE_PLATING_3:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclPlatingProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclPlatingProperty[2]->GetGas());
		}
		break;

		case ETerranUpgradeType::VIHICLE_WEAPONS_1:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclWeaponProperty[0]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclWeaponProperty[0]->GetGas());
		}
		break;

		case ETerranUpgradeType::VIHICLE_WEAPONS_2:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclWeaponProperty[1]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclWeaponProperty[1]->GetGas());
		}
		break;

		case ETerranUpgradeType::VIHICLE_WEAPONS_3:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVhclWeaponProperty[2]->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVhclWeaponProperty[2]->GetGas());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetArmoryState(EArmoryState::IDLE);
		}
	}
	break;

	default:
		break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CArmory::ExecuteCommand()
{
	switch (m_eArmoryState)
	{
	case EArmoryState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::ARMORY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetArmoryState(EArmoryState::IDLE);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EArmoryState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EArmoryState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;


	case EArmoryState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CArmory::Upgrade()
{
	if (GetDead() == true)
	{
		SetArmoryState(EArmoryState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetArmoryState(EArmoryState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::VIHICLE_WEAPONS_1:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pVhclWeaponProperty[0]->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_1, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			UpgradeVihicleWeapon();

			SetArmoryState(EArmoryState::IDLE);
			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;

	case ETerranUpgradeType::VIHICLE_PLATING_1:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pVhclPlatingProperty[0]->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::VIHICLE_PLATING_1, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			UpgradeVihiclePlating();

			SetArmoryState(EArmoryState::IDLE);
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

void CArmory::UpgradeVihicleWeapon()
{
	CUnitProperty* pVultureProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
	pVultureProperty->SetAttackPoint(pVultureProperty->GetAttackPoint() + 1);

	CUnitProperty* pTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
	pTankProperty->SetAttackPoint(pTankProperty->GetAttackPoint() + 3);

	CUnitProperty* pSiegeTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
	pSiegeTankProperty->SetAttackPoint(pSiegeTankProperty->GetAttackPoint() + 3);

	CUnitProperty* pGoliathProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GOLIATH);
	pGoliathProperty->SetAttackPoint(pGoliathProperty->GetAttackPoint() + 1);
}

void CArmory::UpgradeVihiclePlating()
{
	CUnitProperty* pVultureProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
	pVultureProperty->SetDefensePoint(pVultureProperty->GetDefensePoint() + 1);

	CUnitProperty* pTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
	pTankProperty->SetDefensePoint(pTankProperty->GetDefensePoint() + 1);

	CUnitProperty* pSiegeTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
	pSiegeTankProperty->SetDefensePoint(pSiegeTankProperty->GetDefensePoint() + 1);

	CUnitProperty* pGoliathProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GOLIATH);
	pGoliathProperty->SetDefensePoint(pGoliathProperty->GetDefensePoint() + 1);
}
