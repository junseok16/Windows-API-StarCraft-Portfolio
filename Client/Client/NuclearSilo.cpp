#include "pch.h"
#include "NuclearSilo.h"

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

CNuclearSilo::CNuclearSilo(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) {
}

void CNuclearSilo::Initialize() {
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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"NclrSloCnstrctn");
	m_pAddOnConnectAnim = CResourceManager::GetManager()->GetAnimation(L"NclrSloConnect");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"NclrSloIdle");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"NclrSloUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"NclrSloBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ARM_NUCLEAR_SILO);
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
	SetTerranBuildingType(ETerranBuildingType::NUCLEAR_SILO);


	/********************
		Academy 클래스
	********************/
	SetNuclearSiloState(ENuclearSiloState::CONSTRUCTION);
	SetAnimation(m_pLandAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pArmNclrSloProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::ARM_NUCLEAR_SILO);
}

void CNuclearSilo::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CNuclearSilo::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CNuclearSilo::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CNuclearSilo::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CNuclearSilo::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CNuclearSilo::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CNuclearSilo::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CNuclearSilo::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetNuclearSiloState(ENuclearSiloState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::ARM_NUCLEAR_SILO:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pArmNclrSloProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pArmNclrSloProperty->GetGas());
		CGameManager::GetManager()->IncreaseConsumedSupply(m_pArmNclrSloProperty->GetConsumeSupply());
		m_queUpgrades.push_back(ETerranUpgradeType::ARM_NUCLEAR_SILO);
	}
	break;
	
	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }

		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::ARM_NUCLEAR_SILO:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pArmNclrSloProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pArmNclrSloProperty->GetGas());
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pArmNclrSloProperty->GetConsumeSupply());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetNuclearSiloState(ENuclearSiloState::IDLE);
		}
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CNuclearSilo::ExecuteCommand() {
	switch (m_eNuclearSiloState)
	{
	case ENuclearSiloState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd03.wav", ESoundChannel::UNIT, 1.0f);

			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::NUCLEAR_SILO, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetNuclearSiloState(ENuclearSiloState::IDLE);
			SetAnimation(m_pAddOnConnectAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case ENuclearSiloState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case ENuclearSiloState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case ENuclearSiloState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CNuclearSilo::Upgrade() {
	if (GetDead() == true)
	{
		SetNuclearSiloState(ENuclearSiloState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetNuclearSiloState(ENuclearSiloState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::ARM_NUCLEAR_SILO:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pArmNclrSloProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::ARM_NUCLEAR_SILO, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd07.wav", ESoundChannel::UNIT, 1.0f);
			SetNuclearSiloState(ENuclearSiloState::IDLE);

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
