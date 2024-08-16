#include "pch.h"
#include "SCV.h"
#include "RectangleColliderComponent.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "PropertyManager.h"
#include "AStarManager.h"
#include "SoundManager.h"

#include "DynamicTilemapObject.h"
#include "Command.h"

#include "BuildingProperty.h"
#include "UnitProperty.h"

#include "Scene.h"
#include "Player.h"

#include "CommandCenter.h"
#include "SupplyDepot.h"
#include "Refinery.h"
#include "Barracks.h"
#include "EngineeringBay.h"
#include "Academy.h"
#include "Factory.h"
#include "Armory.h"
#include "Starport.h"
#include "ScienceFacility.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"

#include "Mineral.h"
#include "Sprite.h"
using namespace std;

CSCV::CSCV(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CSCV::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 20, 30 });
	SetGdiRender(true);

	// SCV에 사각형 콜라이더 컴포넌트를 붙입니다.
	pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 20, 30 });

	pRectCollider->SetCollisionType(ECollisionType::GROUND_UNIT);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	// pRectCollider->SetCollisionType(ECollisionType::GATHER);
	// pRectCollider->ResetCollisionFlag();
	// pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	// pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	// pRectCollider->InsertCollisionFlag(ECollisionType::GAS);
	
	// pRectCollider->SetCollisionType(ECollisionType::BUILD);
	// pRectCollider->ResetCollisionFlag();
	// pRectCollider->InsertCollisionFlag(ECollisionType::UNIT);
	// pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	// pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);


	/********************
		AnimationObject 클래스
	********************/
	{
		m_pUnitMoveAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopSE");

		m_pUnitStopAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVMoveStopSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST]		 = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH]		 = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST]		 = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH]		 = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"SCVBldAttckSE");

		m_pUnitHitingAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"SCVHting");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SCVHting");

		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"BangS");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"SCVPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"SCVBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"SCVSmllWrfrm5");
		SetAnimation(m_pUnitMoveAnim[(int32)EDirectionState::SOUTH]);
	}
	

	/********************
		Terran 클래스
	********************/
	{
		SetTerranObjectType(ETerranObjectType::GROUND_UNIT);
		SetUnitAtributeType(EUnitAttributeType::BIOLOGICAL);
		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::MOVE);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::STOP);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ATTACK);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_BASIC_STRUCTURE);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_ADVANCED_STRUCTURE);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_COMMAND_CENTER);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_SUPPLY_DEPOT);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_REFINERY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_BARRACKS);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_ENGINEERING_BAY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_ACADEMY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::GO_BACK);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_C].push_back(ECommandType::BUILD_FACTORY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_C].push_back(ECommandType::BUILD_STARPORT);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_C].push_back(ECommandType::BUILD_SCIENCE_FACILITY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_C].push_back(ECommandType::BUILD_ARMORY);
		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_C].push_back(ECommandType::GO_BACK);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);
	}
	

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct1"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(24.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	/********************
		Unit 클래스
	********************/
	SetCurHP(m_unitProperty.GetMaxHP());
	SetCurMP(m_unitProperty.GetMaxMP());
	SetCurShield(m_unitProperty.GetMaxShield());
	SetCurSpeed(m_unitProperty.GetSpeed());
	SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds());
	SetCurRange(m_unitProperty.GetRange());
	SetTerranUnitType(ETerranUnitType::SCV);


	/********************
		SCV 클래스
	********************/
	SetSCVState(ESCVState::STOP);
	m_pCommandCenterProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::COMMAND_CENTER);
	m_pSupplyDepotProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::SUPPLY_DEPOT);
	m_pRefineryProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::REFINERY);
	m_pBarracksProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::BARRACKS);
	m_pEngineeringBayProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::ENGINEERING_BAY);
	m_pAcademyProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::ACADEMY);
	m_pFactoryProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::FACTORY);
	m_pStarportProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::STARPORT);
	m_pScienceFacilityProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::SCIENCE_FACILITY);
	m_pArmoryProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::ARMORY);

	m_pMineralOrb = CResourceManager::GetManager()->GetSprite(L"MnrlOrb");
	m_pGasOrb = CResourceManager::GetManager()->GetSprite(L"GasOrb");
}

void CSCV::Update()
{
	CUnit::Update();
	UpdateDirection();
	UpdateOrbPosition();
	AnalyseCommand();
	ExecuteCommand();
}

void CSCV::LateUpdate()
{
	CUnit::LateUpdate();
}

void CSCV::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
	RenderResource(_hDC);

	/*
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	for (uint32 i = 1; i < m_vecOptimalPath.size(); ++i)
	{
		Vector2 tSrcPosition = { m_vecOptimalPath[i - 1].m_iX * FTILECX + FTILECX * 0.5f, m_vecOptimalPath[i - 1].m_iY * FTILECY + FTILECY * 0.5f};
		Vector2 tDstPosition = { m_vecOptimalPath[i].m_iX * FTILECX + FTILECX * 0.5f, m_vecOptimalPath[i].m_iY * FTILECY + FTILECY * 0.5f};

		tSrcPosition.m_fX -= tCameraPosition.m_fX - FWINCX * 0.5f;
		tSrcPosition.m_fY -= tCameraPosition.m_fY - FWINCY * 0.5f;

		tDstPosition.m_fX -= tCameraPosition.m_fX - FWINCX * 0.5f;
		tDstPosition.m_fY -= tCameraPosition.m_fY - FWINCY * 0.5f;

		CGeometry::DrawLine(_hDC, tSrcPosition , tDstPosition, RGB(0, 255, 0));
	}
	*/
	// CGeometry::DrawString(_hDC, { 300, 20 }, std::to_wstring(m_fDegree), RGB(0, 255, 0));
}

void CSCV::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CSCV::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);

	if (m_eSCVState == ESCVState::MOVE_TO_GATHER)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(_pDstCollider->GetComponentOwner());
		VERIFY_NULLPTR(pTerranObject);

		if (pTerranObject->GetObjectType() == EObjectType::MINERAL && m_pTarget == pTerranObject)
		{
			SetSCVState(ESCVState::GATHER);
			m_tDstPosition = m_tPosition;
		}
	}

	if (m_eSCVState == ESCVState::RETURN_CARGO)
	{
		CBuilding* pBuilding = dynamic_cast<CBuilding*>(_pDstCollider->GetComponentOwner());
		VERIFY_NULLPTR(pBuilding);

		if ((pBuilding->GetObjectType() == EObjectType::BUILDING) && (pBuilding->GetTerranBuildingType() == ETerranBuildingType::COMMAND_CENTER))
		{
			// TODO: 미네랄 스프라이트를 없앤다.
			m_pCurResourceSprite = nullptr;
			CGameManager::GetManager()->IncreaseProducedMineral(8);
			CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tMnrlTile);
			if (!m_queOptimalPath.empty())
			{
				m_queOptimalPath.pop();
			}
			SetSCVState(ESCVState::MOVE_TO_GATHER);
		}
	}
}

void CSCV::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CSCV::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CSCV::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetSCVState(ESCVState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }
	
	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eSCVState == ESCVState::CONSTRUCT) { break; }

		SetSCVState(ESCVState::MOVE);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTile = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;

		CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tDstTile);
		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}
	}
	break;

	case ECommandType::STOP:
	{
		if (m_eSCVState == ESCVState::CONSTRUCT) { break; }

		SetSCVState(ESCVState::STOP);

		pRectCollider->SetCollisionType(ECollisionType::GROUND_UNIT);
		pRectCollider->ResetCollisionFlag();
		pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
		pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
		pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
		pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
		pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	}
	break;

	case ECommandType::ATTACK:
	{
		SetSCVState(ESCVState::ATTACK);
		m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;
	}
	break;

	case ECommandType::BUILD_COMMAND_CENTER:
	case ECommandType::BUILD_ENGINEERING_BAY:
	case ECommandType::BUILD_BARRACKS:
	case ECommandType::BUILD_FACTORY:
	case ECommandType::BUILD_STARPORT:
	case ECommandType::BUILD_SCIENCE_FACILITY:
	{
		if (m_eSCVState == ESCVState::CONSTRUCT) { break; }

		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetSCVState(ESCVState::BUILD);
		m_eCommandType = static_cast<CConstruct*>(pCmd)->m_eCommandType;
		m_tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		m_pTarget = nullptr;

		Vector2Int tDstTile[4] = { { m_tDstTile.m_iX - 1, m_tDstTile.m_iY }, { m_tDstTile.m_iX - 1, m_tDstTile.m_iY + 2 }, { m_tDstTile.m_iX + 4, m_tDstTile.m_iY }, { m_tDstTile.m_iX + 4, m_tDstTile.m_iY + 2 } };
		uint32 uiMinDistance = 8192;
		std::queue<Vector2Int> queOptimalPath;

		// 가장 가까운 건설 지점을 찾습니다.
		for (int i = 0; i < 4; ++i)
		{
			CAStarManager::GetManager()->FindOptimalPath(queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), tDstTile[i]);

			if (queOptimalPath.size() != 0 && queOptimalPath.size() < uiMinDistance)
			{
				m_iBuildDirection = i;
				uiMinDistance = queOptimalPath.size();
				m_queOptimalPath = queOptimalPath;
			}
		}
		
		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}
	}
	break;

	case ECommandType::BUILD_SUPPLY_DEPOT:
	case ECommandType::BUILD_ACADEMY:
	case ECommandType::BUILD_ARMORY:
	{
		if (m_eSCVState == ESCVState::CONSTRUCT) { break; }

		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetSCVState(ESCVState::BUILD);
		m_eCommandType = static_cast<CConstruct*>(pCmd)->m_eCommandType;
		m_tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		m_pTarget = nullptr;

		Vector2Int tDstTile[4] = { { m_tDstTile.m_iX - 1, m_tDstTile.m_iY }, { m_tDstTile.m_iX - 1, m_tDstTile.m_iY + 1 }, { m_tDstTile.m_iX + 3, m_tDstTile.m_iY }, { m_tDstTile.m_iX + 3, m_tDstTile.m_iY + 1 } };
		uint32 uiMinDistance = 8192;
		std::queue<Vector2Int> queOptimalPath;

		// 가장 가까운 건설 지점을 찾습니다.
		for (int i = 0; i < 4; ++i)
		{
			CAStarManager::GetManager()->FindOptimalPath(queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), tDstTile[i]);

			if (queOptimalPath.size() != 0 && queOptimalPath.size() < uiMinDistance)
			{
				m_iBuildDirection = i;
				uiMinDistance = queOptimalPath.size();
				m_queOptimalPath = queOptimalPath;
			}
		}

		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}
	}
	break;

	case ECommandType::BUILD_REFINERY:
	{

	}
	break;

	case ECommandType::GATHER:
	{
		if (m_eSCVState == ESCVState::CONSTRUCT) { break; }

		SetSCVState(ESCVState::MOVE_TO_GATHER);
		m_eCommandType = static_cast<CGather*>(pCmd)->m_eCommandType;
		m_tMnrlTile = static_cast<CGather*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CGather*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CGather*>(pCmd)->m_pTarget;

		CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tMnrlTile);
		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}

		// 충돌 레이어를 재설정합니다.
		pRectCollider->SetCollisionType(ECollisionType::GATHER);
		pRectCollider->ResetCollisionFlag();
		pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
		pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
		pRectCollider->InsertCollisionFlag(ECollisionType::GAS);
	}
	break;

	case ECommandType::CANCEL:
	{
		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		m_pTarget = nullptr;
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CSCV::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eSCVState)
	{
	case ESCVState::STOP:
	{
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
	}
	break;

	case ESCVState::MOVE:
	{
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);

		if (!m_queOptimalPath.empty())
		{
			Vector2Int tDstTilePosition = m_queOptimalPath.front();
			m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

			Vector2 direction = m_tDstPosition - m_tPosition;
			if (direction.Magnitude() < 1.0f)
			{
				m_queOptimalPath.pop();
				break;
			}

			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
		}
		else
		{
			SetSCVState(ESCVState::STOP);
		}
	}
	break;

	case ESCVState::MOVE_TO_GATHER:
	{
		// 미네랄이 있는 곳까지 움직인다.
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
		if (!m_queOptimalPath.empty())
		{
			Vector2Int tDstTilePosition = m_queOptimalPath.front();
			m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

			Vector2 direction = m_tDstPosition - m_tPosition;
			if (direction.Magnitude() < 1.0f)
			{
				m_queOptimalPath.pop();
				break;
			}

			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
		}
		else
		{
			SetSCVState(ESCVState::STOP);
		}
	}
	break;

	case ESCVState::GATHER:
	{
		CMineral* pMineral = dynamic_cast<CMineral*>(m_pTarget);
		if (pMineral->GetIsOccupied())
		{
			// 기다린다.
		}

		SetAnimation(m_pUnitAttckAnim[(int32)m_eDirectionState]);
		pMineral->SetIsOccupied(true);

		// TODO: 용접 애니메이션을 출력한다.
		SetCurHitingAnim(m_pUnitHitingAnim[(int32)m_eDirectionState]);
		SetHitingPosition(m_tPosition);

		// TODO: 용접 소리를 출력한다.

		m_fSumGthrMnrlDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_fSumGthrMnrlDeltaSeconds >= 3.0f)
		{
			SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
			m_bPlayHitingAnim = false;
			SetCurHitingAnim(nullptr);

			// TODO: 미네랄 덩이 스프라이트를 출력한다.
			m_pCurResourceSprite = m_pMineralOrb;


			pMineral->DecreaseMineral(8);
			pMineral->SetIsOccupied(false);
			
			// 커맨드 센터가 없는 경우
			if (CGameManager::GetManager()->GetCmdCntrTilePosition().empty()) { SetSCVState(ESCVState::STOP); break; }

			// 가장 가까운 커맨드 센터를 구한다.
			float fMinDistance = 8192.0f;
			Vector2Int tCurTilePosition = CGeometry::ToTilePosition(m_tPosition);

			std::vector<Vector2Int>& tTilePositions = CGameManager::GetManager()->GetCmdCntrTilePosition();
			for (const auto& tTilePosition : tTilePositions)
			{
				float fDistance = abs(tCurTilePosition.m_iX - tTilePosition.m_iX) + abs(tCurTilePosition.m_iY - tTilePosition.m_iY);
				if (fDistance < fMinDistance)
				{
					fMinDistance = fDistance;
					m_tCmdCntrTile = tTilePosition;
				}
			}

			CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tCmdCntrTile);
			if (!m_queOptimalPath.empty()) { m_queOptimalPath.pop(); }

			SetSCVState(ESCVState::RETURN_CARGO);
			m_fSumGthrMnrlDeltaSeconds = 0.0f;
		}
	}
	break;

	case ESCVState::RETURN_CARGO:
	{
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
		if (!m_queOptimalPath.empty())
		{
			Vector2Int tDstTilePosition = m_queOptimalPath.front();
			m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

			Vector2 direction = m_tDstPosition - m_tPosition;
			if (direction.Magnitude() < 1.0f)
			{
				m_queOptimalPath.pop();
				break;
			}

			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
		}
		else
		{
			SetSCVState(ESCVState::STOP);
		}
	}

	case ESCVState::ATTACK:
	{

	}
	break;

	case ESCVState::BUILD:
	{
		// 건물을 건설할 곳으로 이동합니다.
		if (!m_queOptimalPath.empty())
		{
			SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
			Vector2Int tDstTilePosition = m_queOptimalPath.front();
			m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

			Vector2 direction = m_tDstPosition - m_tPosition;
			if (direction.Magnitude() < 1.0f)
			{
				m_queOptimalPath.pop();
				break;
			}

			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
			break;
		}

		// SCV가 건설하는 방향을 맞춥니다.
		switch (m_iBuildDirection)
		{
		case 0: SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST]); break;
		case 1: SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST]); break;
		case 2: SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST]); break;
		case 3: SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST]); break;

		default:
		break;
		}

		pRectCollider->SetCollisionType(ECollisionType::BUILD);
		pRectCollider->ResetCollisionFlag();
		pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
		pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
		pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
		pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

		switch (m_eCommandType)
		{
		case ECommandType::BUILD_COMMAND_CENTER:
		{
			CCommandCenter* pCommandCenter = new CCommandCenter(*m_pCommandCenterProperty);
			
			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pCommandCenterProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pCommandCenterProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pCommandCenter->SetOwnerType(EOwnerType::PLAYER);
			pCommandCenter->SetPosition(tPosition);
			pCommandCenter->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pCommandCenter);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pCommandCenterProperty->GetMineral());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pCommandCenterProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		}
		break;

		case ECommandType::BUILD_SUPPLY_DEPOT:
		{
			CSupplyDepot* pSupplyDepotObject = new CSupplyDepot(*m_pSupplyDepotProperty);
			pSupplyDepotObject->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pSupplyDepotProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pSupplyDepotProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pSupplyDepotObject->SetPosition({ tPosition });
			pSupplyDepotObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pSupplyDepotObject);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pSupplyDepotProperty->GetMineral());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pSupplyDepotProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_REFINERY:
		{
			CRefinery* pRefinery = new CRefinery(*m_pRefineryProperty);
			pRefinery->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pRefineryProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pRefineryProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pRefinery->SetPosition({ tPosition });
			pRefinery->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pRefinery);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pRefineryProperty->GetMineral());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pRefineryProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_BARRACKS:
		{
			CBarracks* pBarracksObject = new CBarracks(*m_pBarracksProperty);
			pBarracksObject->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pBarracksProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pBarracksProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pBarracksObject->SetPosition({ tPosition });
			pBarracksObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pBarracksObject);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pBarracksProperty->GetMineral());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pBarracksProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_ENGINEERING_BAY:
		{
			CEngineeringBay* pEngineeringBay = new CEngineeringBay(*m_pEngineeringBayProperty);
			pEngineeringBay->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pEngineeringBayProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pEngineeringBayProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pEngineeringBay->SetPosition({ tPosition });
			pEngineeringBay->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pEngineeringBay);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pEngineeringBayProperty->GetMineral());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pEngineeringBayProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_ACADEMY:
		{
			CAcademy* pAcademyObject = new CAcademy(*m_pAcademyProperty);
			pAcademyObject->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pAcademyProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pAcademyProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pAcademyObject->SetPosition({ tPosition });
			pAcademyObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pAcademyObject);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pAcademyProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pAcademyProperty->GetGas());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pAcademyProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_FACTORY:
		{
			CFactory* pFactory = new CFactory(*m_pFactoryProperty);
			pFactory->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pFactoryProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pFactoryProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pFactory->SetPosition({ tPosition });
			pFactory->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pFactory);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pFactoryProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pFactoryProperty->GetGas());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pFactoryProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_ARMORY:
		{
			CArmory* pArmory = new CArmory(*m_pArmoryProperty);
			pArmory->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pArmoryProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pArmoryProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pArmory->SetPosition({ tPosition });
			pArmory->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pArmory);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pArmoryProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pArmoryProperty->GetGas());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pArmoryProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_STARPORT:
		{
			CStarport* pStarport = new CStarport(*m_pStarportProperty);
			pStarport->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pStarportProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pStarportProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pStarport->SetPosition({ tPosition });
			pStarport->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pStarport);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pStarportProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pStarportProperty->GetGas());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pStarportProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;

		case ECommandType::BUILD_SCIENCE_FACILITY:
		{
			CScienceFacility* pScienceFacility = new CScienceFacility(*m_pScienceFacilityProperty);
			pScienceFacility->SetOwnerType(EOwnerType::PLAYER);

			Vector2 tLeftTop = { m_tDstTile.m_iX * FTILECX, m_tDstTile.m_iY * FTILECY };
			Vector2 tOffset = { (float)m_pScienceFacilityProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pScienceFacilityProperty->GetTileSize().m_iY * FTILECY * 0.5f };
			Vector2 tPosition = tLeftTop + tOffset;

			pScienceFacility->SetPosition({ tPosition });
			pScienceFacility->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pScienceFacility);

			CGameManager::GetManager()->IncreaseProducedMineral(-m_pScienceFacilityProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(-m_pScienceFacilityProperty->GetGas());

			CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
			pDynamicTilemapObject->InsertDynamicTiles(m_tDstTile, m_pStarportProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });
		}
		break;
		}

		SetSCVState(ESCVState::CONSTRUCT);
	}
	break;

	case ESCVState::CONSTRUCT:
	{
		m_fSumCnstrctDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		SetCurHitingAnim(m_pUnitHitingAnim[(int32)m_eDirectionState]);

		Vector2 tDirVector(0.0f, 0.0f);

		// SCV가 건설하는 방향을 맞춥니다.
		switch (m_iBuildDirection)
		{
		case 0: tDirVector = { 4.0f, 1.0f }; break;
		case 1: tDirVector = { 4.0f, -1.0f }; break;
		case 2: tDirVector = { -4.0f, -1.0f }; break;
		case 3: tDirVector = { -4.0f, 1.0f }; break;

		default:
			break;
		}
		tDirVector.Normalize();
		SetHitingPosition(m_tPosition + tDirVector * 16.0f);

		if (m_fSumCnstrctDeltaSeconds >= 3.0f)
		{
			CSoundManager::GetManager()->PlaySoundEx(L"tscupd00.wav", ESoundChannel::UNIT, 1.0f);
			SetSCVState(ESCVState::STOP);
			m_bPlayHitingAnim = false;
			SetCurHitingAnim(nullptr);

			pRectCollider->SetCollisionType(ECollisionType::GROUND_UNIT);
			pRectCollider->ResetCollisionFlag();
			pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
			pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
			pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
			pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
			pRectCollider->InsertCollisionFlag(ECollisionType::GAS);
			m_fSumCnstrctDeltaSeconds = 0.0f;
		}
	}
	break;

	case ESCVState::DIE:
	{
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tscdth00.wav", ESoundChannel::UNIT, 1.0f);

			// 동적 타일맵을 불러옵니다.
			CTilemapObject* pObject = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pObject);

			// 동적 타일맵 정보를 갱신합니다.
			Vector2Int tTileSize = m_unitProperty.GetTileSize();
			pDynamicTilemapObject->EraseDynamicTiles(m_tPrevTilePosition, tTileSize, { ETileType::PASSABLE, EOwnerType::NEUTRAL });

			// 소비하는 보급품을 감소시킵니다.
			if (GetOwnerType() == EOwnerType::PLAYER)
			{
				CGameManager::GetManager()->IncreaseConsumedSupply(-m_unitProperty.GetConsumeSupply());
			}
			m_bDeadHandle = true;
		}

		m_fDeadDelay += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_fDeadDelay > 4.0f)
		{
			SetReady2Delete(true);
		}
	}
	break;
	}
}

void CSCV::RenderResource(HDC _hDC)
{
	// 스프라이트를 렌더합니다.
	VERIFY_NULLPTR(m_pCurResourceSprite);
	tagSpriteInfo tSpriteInfo = m_pCurResourceSprite->GetSpriteInfo();

	Vector2Int tSize = tSpriteInfo.m_tSize;
	Vector2Int tPosition = tSpriteInfo.m_tPosition;
	uint32 uiAlpha = m_pCurResourceSprite->GetTextureAlpha();

	// 스크롤된 위치를 구합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		::BitBlt(_hDC,																				// 사본 이미지의 DC
			(int32)(m_tOrbPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),	// 사본 이미지에서 원본 이미지가 렌더될 좌상단 위치
			(int32)(m_tOrbPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
			tSize.m_iWidth,																			// 원본 이미지의 밑변
			tSize.m_iHeight,																		// 원본 이미지의 높이
			m_pCurResourceSprite->GetTextureDC(),																// 원본 이미지의 DC
			tPosition.m_iX,																			// 원본 이미지의 좌상단 위치
			tPosition.m_iY,
			SRCCOPY);
	}
	else
	{
		GdiTransparentBlt(_hDC,
			(int32)(m_tOrbPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
			(int32)(m_tOrbPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
			tSize.m_iWidth,
			tSize.m_iHeight,
			m_pCurResourceSprite->GetTextureDC(),
			tPosition.m_iX,
			tPosition.m_iY,
			tSize.m_iWidth,
			tSize.m_iHeight,
			uiAlpha);
	}
}

void CSCV::UpdateOrbPosition()
{
	switch (m_eDirectionState)
	{
	case EDirectionState::NORTH_WEST:
	{
		Vector2 tNormal = { -1.0f, -1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;

	case EDirectionState::NORTH:
	{
		Vector2 tNormal = { 0.0f, -1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;

	case EDirectionState::NORTH_EAST:
	{
		Vector2 tNormal = { +1.0f, -1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;
	
	case EDirectionState::EAST:
	{
		Vector2 tNormal = { +1.0f, 0.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;
	
	case EDirectionState::SOUTH_EAST:
	{
		Vector2 tNormal = { +1.0f, +1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;
	
	case EDirectionState::SOUTH:
	{
		Vector2 tNormal = { 0.0f, +1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;

	case EDirectionState::SOUTH_WEST:
	{
		Vector2 tNormal = { -1.0f, +1.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;
	
	case EDirectionState::WEST:
	{
		Vector2 tNormal = { -1.0f, 0.0f };
		tNormal.Normalize();
		m_tOrbPosition = m_tPosition + tNormal * 15;
	}
	break;
	}
}
