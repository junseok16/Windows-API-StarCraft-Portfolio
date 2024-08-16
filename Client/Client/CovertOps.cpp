#include "pch.h"
#include "CovertOps.h"

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

CCovertOps::CCovertOps(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) {
}

void CCovertOps::Initialize() {
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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"CvrtOpsCnstrctn");
	m_pAddOnConnectAnim = CResourceManager::GetManager()->GetAnimation(L"CvrtOpsConnect");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"CvrtOpsIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"CvrtOpsUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"CvrtOpsBgWrfrm5");

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
	SetTerranBuildingType(ETerranBuildingType::COVERT_OPS);

	/********************
		Academy 클래스
	********************/
	SetCovertOpsState(ECovertOpsState::CONSTRUCTION);
	SetAnimation(m_pLandAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	//m_pIonThrustersProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::ION_THRUSTERS);
	//m_pSiegeTechProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::SIEGE_TECH);
}

void CCovertOps::Update() {
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CCovertOps::LateUpdate() {
	CBuilding::LateUpdate();
}

void CCovertOps::Render(HDC _hDC) {
	CBuilding::Render(_hDC);
}

void CCovertOps::Release() {
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CCovertOps::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CCovertOps::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CCovertOps::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CCovertOps::AnalyseCommand() {
	if (GetDead() == true)
	{
		SetCovertOpsState(ECovertOpsState::DIE);
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

	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }
	}
	break;
	*/
	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CCovertOps::ExecuteCommand()
{
	switch (m_eCovertOpsState)
	{
	case ECovertOpsState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd03.wav", ESoundChannel::UNIT, 1.0f);

			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::COVERT_OPS, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetCovertOpsState(ECovertOpsState::IDLE);
			SetAnimation(m_pAddOnConnectAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case ECovertOpsState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case ECovertOpsState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case ECovertOpsState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CCovertOps::Upgrade()
{
	if (GetDead() == true)
	{
		SetCovertOpsState(ECovertOpsState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetCovertOpsState(ECovertOpsState::UPGRADE);

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
			SetCovertOpsState(ECovertOpsState::IDLE);

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
			SetCovertOpsState(ECovertOpsState::IDLE);

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
