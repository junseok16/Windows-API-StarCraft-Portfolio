#include "pch.h"
#include "ControlTower.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "PropertyManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "Scene.h"

#include "UpgradeProperty.h"
#include "BuildingProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"

#include "RectangleColliderComponent.h"
#include "Command.h"

CControlTower::CControlTower(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) {}

void CControlTower::Initialize()
{
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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"CntrlTwrCnstrctn");
	m_pAddOnConnectAnim = CResourceManager::GetManager()->GetAnimation(L"CntrlTwrConnect");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"CntrlTwrIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"CntrlTwrUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"CntrlTwrBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);

	//m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_ION_THRUSTERS);
	//m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_SIEGE_TECH);

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
	SetTerranBuildingType(ETerranBuildingType::CONTROL_TOWER);

	/********************
		Academy 클래스
	********************/
	SetControlTowerState(EControlTowerState::CONSTRUCTION);
	SetAnimation(m_pLandAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	//m_pIonThrustersProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::ION_THRUSTERS);
	//m_pSiegeTechProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::SIEGE_TECH);
}

void CControlTower::Update() {
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CControlTower::LateUpdate() {
	CBuilding::LateUpdate();
}

void CControlTower::Render(HDC _hDC) {
	CBuilding::Render(_hDC);
}

void CControlTower::Release() {
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CControlTower::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CControlTower::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CControlTower::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CControlTower::AnalyseCommand() {
	if (GetDead() == true)
	{
		SetControlTowerState(EControlTowerState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
		/*
	case ECommandType::UPGRADE_ION_THRUSTERS:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pIonThrustersProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pIonThrustersProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::ION_THRUSTERS);
	}
	break;

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
	}
	break;

	default:
		break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CControlTower::ExecuteCommand() {
	switch (m_eControlTowerState)
	{
	case EControlTowerState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd03.wav", ESoundChannel::UNIT, 1.0f);

			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::CONTROL_TOWER, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetControlTowerState(EControlTowerState::IDLE);
			SetAnimation(m_pAddOnConnectAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EControlTowerState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EControlTowerState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case EControlTowerState::DIE:
	{

	}
	break;

	default:
		break;
	}
}

void CControlTower::Upgrade() {
	if (GetDead() == true)
	{
		SetControlTowerState(EControlTowerState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetControlTowerState(EControlTowerState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	/*
	case ETerranUpgradeType::ION_THRUSTERS:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pIonThrustersProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::ION_THRUSTERS, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd06.wav", ESoundChannel::UNIT, 1.0f);
			SetControlTowerState(EMachineShopState::IDLE);

			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_ION_THRUSTERS),
				m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
			);

			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;

	case ETerranUpgradeType::SIEGE_TECH:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pSiegeTechProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::SIEGE_TECH, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd02.wav", ESoundChannel::UNIT, 1.0f);
			SetControlTowerState(EMachineShopState::IDLE);

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_SIEGE_TECH),
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
	*/
	}
}
