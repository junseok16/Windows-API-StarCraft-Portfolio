#include "pch.h"
#include "CommandCenter.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "PropertyManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Player.h"

#include "RectangleColliderComponent.h"
#include "Command.h"
#include "DynamicTilemapObject.h"

#include "BuildingProperty.h"
#include "UnitProperty.h"

#include "SCV.h"
#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "NuclearSilo.h"
using namespace std;

CCommandCenter::CCommandCenter(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CCommandCenter::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 커맨드 센터에 사각형 콜라이더 컴포넌트를 붙입니다.
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
	pRectCollider->InsertCollisionFlag(ECollisionType::GATHER);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);


	/********************
		AnimationObject 클래스
	********************/
	m_pCnstrctnAnim		= CResourceManager::GetManager()->GetAnimation(L"CmdCntrCnstrctn");
	m_pLandAnim			= CResourceManager::GetManager()->GetAnimation(L"CmdCntrLnd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"CmndCntrBgWrfrm5");
	SetAnimation(m_pCnstrctnAnim);

	/********************
		TerranObject 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);

	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_SCV);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::SET_RALLY_POINT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_COMSAT_STATION);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_NUCLEAR_SILO);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_SCV);
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
	SetTerranBuildingType(ETerranBuildingType::COMMAND_CENTER);
	m_pCurBigWireframe = m_pBigWireframe[0];
	

	/********************
		CommandCenter 클래스
	********************/
	SetCommandCenterState(ECommandCenterState::CONSTRUCTION);

	m_pSCVProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SCV);
	m_pNuclearSiloProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::NUCLEAR_SILO);
}

void CCommandCenter::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	BuildUnit();
}

void CCommandCenter::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CCommandCenter::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CCommandCenter::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CCommandCenter::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetCommandCenterState(ECommandCenterState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eCommandCenterState != ECommandCenterState::LIFT_OFF) { break; }
		SetCommandCenterState(ECommandCenterState::LIFT_OFF);
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

	case ECommandType::BUILD_SCV:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pSCVProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pSCVProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pSCVProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::SCV);
	}
	break;

	case ECommandType::BUILD_COMSAT_STATION:
	{
		// TODO: 콤셋 스테이션
	}
	break;

	case ECommandType::BUILD_NUCLEAR_SILO:
	{
		Vector2 tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		Vector2Int tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;

		CNuclearSilo* pNuclearSilo = new CNuclearSilo(*m_pNuclearSiloProperty);
		pNuclearSilo->SetOwnerType(EOwnerType::PLAYER);

		Vector2 tLeftTop = { tDstTile.m_iX * FTILECX, tDstTile.m_iY * FTILECY };
		Vector2 tOffset = { (float)m_pNuclearSiloProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pNuclearSiloProperty->GetTileSize().m_iY * FTILECY * 0.5f };
		Vector2 tPosition = tLeftTop + tOffset;

		pNuclearSilo->SetPosition({ tPosition });
		pNuclearSilo->Initialize();
		CSceneManager::GetManager()->GetCurScene()->InsertObject(pNuclearSilo);

		CGameManager::GetManager()->IncreaseProducedMineral(-m_pNuclearSiloProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pNuclearSiloProperty->GetGas());

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		pDynamicTilemapObject->InsertDynamicTiles(tDstTile, m_pNuclearSiloProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_NUCLEAR_SILO),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_COMSAT_STATION),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);
		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
	break;

	case ECommandType::CANCEL_LAST:
	{
		ETerranUnitType eTerranUnitType = m_queBuildingUnits.back();
		switch (eTerranUnitType)
		{
		case ETerranUnitType::SCV:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pSCVProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pSCVProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pSCVProperty->GetGas());
		}
		break;
		}

		m_queBuildingUnits.pop_back();
		if (m_queBuildingUnits.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetCommandCenterState(ECommandCenterState::LAND);
		}
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CCommandCenter::ExecuteCommand()
{
	switch (m_eCommandCenterState)
	{
	case ECommandCenterState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		m_pCurCnstrctnDeltaSeconds += fDeltaSeconds;

		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::COMMAND_CENTER, 1);
			CGameManager::GetManager()->IncreaseProducedSupply(10);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetCommandCenterState(ECommandCenterState::LAND);
			SetAnimation(m_pLandAnim);

			CGameManager::GetManager()->InsertCmdCntrTilePosition(CGeometry::ToTilePosition({ m_tPosition.m_fX - 48.0f, m_tPosition.m_fY - 32.0f }));
			CGameManager::GetManager()->InsertCmdCntrTilePosition(CGeometry::ToTilePosition({ m_tPosition.m_fX - 48.0f, m_tPosition.m_fY }));
			CGameManager::GetManager()->InsertCmdCntrTilePosition(CGeometry::ToTilePosition({ m_tPosition.m_fX - 48.0f, m_tPosition.m_fY + 32.0f }));
			CGameManager::GetManager()->InsertAddOnTilePosition(ETerranAddOnType::NUCLEAR_SILO, CGeometry::ToTilePosition({ m_tPosition.m_fX + 80.0f, m_tPosition.m_fY }));
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case ECommandCenterState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case ECommandCenterState::BUILD:
	{

	}
	break;

	case ECommandCenterState::DIE:
	{

	}
	break;
	}
}

void CCommandCenter::BuildUnit()
{
	if (GetDead() == true)
	{
		SetCommandCenterState(ECommandCenterState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queBuildingUnits.empty()) { return; }
	SetCommandCenterState(ECommandCenterState::BUILD);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurBuildDeltaSecond += fDeltaSeconds;

	switch (m_queBuildingUnits.front())
	{
	case ETerranUnitType::SCV:
	{
		if (m_fCurBuildDeltaSecond >= m_pSCVProperty->GetSeconds())
		{
			CSCV* pSCVObject = new CSCV(*m_pSCVProperty);
			pSCVObject->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pSCVObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pSCVObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pSCVObject);

			if (m_bRallyPoint)
			{
				pSCVObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}
			
			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tscrdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetCommandCenterState(ECommandCenterState::LAND);
			
			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;
	}
}

void CCommandCenter::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CCommandCenter::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CCommandCenter::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}
