#include "pch.h"
#include "PhysicsLab.h"

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

#include "UpgradeProperty.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"

CPhysicsLab::CPhysicsLab(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) {
}

void CPhysicsLab::Initialize() {
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 64, 64 });
	SetGdiRender(true);

	// 배럭에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 32, 32 });

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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"PhyscLbCnstrctn");
	m_pAddOnConnectAnim = CResourceManager::GetManager()->GetAnimation(L"PhyscLbConnect");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"PhyscLbIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"PhyscLbUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"PhyscLbBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_YAMATO_CANNON);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_G].push_back(ECommandType::CANCEL_UPGRADE);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct5"));
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
	SetTerranBuildingType(ETerranBuildingType::PHYSICS_LAB);

	/********************
		Academy 클래스
	********************/
	SetPhysicsLabState(EPhysicsLabState::CONSTRUCTION);
	SetAnimation(m_pLandAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pYamatoCannonProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::YAMATO_CANNON);
	//m_pSiegeTechProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::SIEGE_TECH);
}

void CPhysicsLab::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CPhysicsLab::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CPhysicsLab::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CPhysicsLab::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CPhysicsLab::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CPhysicsLab::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CPhysicsLab::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CPhysicsLab::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetPhysicsLabState(EPhysicsLabState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::UPGRADE_YAMATO_CANNON:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pYamatoCannonProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pYamatoCannonProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::YAMATO_CANNON);
	}
	break;
	/*
	case ECommandType::UPGRADE_SIEGE_TECH:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pSiegeTechProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pSiegeTechProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::SIEGE_TECH);
	}
	break;
	*/
	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }

		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::YAMATO_CANNON:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pYamatoCannonProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pYamatoCannonProperty->GetGas());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetPhysicsLabState(EPhysicsLabState::IDLE);
		}
	}
	break;
	
	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CPhysicsLab::ExecuteCommand()
{
	switch (m_ePhysicsLabState)
	{
	case EPhysicsLabState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd03.wav", ESoundChannel::UNIT, 1.0f);

			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::PHYSICS_LAB, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetPhysicsLabState(EPhysicsLabState::IDLE);
			SetAnimation(m_pAddOnConnectAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EPhysicsLabState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EPhysicsLabState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case EPhysicsLabState::DIE:
	{

	}
	break;

	default:
		break;
	}
}

void CPhysicsLab::Upgrade() {
	if (GetDead() == true)
	{
		SetPhysicsLabState(EPhysicsLabState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetPhysicsLabState(EPhysicsLabState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::YAMATO_CANNON:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pYamatoCannonProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::YAMATO_CANNON, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd02.wav", ESoundChannel::UNIT, 1.0f);
			SetPhysicsLabState(EPhysicsLabState::IDLE);

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_YAMATO_CANNON),
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
