#include "pch.h"
#include "Barracks.h"

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

#include "Marine.h"
#include "Firebat.h"
#include "Medic.h"
#include "Ghost.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
using namespace std;

CBarracks::CBarracks(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CBarracks::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 배럭에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 128, 96 });

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
	m_pCnstrctnAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksCnstrctn");
	m_pBuildAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksPrdc");
	m_pLandAnim			= CResourceManager::GetManager()->GetAnimation(L"BrrcksLnd");
	m_pLandingAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksLnding");
	m_pLiftAnim			= CResourceManager::GetManager()->GetAnimation(L"BrrcksLft");
	m_pLiftingAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksLfting");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm0");
	m_pBigWireframe[1]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm1");
	m_pBigWireframe[2]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm2");
	m_pBigWireframe[3]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm3");
	m_pBigWireframe[4]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm4");
	m_pBigWireframe[5]	= CResourceManager::GetManager()->GetSprite(L"BrrcksBgWrfrm5");
	SetAnimation(m_pCnstrctnAnim);

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);

	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_MARINE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_FIREBAT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_MEDIC);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_GHOST);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::SET_RALLY_POINT);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_MARINE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_FIREBAT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_MEDIC);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_GHOST);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::SET_RALLY_POINT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::CANCEL_LAST);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

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
	SetCurMP(0);
	SetCurShield(0);
	SetTerranBuildingType(ETerranBuildingType::BARRACKS);
	m_pCurBigWireframe = m_pBigWireframe[0];


	/********************
		Barracks 클래스
	********************/
	SetBarracksState(EBarracksState::CONSTRUCTION);

	m_pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
	m_pFirebatProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::FIREBAT);
	m_pMedicProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MEDIC);
	m_pGhostProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GHOST);
}

void CBarracks::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	BuildUnit();
}

void CBarracks::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CBarracks::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CBarracks::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CBarracks::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CBarracks::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CBarracks::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CBarracks::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetBarracksState(EBarracksState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eBarracksState != EBarracksState::LIFT_OFF) { break; }
		SetBarracksState(EBarracksState::MOVE);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTilePosition = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;

		// TODO: 길 찾기 알고리즘 없이 바로 이동합니다.
	}
	break;

	case ECommandType::SET_RALLY_POINT:
	{
		m_tRallyPosition = static_cast<CRallyPoint*>(pCmd)->m_tDstPosition;
		m_tRallyTilePosition = static_cast<CRallyPoint*>(pCmd)->m_tDstTile;
		m_bRallyPoint = true;
		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
	break;

	case ECommandType::BUILD_MARINE:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pMarineProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pMarineProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pMarineProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::MARINE);
	}
	break;

	case ECommandType::BUILD_FIREBAT:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pFirebatProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pFirebatProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pFirebatProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::FIREBAT);
	}
	break;

	case ECommandType::BUILD_MEDIC:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pMedicProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pMedicProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pMedicProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::MEDIC);
	}
	break;

	case ECommandType::BUILD_GHOST:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pGhostProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pGhostProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pGhostProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::GHOST);
	}
	break;

	case ECommandType::CANCEL_LAST:
	{
		ETerranUnitType eTerranUnitType = m_queBuildingUnits.back();
		switch (eTerranUnitType)
		{
		case ETerranUnitType::MARINE:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pMarineProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pMarineProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pMarineProperty->GetGas());
		}
		break;


		case ETerranUnitType::FIREBAT:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pFirebatProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pFirebatProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pFirebatProperty->GetGas());
		}
		break;


		case ETerranUnitType::MEDIC:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pMedicProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pMedicProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pMedicProperty->GetGas());
		}
		break;


		case ETerranUnitType::GHOST:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pGhostProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pGhostProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pGhostProperty->GetGas());
		}
		break;
		}

		m_queBuildingUnits.pop_back();
		if (m_queBuildingUnits.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetBarracksState(EBarracksState::LAND);
		}
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CBarracks::ExecuteCommand()
{
	switch (m_eBarracksState)
	{
	case EBarracksState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		m_pCurCnstrctnDeltaSeconds += fDeltaSeconds;

		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::BARRACKS, 1);

			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetBarracksState(EBarracksState::LAND);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EBarracksState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EBarracksState::LANDING:
	{

	}
	break;

	case EBarracksState::LIFTING_OFF:
	{

	}
	break;

	case EBarracksState::LIFT_OFF:
	{

	}
	break;

	case EBarracksState::BUILD:
	{
		SetAnimation(m_pBuildAnim);
	}
	break;

	case EBarracksState::DIE:
	{

	}
	break;
	}
}

void CBarracks::BuildUnit()
{
	if (GetDead() == true)
	{
		SetBarracksState(EBarracksState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queBuildingUnits.empty()) { return; }
	SetBarracksState(EBarracksState::BUILD);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurBuildDeltaSecond += fDeltaSeconds;

	switch (m_queBuildingUnits.front())
	{
	case ETerranUnitType::MARINE:
	{
		if (m_fCurBuildDeltaSecond >= m_pMarineProperty->GetSeconds())
		{
			CMarine* pMarineObject = new CMarine(*m_pMarineProperty);
			pMarineObject->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pMarineObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pMarineObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pMarineObject);

			if (m_bRallyPoint)
			{
				pMarineObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tmardy00.wav", ESoundChannel::UNIT, 1.0f);
			SetBarracksState(EBarracksState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::FIREBAT:
	{
		if (m_fCurBuildDeltaSecond >= m_pFirebatProperty->GetSeconds())
		{
			CFirebat* pFirebatObject = new CFirebat(*m_pFirebatProperty);
			pFirebatObject->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pFirebatObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pFirebatObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pFirebatObject);

			if (m_bRallyPoint)
			{
				pFirebatObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tfbrdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetBarracksState(EBarracksState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::MEDIC:
	{
		if (m_fCurBuildDeltaSecond >= m_pMedicProperty->GetSeconds())
		{
			CMedic* pMedicObject = new CMedic(*m_pMedicProperty);
			pMedicObject->SetOwnerType(EOwnerType::PLAYER);
			pMedicObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pMedicObject->Initialize();// *** 초기화 함수를 반드시 호출해야 한다. ***
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pMedicObject);

			if (m_bRallyPoint)
			{
				pMedicObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tmdrdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetBarracksState(EBarracksState::LAND);
			
			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::GHOST:
	{
		if (m_fCurBuildDeltaSecond >= m_pGhostProperty->GetSeconds())
		{
			CGhost* pGhostObject = new CGhost(*m_pGhostProperty);
			pGhostObject->SetOwnerType(EOwnerType::PLAYER);
			pGhostObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pGhostObject->Initialize();// *** 초기화 함수를 반드시 호출해야 한다. ***
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pGhostObject);

			if (m_bRallyPoint)
			{
				pGhostObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tghrdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetBarracksState(EBarracksState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;
	}
}

