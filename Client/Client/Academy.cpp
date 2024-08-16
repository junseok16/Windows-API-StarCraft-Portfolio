#include "pch.h"
#include "Academy.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "PropertyManager.h"
#include "Scene.h"
#include "Player.h"

#include "RectangleColliderComponent.h"
#include "Command.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Unit.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"

CAcademy::CAcademy(CBuildingProperty& _buildingProperty)
    : CBuilding(_buildingProperty) { }

void CAcademy::Initialize()
{
    CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 96, 64 });
	SetGdiRender(true);

	// 배럭에 사각형 콜라이더 컴포넌트를 붙입니다.
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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"AcdmyCnstrctn");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"AcdmyIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"AcdmyUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"AcdmyBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_U238_SHELLS);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_STIMPACK_TECH);

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
	SetCurMP(0);
	SetCurShield(0);
	SetTerranBuildingType(ETerranBuildingType::ACADEMY);
	
	/********************
		Academy 클래스
	********************/
	SetAcademyState(EAcademyState::CONSTRUCTION);
	SetAnimation(m_pCnstrctnAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pU238ShellsProperty	= CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::U238_SHELLS);
	m_pStimpackTechProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::STIMPACK_TECH);
}

void CAcademy::Update()
{
    CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CAcademy::LateUpdate()
{
    CBuilding::LateUpdate();
}

void CAcademy::Render(HDC _hDC)
{
    CBuilding::Render(_hDC);
}

void CAcademy::Release()
{
    CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CAcademy::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CAcademy::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CAcademy::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CAcademy::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetAcademyState(EAcademyState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::UPGRADE_U238_SHELLS:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pU238ShellsProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pU238ShellsProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::U238_SHELLS);
	}
	break;

	case ECommandType::UPGRADE_STIMPACK_TECH:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pStimpackTechProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pStimpackTechProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::STIMPACK_TECH);
	}
	break;

	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }
		
		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::U238_SHELLS:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pU238ShellsProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pU238ShellsProperty->GetGas());
		}
		break;

		case ETerranUpgradeType::STIMPACK_TECH:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pStimpackTechProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pStimpackTechProperty->GetGas());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetAcademyState(EAcademyState::IDLE);
		}
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CAcademy::ExecuteCommand()
{
	switch (m_eAcademyState)
	{
	case EAcademyState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::ACADEMY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetAcademyState(EAcademyState::IDLE);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EAcademyState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EAcademyState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case EAcademyState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CAcademy::Upgrade()
{
	if (GetDead() == true)
	{
		SetAcademyState(EAcademyState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetAcademyState(EAcademyState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::U238_SHELLS:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pU238ShellsProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::U238_SHELLS, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			CUnitProperty* pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
			pMarineProperty->SetRange(pMarineProperty->GetRange() + 32);

			SetAcademyState(EAcademyState::IDLE);

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_U238_SHELLS),
				m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
			);

			// 마린 유닛의 사거리를 늘린다.
			std::list<CObject*>& lstObjects = CSceneManager::GetManager()->GetCurScene()->GetUnits();
			for (const auto& pObject : lstObjects)
			{
				CUnit* pUnit = dynamic_cast<CUnit*>(pObject);
				if (pUnit->GetTerranUnitType() == ETerranUnitType::MARINE
					&& pUnit->GetOwnerType() == EOwnerType::PLAYER)
				{
					pUnit->SetCurRange(160);
				}
			}

			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}

			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;

	case ETerranUpgradeType::STIMPACK_TECH:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pStimpackTechProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::STIMPACK_TECH, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd02.wav", ESoundChannel::UNIT, 1.0f);
			SetAcademyState(EAcademyState::IDLE);

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_STIMPACK_TECH),
				m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
			);

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
