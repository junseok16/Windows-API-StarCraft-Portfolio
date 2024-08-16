#include "pch.h"
#include "Starport.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "PropertyManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TimeManager.h"

#include "Scene.h"
#include "Player.h"

#include "RectangleColliderComponent.h"
#include "Command.h"
#include "DynamicTilemapObject.h"

#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "ControlTower.h"

#include "Battlecruiser.h"
#include "ScienceVessel.h"
using namespace std;

CStarport::CStarport(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CStarport::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 팩토리에 사각형 콜라이더 컴포넌트를 붙입니다.
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
	m_pCnstrctnAnim		= CResourceManager::GetManager()->GetAnimation(L"StrprtCnstrctn");
	m_pBuildAnim		= CResourceManager::GetManager()->GetAnimation(L"StrprtPrdc");
	m_pLandAnim			= CResourceManager::GetManager()->GetAnimation(L"StrprtLnd");
	// m_pLandingAnim	= CResourceManager::GetManager()->GetAnimation(L"BrrcksLnding");
	// m_pLiftAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksLft");
	// m_pLiftingAnim	= CResourceManager::GetManager()->GetAnimation(L"BrrcksLfting");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"StrprtBgWrfrm5");
	SetAnimation(m_pLandAnim);


	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);

	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_SCIENCE_VESSEL);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_BATTLECRUISER);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::SET_RALLY_POINT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_CONTROL_TOWER);
	
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_SCIENCE_VESSEL);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_BATTLECRUISER);
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
	SetTerranBuildingType(ETerranBuildingType::STARPORT);
	m_pCurBigWireframe = m_pBigWireframe[0];


	/********************
		Factory 클래스
	********************/
	SetStarportState(EStarportState::CONSTRUCTION);
	
	m_pScienceVesselProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SCIENCE_VESSEL);
	m_pBattlecruiserProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::BATTLE_CRUISER);
	m_pContolTowerProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::CONTROL_TOWER);
}

void CStarport::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	BuildUnit();
}

void CStarport::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CStarport::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CStarport::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CStarport::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetStarportState(EStarportState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eStarportState != EStarportState::LIFT_OFF) { break; }
		SetStarportState(EStarportState::LIFT_OFF);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTilePosition = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;
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

	
	case ECommandType::BUILD_SCIENCE_VESSEL:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pScienceVesselProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pScienceVesselProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pScienceVesselProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::SCIENCE_VESSEL);
	}
	break;
	
	case ECommandType::BUILD_BATTLECRUISER:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pBattlecruiserProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pBattlecruiserProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pBattlecruiserProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::BATTLE_CRUISER);
	}
	break;

	case ECommandType::BUILD_CONTROL_TOWER:
	{
		Vector2 tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		Vector2Int tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;

		CControlTower* pControlTower = new CControlTower(*m_pContolTowerProperty);
		pControlTower->SetOwnerType(EOwnerType::PLAYER);

		Vector2 tLeftTop = { tDstTile.m_iX * FTILECX, tDstTile.m_iY * FTILECY };
		Vector2 tOffset = { (float)m_pContolTowerProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pContolTowerProperty->GetTileSize().m_iY * FTILECY * 0.5f };
		Vector2 tPosition = tLeftTop + tOffset;

		pControlTower->SetPosition({ tPosition });
		pControlTower->Initialize();
		CSceneManager::GetManager()->GetCurScene()->InsertObject(pControlTower);

		CGameManager::GetManager()->IncreaseProducedMineral(-m_pContolTowerProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pContolTowerProperty->GetGas());

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		pDynamicTilemapObject->InsertDynamicTiles(tDstTile, m_pContolTowerProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_CONTROL_TOWER),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);
	}
	break;

	case ECommandType::CANCEL_LAST:
	{
		ETerranUnitType eTerranUnitType = m_queBuildingUnits.back();
		switch (eTerranUnitType)
		{
		case ETerranUnitType::SCIENCE_VESSEL:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pScienceVesselProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pScienceVesselProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pScienceVesselProperty->GetGas());
		}
		break;


		case ETerranUnitType::BATTLE_CRUISER:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pBattlecruiserProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pBattlecruiserProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pBattlecruiserProperty->GetGas());
		}
		break;
		}

		m_queBuildingUnits.pop_back();
		if (m_queBuildingUnits.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetStarportState(EStarportState::LAND);
		}
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CStarport::ExecuteCommand()
{
	switch (m_eStarportState)
	{
	case EStarportState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		m_pCurCnstrctnDeltaSeconds += fDeltaSeconds;

		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::STARPORT, 1);

			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetStarportState(EStarportState::LAND);
			SetAnimation(m_pLandAnim);

			CGameManager::GetManager()->InsertAddOnTilePosition(ETerranAddOnType::CONTROL_TOWER, CGeometry::ToTilePosition({ m_tPosition.m_fX + 80.0f, m_tPosition.m_fY }));
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EStarportState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EStarportState::LANDING:
	{

	}
	break;
	
	case EStarportState::LIFTING_OFF:
	{

	}
	break;

	case EStarportState::LIFT_OFF:
	{

	}
	break;

	case EStarportState::BUILD:
	{
		SetAnimation(m_pBuildAnim);
	}
	break;

	case EStarportState::DIE:
	{

	}
	break;
	}
}

void CStarport::BuildUnit()
{
	if (GetDead() == true)
	{
		SetStarportState(EStarportState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queBuildingUnits.empty()) { return; }
	SetStarportState(EStarportState::BUILD);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurBuildDeltaSecond += fDeltaSeconds;

	switch (m_queBuildingUnits.front())
	{
	case ETerranUnitType::SCIENCE_VESSEL:
	{
		if (m_fCurBuildDeltaSecond >= m_pScienceVesselProperty->GetSeconds())
		{
			CScienceVessel* pScienceVessel = new CScienceVessel(*m_pScienceVesselProperty);
			pScienceVessel->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pScienceVessel->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 50.0f });
			pScienceVessel->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pScienceVessel);

			if (m_bRallyPoint)
			{
				pScienceVessel->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tverdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetStarportState(EStarportState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::BATTLE_CRUISER:
	{
		if (m_fCurBuildDeltaSecond >= m_pBattlecruiserProperty->GetSeconds())
		{
			CBattlecruiser* pBattlecruiser = new CBattlecruiser(*m_pBattlecruiserProperty);
			pBattlecruiser->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pBattlecruiser->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 50.0f });
			pBattlecruiser->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pBattlecruiser);

			if (m_bRallyPoint)
			{
				pBattlecruiser->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tbardy00.wav", ESoundChannel::UNIT, 1.0f);
			SetStarportState(EStarportState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	default:
	break;
	}
}

void CStarport::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CStarport::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CStarport::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}