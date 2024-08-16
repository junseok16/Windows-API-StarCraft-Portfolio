#include "pch.h"
#include "SiegeTank.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "AStarManager.h"

#include "Animation.h"

#include "RectangleColliderComponent.h"
#include "UnitProperty.h"
#include "Command.h"
#include "Scene.h"
#include "Player.h"
#include "DynamicTilemapObject.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "TankProjectile.h"
#include "SiegeTankProjectile.h"
using namespace std;

CSiegeTank::CSiegeTank(CUnitProperty& _tnkProperty, CUnitProperty& _sgTnkProperty) : CUnit(_tnkProperty), m_pSiegeTankProperty(_sgTnkProperty) {}

void CSiegeTank::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 40, 40 });
	SetGdiRender(true);

	// 마린에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 40, 40 });

	pRectCollider->SetCollisionType(ECollisionType::GROUND_UNIT);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
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
	{
		// 모드 변환
		m_pBdySiegeModingAnim = CResourceManager::GetManager()->GetAnimation(L"TnkBdySgMding");
		m_pBdyTankModingAnim = CResourceManager::GetManager()->GetAnimation(L"TnkBdyTnkMding");

		m_pHdSiegeModingAnim = CResourceManager::GetManager()->GetAnimation(L"TnkHdSgMding");
		m_pHdTankModingAnim = CResourceManager::GetManager()->GetAnimation(L"TnkHdTnkMding");

		// 일반 모드
		m_pTnkBdyStopAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopE");
		m_pTnkBdyStopAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopNE");
		m_pTnkBdyStopAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopN");
		m_pTnkBdyStopAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopNW");
		m_pTnkBdyStopAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopW");
		m_pTnkBdyStopAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopSW");
		m_pTnkBdyStopAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopS");
		m_pTnkBdyStopAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyStopSE");

		m_pTnkBdyMoveAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveE");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveNE");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveN");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveNW");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveW");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveSW");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveS");
		m_pTnkBdyMoveAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkBdyMoveSE");

		m_pTankBdyDieAnim = CResourceManager::GetManager()->GetAnimation(L"BangM");

		m_pTnkHdStpRotAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotE");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotNE");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotN");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotNW");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotW");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotSW");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotS");
		m_pTnkHdStpRotAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"TnkHdStopRotSE");

		m_pTnkHdDieAnim = CResourceManager::GetManager()->GetAnimation(L"TnkHdDie");

		// 시즈 모드
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopE");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopNE");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopN");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopNW");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopW");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopSW");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopS");
		m_pSgTnkBdyStpAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkBdyStopSE");

		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotE");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::NORTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotNE");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotN");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::NORTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotNW");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotW");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::SOUTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotSW");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotS");
		m_pSgTnkHdStpRotAnim[(int32)EDirectionState::SOUTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdStpRotSE");


		// 탱크 모드 포신 공격
		m_pTnkHdHtngAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngE");
		m_pTnkHdHtngAnim[(int32)EDirectionState::NORTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngNE");
		m_pTnkHdHtngAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngN"); 
		m_pTnkHdHtngAnim[(int32)EDirectionState::NORTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngNW");
		m_pTnkHdHtngAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngW");
		m_pTnkHdHtngAnim[(int32)EDirectionState::SOUTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngSW");
		m_pTnkHdHtngAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngS"); 
		m_pTnkHdHtngAnim[(int32)EDirectionState::SOUTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"TnkHdHtngSE"); 

		// 탱크 모드 포신 피격
		m_pTnkHdHtedAnim = CResourceManager::GetManager()->GetAnimation(L"TnkHdHted");

		// 시즈 모드 포신 공격
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngE");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngNE");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngN");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngNW");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngW");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngSW");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngS");
		m_pSgTnkHdHtngAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHtngSE");

		// 시즈 모드 포신 피격
		m_pSgTnkHdHtedAnim = CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHted");

		// 그외
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"SgTnkPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"TnkBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"TnkSmllWrfrm5");

		SetAnimation(m_pTnkBdyStopAnim[(int32)EDirectionState::SOUTH]);
		SetHdAnimation(m_pTnkHdStpRotAnim[(int32)EDirectionState::SOUTH]);
	}


	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct4"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(36.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::GROUND_UNIT);
	SetUnitAtributeType(EUnitAttributeType::MECHANICAL);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::MOVE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::STOP);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ATTACK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::SIEGE_MODE);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::STOP);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::ATTACK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::TANK_MODE);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

	/********************
		Unit 클래스
	********************/
	SetCurHP(m_unitProperty.GetMaxHP());
	SetCurMP(m_unitProperty.GetMaxMP());
	SetCurShield(m_unitProperty.GetMaxShield());
	SetCurSpeed(m_unitProperty.GetSpeed());
	SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds());
	SetTerranUnitType(ETerranUnitType::TANK);

	/********************
		Marine 클래스
	********************/
	SetSiegeTankState(ESiegeTankState::STOP);
}

void CSiegeTank::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	
	UpdateBarrelAnim();
	UpdateBarrelPosition();
	AnalyseCommand();
	UpdateDirection();
	ExecuteCommand();
}

void CSiegeTank::LateUpdate()
{
	CUnit::LateUpdate();
}

void CSiegeTank::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
	RenderBarrel(_hDC);
}

void CSiegeTank::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CSiegeTank::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CSiegeTank::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CSiegeTank::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CSiegeTank::UpdateDirection()
{
	Vector2 tBdyDirection{ 0.0f, 0.0f };
	Vector2 tHdDirection{ 0.0f, 0.0f };

	switch (m_eSiegeTankState)
	{
	case ESiegeTankState::STOP:
	{
		tBdyDirection = m_tDstPosition - m_tPosition;
		tHdDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case ESiegeTankState::MOVE:
	{
		if (m_pTarget == nullptr)
		{
			tBdyDirection = m_tDstPosition - m_tPosition;
			tHdDirection = m_tDstPosition - m_tPosition;
		}
		else
		{
			// 상대 오브젝트가 죽은 경우
			CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(m_pTarget);
			if (pTerranObject->GetDead())
			{
				m_pTarget = nullptr;
				tBdyDirection = m_tDstPosition - m_tPosition;
				tHdDirection = m_tDstPosition - m_tPosition;
				break;
			}

			tBdyDirection = m_tDstPosition - m_tPosition;
			tHdDirection = m_pTarget->GetPosition() - m_tPosition;
		}
	}
	break;

	case ESiegeTankState::ATTACK:
	{
		if (m_pTarget == nullptr)
		{
			tBdyDirection = m_tDstPosition - m_tPosition;
			tHdDirection = m_tDstPosition - m_tPosition;
		}
		else
		{
			tBdyDirection = m_tDstPosition - m_tPosition;
			tHdDirection = m_pTarget->GetPosition() - m_tPosition;
		}
	}
	break;

	case ESiegeTankState::TO_SIEGE_MODE:
	case ESiegeTankState::TO_TANK_MODE:
	{
		tBdyDirection = Vector2(1.0f, 1.0f);
		tHdDirection = Vector2(1.0f, 1.0f);
	}
	break;

	default:
	break;
	}

	tBdyDirection.Normalize();
	tHdDirection.Normalize();
	m_fDegree = acosf(tBdyDirection.m_fX) * 180.0f / PI;
	m_iHdDegree = acosf(tHdDirection.m_fX) * 180.0f / PI;

	// 탱크 몸체 각도
	if		( 0.0f <= m_fDegree && m_fDegree < 22.5f)
	{
		m_eDirectionState = EDirectionState::EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f &&  tBdyDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f &&  tBdyDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_EAST;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tBdyDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tBdyDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH;
	}
	else if (112.5f <= m_fDegree && m_fDegree < 157.5f && tBdyDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_WEST;
	}
	else if (112.5f <= m_fDegree && m_fDegree < 157.5f && tBdyDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_WEST;
	}
	else if (157.5f <= m_fDegree && m_fDegree < 181.0f)
	{
		m_eDirectionState = EDirectionState::WEST;
	}

	// 탱크 포신 각도
	if (0.0f <=  m_iHdDegree && m_iHdDegree < 22.5f)
	{
		m_eTnkHdDirectionState = EDirectionState::EAST;
		m_tHdNormalVector = { 1.0f, 0.0f };
	}
	else if (22.5f <=  m_iHdDegree && m_iHdDegree < 67.5f &&  tHdDirection.m_fY < 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::NORTH_EAST;
		m_tHdNormalVector = { 1.0f, -1.0f };
	}
	else if (22.5f <=  m_iHdDegree && m_iHdDegree < 67.5f &&  tHdDirection.m_fY > 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::SOUTH_EAST;
		m_tHdNormalVector = { 1.0f, 1.0f };
	}
	else if (67.5f <=  m_iHdDegree && m_iHdDegree < 112.5f && tHdDirection.m_fY < 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::NORTH;
		m_tHdNormalVector = { 0.0f, -1.0f };
	}
	else if (67.5f <=  m_iHdDegree && m_iHdDegree < 112.5f && tHdDirection.m_fY > 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::SOUTH;
		m_tHdNormalVector = { 0.0f, 1.0f };
	}
	else if (112.5f <= m_iHdDegree && m_iHdDegree < 157.5f && tHdDirection.m_fY < 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::NORTH_WEST;
		m_tHdNormalVector = { -1.0f, -1.0f };
	}
	else if (112.5f <= m_iHdDegree && m_iHdDegree < 157.5f && tHdDirection.m_fY > 0.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::SOUTH_WEST;
		m_tHdNormalVector = { -1.0f, 1.0f };
	}
	else if (157.5f <= m_iHdDegree && m_iHdDegree < 181.0f)
	{
		m_eTnkHdDirectionState = EDirectionState::WEST;
		m_tHdNormalVector = { -1.0f, 0.0f };
	}
}

void CSiegeTank::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetSiegeTankState(ESiegeTankState::DIE);
		m_pTarget = nullptr;
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eSiegeTankState == ESiegeTankState::TO_SIEGE_MODE) { break; }
		if (m_eSiegeTankState == ESiegeTankState::TO_TANK_MODE) { break; }

		// 탱크 모드인 경우
		if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
		{
			SetSiegeTankState(ESiegeTankState::MOVE);
			m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
			m_tDstTile = static_cast<CMove*>(pCmd)->m_tDstTile;
			//m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;

			CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tDstTile);
			if (!m_queOptimalPath.empty())
			{
				m_queOptimalPath.pop();
			}
		}
		// 시즈 모드인 경우
		else
		{
			SetSiegeTankState(ESiegeTankState::STOP);
		}
	}
	break;

	case ECommandType::STOP:
	{
		if (m_eSiegeTankState == ESiegeTankState::TO_SIEGE_MODE) { break; }
		if (m_eSiegeTankState == ESiegeTankState::TO_TANK_MODE) { break; }

		SetSiegeTankState(ESiegeTankState::STOP);
	}
	break;

	case ECommandType::ATTACK:
	{
		if (m_eSiegeTankState == ESiegeTankState::TO_SIEGE_MODE) { break; }
		if (m_eSiegeTankState == ESiegeTankState::TO_TANK_MODE) { break; }

		// 탱크 모드인 경우
		if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
		{
			SetSiegeTankState(ESiegeTankState::ATTACK);
			m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
			m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
			m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;

			CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tDstTile);
			if (!m_queOptimalPath.empty())
			{
				m_queOptimalPath.pop();
			}
		}
		// 시즈 모드인 경우
		else
		{
			SetSiegeTankState(ESiegeTankState::ATTACK);
			m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
			m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
			m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;
		}
	}
	break;

	case ECommandType::SIEGE_MODE:
	{
		if (m_eSiegeTankState == ESiegeTankState::TO_SIEGE_MODE) { break; }
		if (m_eSiegeTankState == ESiegeTankState::TO_TANK_MODE) { break; }

		SetSiegeTankState(ESiegeTankState::TO_SIEGE_MODE);
		m_tDstPosition = m_tPosition;
	}
	break;

	case ECommandType::TANK_MODE:
	{
		if (m_eSiegeTankState == ESiegeTankState::TO_SIEGE_MODE) { break; }
		if (m_eSiegeTankState == ESiegeTankState::TO_TANK_MODE) { break; }

		SetSiegeTankState(ESiegeTankState::TO_TANK_MODE);
		m_tDstPosition = m_tPosition;
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CSiegeTank::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eSiegeTankState)
	{
	/****************
		시즈 모드 명령
	****************/
	case ESiegeTankState::TO_SIEGE_MODE:
	{
		SetSiegeTankMode(ESiegeTankMode::SIEGE_MODE);
		m_fBdySgMdDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_fBdySgMdDeltaSeconds < 1.4f)
		{
			if (m_bPlayBdySgMd == false)
			{
				CSoundManager::GetManager()->PlaySoundEx(L"ttatra01.wav", ESoundChannel::UNIT, 1.0f);
				m_bPlayBdySgMd = true;
			}
			SetAnimation(m_pBdySiegeModingAnim);
			SetHdAnimation(m_pTnkHdStpRotAnim[(int32)EDirectionState::SOUTH_EAST]);
		}
		else if (m_fBdySgMdDeltaSeconds >= 1.4f)
		{
			SetHdAnimation(m_pHdSiegeModingAnim);
			if (m_bPlayHdSgMd == false)
			{
				CSoundManager::GetManager()->PlaySoundEx(L"ttatra00.wav", ESoundChannel::UNIT, 1.0f);
				m_bPlayHdSgMd = true;
			}

			m_fHdSgMdDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
			if (m_fHdSgMdDeltaSeconds >= 2.0f)
			{
				SetSiegeTankState(ESiegeTankState::STOP);
				m_fBdySgMdDeltaSeconds = 0.0f;
				m_fHdSgMdDeltaSeconds = 0.0f;
				m_bPlayBdySgMd = false;
				m_bPlayHdSgMd = false;
			}
		}
	}
	break;

	/****************
		탱크 모드 명령
	****************/
	case ESiegeTankState::TO_TANK_MODE:
	{
		m_fHdSgMdDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_fHdSgMdDeltaSeconds < 2.0f)
		{
			if (m_bPlayHdSgMd == false)
			{
				CSoundManager::GetManager()->PlaySoundEx(L"ttatra00.wav", ESoundChannel::UNIT, 1.0f);
				m_bPlayHdSgMd = true;
			}
			SetHdAnimation(m_pHdTankModingAnim);
		}
		else if (m_fHdSgMdDeltaSeconds >= 2.0f)
		{
			SetAnimation(m_pBdyTankModingAnim);
			if (m_bPlayBdySgMd == false)
			{
				CSoundManager::GetManager()->PlaySoundEx(L"ttatra01.wav", ESoundChannel::UNIT, 1.0f);
				m_bPlayBdySgMd = true;
			}

			m_fBdySgMdDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
			if (m_fBdySgMdDeltaSeconds >= 1.4f)
			{
				SetSiegeTankState(ESiegeTankState::STOP);
				m_fBdySgMdDeltaSeconds = 0.0f;
				m_fHdSgMdDeltaSeconds = 0.0f;
				m_bPlayBdySgMd = false;
				m_bPlayHdSgMd = false;
				SetSiegeTankMode(ESiegeTankMode::TANK_MODE);
			}
		}
	}
	break;

	case ESiegeTankState::STOP:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);

		// 탱크 모드인 경우
		if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
		{
			SetAnimation(m_pTnkBdyStopAnim[(int32)m_eDirectionState]);
			SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
			m_tDstPosition = m_tPosition;
			AlertAround(m_unitProperty);
		}

		// 시즈 모드인 경우
		else
		{
			SetHdAnimation(m_pSgTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
			m_tDstPosition = m_tPosition;
			AlertAround(m_pSiegeTankProperty);
		}
	}
	break;

	case ESiegeTankState::MOVE:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);

		if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
		{
			SetAnimation(m_pTnkBdyMoveAnim[(int32)m_eDirectionState]);
			SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);

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
				SetSiegeTankState(ESiegeTankState::STOP);
			}
		}
	}
	break;

	case ESiegeTankState::ATTACK:
	{
		// 탱크 모드인 경우
		if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
		{
			// 목표가 없는 경우
			if (m_pTarget == nullptr)
			{
				SetCurHitingAnim(nullptr);
				//SetCurHitedAnim(nullptr);
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

					// 주변을 경계한다.
					SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
					AlertAround(m_unitProperty);
				}
				else
				{
					SetSiegeTankState(ESiegeTankState::STOP);
				}
				break;
			}

			// 상대 오브젝트가 죽은 경우
			if (m_pTarget->GetDead())
			{
				SetCurHitingAnim(nullptr);
				//SetCurHitedAnim(nullptr);
				SetSiegeTankState(ESiegeTankState::STOP);
				SetTarget(nullptr);
				break;
			}

			// 목표가 있는 경우
			else
			{
				// 사거리보다 짧은 경우
				if (m_tPosition.Distance(m_pTarget->GetPosition()) <= m_unitProperty.GetRange())
				{
					m_fSumAttackMoveDeltaSeconds = 0.0f;

					SetAnimation(m_pTnkBdyStopAnim[(int32)m_eDirectionState]);
					SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);

					// 공격 주기가 되었을 때
					if (m_fSumAttackDeltaSeconds >= m_unitProperty.GetAttackDeltaSeconds())
					{
						CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

						// 목표의 체력이 0보다 클 때, 공격한다.
						if (pTarget->GetCurHP() > 0)
						{
							CSoundManager::GetManager()->PlaySoundEx(L"ttafir00.wav", ESoundChannel::UNIT, 1.0f);
							
							SetCurHitingAnim(m_pTnkHdHtngAnim[(int32)m_eTnkHdDirectionState]);
							//SetCurHitedAnim(m_pTnkHdHtedAnim);
							
							{
								// 투사체를 생성합니다.
								CTankProjectile* pProjectile = new CTankProjectile();
								pProjectile->SetPosition(m_tPosition);
								pProjectile->SetTarget(pTarget);
								pProjectile->SetDirectionState(m_eDirectionState);
								pProjectile->Initialize();
								CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
							}

							Vector2 tDirVector = m_pTarget->GetPosition() - m_tPosition;
							tDirVector.Normalize();

							SetHitingPosition(m_tHdPosition);
							m_fSumAttackDeltaSeconds = 0.0f;
						}
						else
						{
							SetCurHitingAnim(nullptr);
							//SetCurHitedAnim(nullptr);
							SetSiegeTankState(ESiegeTankState::STOP);
							SetAnimation(m_pTnkBdyStopAnim[(int32)m_eDirectionState]);
							SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
							m_pTarget = nullptr;
						}
					}
					else
					{
						SetCurHitingAnim(nullptr);
						//SetCurHitedAnim(nullptr);
					}
				}
				// 사거리보다 먼 경우
				else
				{
					SetCurHitingAnim(nullptr);
					//SetCurHitedAnim(nullptr);

					m_tDstPosition = m_pTarget->GetPosition();

					m_fSumAttackMoveDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
					if (m_fSumAttackMoveDeltaSeconds <= 0.5f)
					{
						SetAnimation(m_pTnkBdyStopAnim[(int32)m_eDirectionState]);
						SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
						break;
					}

					// 목표가 있는 곳으로 이동한다.
					SetAnimation(m_pTnkBdyMoveAnim[(int32)m_eDirectionState]);
					SetHdAnimation(m_pTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);

					Vector2 direction = m_pTarget->GetPosition() - m_tPosition;
					direction.Normalize();
					m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
				}
			}
		}

		// 시즈 모드인 경우
		else
		{
			// 목표가 없는 경우
			if (m_pTarget == nullptr)
			{
				SetCurHitingAnim(nullptr);
				//SetCurHitedAnim(nullptr);
				SetSiegeTankState(ESiegeTankState::STOP);
				break;
			}

			// 목표가 죽은 경우
			else if (m_pTarget->GetDead())
			{
				SetCurHitingAnim(nullptr);
				//SetCurHitedAnim(nullptr);
				SetSiegeTankState(ESiegeTankState::STOP);
				SetTarget(nullptr);
				break;
			}

			// 목표가 살아있는 경우
			else
			{
				// 사거리보다 짧은 경우
				if (m_tPosition.Distance(m_pTarget->GetPosition()) <= m_pSiegeTankProperty.GetRange())
				{
					m_fSumAttackMoveDeltaSeconds = 0.0f;
					
					SetHdAnimation(m_pSgTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);

					// 공격 주기가 되었을 때
					if (m_fSumAttackDeltaSeconds >= m_pSiegeTankProperty.GetAttackDeltaSeconds())
					{
						CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

						// 목표의 체력이 0보다 클 때, 공격한다.
						if (pTarget->GetCurHP() > 0)
						{
							CSoundManager::GetManager()->PlaySoundEx(L"ttafi200.wav", ESoundChannel::UNIT, 1.0f);
							
							{
								// 투사체를 생성합니다.
								CSiegeTankProjectile* pProjectile = new CSiegeTankProjectile();
								pProjectile->SetPosition(m_tPosition);
								pProjectile->SetTarget(pTarget);
								pProjectile->SetDirectionState(m_eDirectionState);
								pProjectile->Initialize();
								CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
							}

							SetCurHitingAnim(m_pSgTnkHdHtngAnim[(int32)m_eTnkHdDirectionState]);
							//SetCurHitedAnim(m_pSgTnkHdHtedAnim);

							m_tHdNormalVector.Normalize();
							SetHitingPosition(m_tHdPosition + m_tHdNormalVector * 30.0f);
							//SetHitedPosition(m_pTarget->GetPosition());

							/*
							if (pTarget->GetAttacked(m_pSiegeTankProperty.GetAttackPoint()) == true)
							{
								SetCurHitingAnim(nullptr);
								//SetCurHitedAnim(nullptr);
								pTarget->SetDead(true);

								SetSiegeTankState(ESiegeTankState::STOP);
								SetHdAnimation(m_pSgTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
								m_pTarget = nullptr;
							}
							*/
							m_fSumAttackDeltaSeconds = 0.0f;
						}
						else
						{
							SetCurHitingAnim(nullptr);
							//SetCurHitedAnim(nullptr);
							SetSiegeTankState(ESiegeTankState::STOP);
							SetHdAnimation(m_pSgTnkHdStpRotAnim[(int32)m_eTnkHdDirectionState]);
							m_pTarget = nullptr;
						}
					}
					else
					{
						SetCurHitingAnim(nullptr);
						//SetCurHitedAnim(nullptr);
					}
				}
				// 사거리보다 먼 경우
				else
				{
					SetCurHitingAnim(nullptr);
					//SetCurHitedAnim(nullptr);
					SetSiegeTankState(ESiegeTankState::STOP);
				}
			}
		}
	}
	break;

	case ESiegeTankState::DIE:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);
		SetAnimation(m_pTankBdyDieAnim);
		SetHdAnimation(m_pTnkHdDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"ttadth00.wav", ESoundChannel::UNIT, 1.0f);

			// 동적 타일맵을 불러옵니다.
			CTilemapObject* pObject = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
			CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pObject);

			// 동적 타일맵 정보를 갱신합니다.
			Vector2Int tTileSize = m_unitProperty.GetTileSize();
			pDynamicTilemapObject->EraseDynamicTiles(m_tPrevTilePosition, tTileSize, { ETileType::PASSABLE, EOwnerType::NONE });

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

	default:
	break;
	}
}

void CSiegeTank::UpdateBarrelAnim()
{
	// 애니메이션을 업데이트합니다.
	VERIFY_NULLPTR(m_pTnkHdAnim);
	tagAnimationInfo tAnimationInfo = m_pTnkHdAnim->GetAnimationInfo();

	pair<int32, int32> tXIndex{ 0, 0 };
	pair<int32, int32> tYIndex{ 0, 0 };
	int32 iNumSprite = 0;
	float fDeltaDuration = 0.0f;

	// 애니메이션의 인덱스를 갱신합니다.
	if (tAnimationInfo.m_bVertical == true)
	{
		// 애니메이션이 모두 한 열에만 나열되어 있다고 가정합니다.
		tYIndex = tAnimationInfo.m_tYIndex;
		iNumSprite = tYIndex.second - tYIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}
	else
	{
		// 애니메이션이 모두 한 행에만 나열되어 있다고 가정합니다.
		tXIndex = tAnimationInfo.m_tXIndex;
		iNumSprite = tXIndex.second - tXIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}


	m_fHdSumDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

	// 한 번만 애니메이션을 실행합니다.
	if (tAnimationInfo.m_bPlayOnce == true)
	{
		if (m_fHdSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHdSumDeltaSeconds = 0.0f;
			m_iHdOffset = (m_iHdOffset + 1) % iNumSprite;

			if (m_iHdOffset == 0) { m_iHdOffset = iNumSprite - 1; }
		}
	}
	// 반복해서 애니메이션을 실행합니다.
	else if (tAnimationInfo.m_bRepeat == true)
	{
		// 다음 스프라이트를 렌더하도록 오프셋을 증가시킵니다.
		if (m_fHdSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHdSumDeltaSeconds = 0.0f;
			m_iHdOffset = (m_iHdOffset + 1) % iNumSprite;
		}
	}
}

void CSiegeTank::UpdateBarrelPosition()
{
	Vector2 normalVector(0.0f, 0.0f);

	if (m_eSiegeTankMode == ESiegeTankMode::TANK_MODE)
	{
		switch (m_eDirectionState)
		{
		case EDirectionState::NORTH_WEST:
		{
			normalVector = { +0.8f, +0.2f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 8;
		}
		break;

		case EDirectionState::NORTH:
		{
			m_tHdPosition = m_tPosition;
		}
		break;

		case EDirectionState::NORTH_EAST:
		{
			normalVector = { -0.8f, +0.2f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 8;
		}
		break;

		case EDirectionState::EAST:
		{
			normalVector = { -1.0f, -0.4f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 10;
		}
		break;

		case EDirectionState::SOUTH_EAST:
		{
			normalVector = { -0.4f, -0.8f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 14;
		}
		break;

		case EDirectionState::SOUTH:
		{
			normalVector = { 0.0f, -1.0f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 10;
		}
		break;

		case EDirectionState::SOUTH_WEST:
		{
			normalVector = { +0.2f, -0.8f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 10;
		}
		break;

		case EDirectionState::WEST:
		{
			normalVector = { +1.0f, -0.4f };
			normalVector.Normalize();
			m_tHdPosition = m_tPosition + normalVector * 10;
		}
		break;

		case EDirectionState::ENUM_END:
		{

		}
		break;

		default:
			break;
		}
	}

	else
	{
		normalVector = { -0.4f, -0.8f };
		normalVector.Normalize();
		m_tHdPosition = m_tPosition + normalVector * 15;
	}
}

void CSiegeTank::RenderBarrel(HDC _hDC)
{
	VERIFY_NULLPTR(m_pTnkHdAnim);
	tagAnimationInfo tAnimationInfo = m_pTnkHdAnim->GetAnimationInfo();

	bool bVertical = tAnimationInfo.m_bVertical;
	Vector2Int tSize = tAnimationInfo.m_tSize;
	pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
	pair<int32, int32> tYIndex = tAnimationInfo.m_tYIndex;
	uint32 uiAlpha = m_pTnkHdAnim->GetTextureAlpha();

	// 카메라 위치를 구합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		// 행으로 나열된 애니메이션
		if (bVertical == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pTnkHdAnim->GetTextureDC(),
				(tXIndex.first + m_iHdOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				SRCCOPY);
		}
		// 열로 나열된 애니메이션
		else
		{
			::BitBlt(_hDC,
				(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pTnkHdAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHdOffset) * tSize.m_iHeight,
				SRCCOPY);
		}
	}
	else
	{
		// 행으로 나열된 애니메이션
		if (bVertical == false)
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pTnkHdAnim->GetTextureDC(),
				(tXIndex.first + m_iHdOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
		// 열로 나열된 애니메이션
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pTnkHdAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHdOffset) * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
}

void CSiegeTank::SetHdAnimation(CAnimation* _pHdAnimation)
{
	VERIFY_NULLPTR(_pHdAnimation);
	if (m_pTnkHdAnim == _pHdAnimation) { return; }
	m_pTnkHdAnim = _pHdAnimation;

	m_iHdOffset = 0;
	m_fHdSumDeltaSeconds = 0.0f;
}

void CSiegeTank::AlertAround(CUnitProperty& _unitProperty)
{
	float fMinDistance = 8192.0f;
	CTerranObject* pNearestObject = nullptr;

	list<CObject*>& lstUnits = CSceneManager::GetManager()->GetCurScene()->GetUnits();
	for (const auto& pUnit : lstUnits)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pUnit);
		if (pTerranObject == this) { continue; }
		if (pTerranObject->GetDead() == true) { continue; }
		if (pTerranObject->GetTerranObjectType() == ETerranObjectType::AIR_UNIT) { continue; }
		if (GetOwnerType() == EOwnerType::COMPUTER && pTerranObject->GetOwnerType() == EOwnerType::COMPUTER) { continue; }
		if (GetOwnerType() == EOwnerType::PLAYER && pTerranObject->GetOwnerType() == EOwnerType::PLAYER) { continue; }

		// 시야보다 짧은 경우
		Vector2 tEnemyPosition = pTerranObject->GetPosition();
		float fDistance = m_tPosition.Distance(tEnemyPosition);

		if (fDistance <= m_unitProperty.GetSight())
		{
			if (fDistance <= fMinDistance)
			{
				fMinDistance = fDistance;
				pNearestObject = pTerranObject;
			}
		}
	}

	if (pNearestObject != nullptr)
	{
		SetTarget(pNearestObject);
		SetSiegeTankState(ESiegeTankState::ATTACK);
	}
}
