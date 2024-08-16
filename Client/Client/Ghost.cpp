#include "pch.h"
#include "Ghost.h"
#include "RectangleColliderComponent.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "AStarManager.h"

#include "Command.h"
#include "UnitProperty.h"

#include "Scene.h"
#include "TerranObject.h"
#include "Player.h"
#include "DynamicTilemapObject.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"

#include "GhstProjectile.h"
#include "NuclearProjectile.h"
using namespace std;

CGhost::CGhost(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CGhost::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 20, 30 });
	SetGdiRender(true);

	// 고스트에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
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

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);


	/********************
		AnimationObject 클래스
	********************/
	{
		m_pUnitStopAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"GhstStopN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"GhstStopS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstStopSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstMoveSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstAttckSE");

		m_pNclrStrkAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkE");
		m_pNclrStrkAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkNE");
		m_pNclrStrkAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkN");
		m_pNclrStrkAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkNW");
		m_pNclrStrkAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkW");
		m_pNclrStrkAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkSW");
		m_pNclrStrkAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkS");
		m_pNclrStrkAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"GhstNclrStrkSE");


		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"GhstDie");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"GhstPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"GhstBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"GhstSmllWrfrm5");

		SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::SOUTH]);
	}
	

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::GROUND_UNIT);
	SetUnitAtributeType(EUnitAttributeType::BIOLOGICAL);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::MOVE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::STOP);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ATTACK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::USE_NUCLEAR_STRIKE);
	// TODO: 고스트 스킬
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct0"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(21.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	m_pMPBarUI = new CMPBarUI();
	m_pMPBarUI->SetUIActive(false);
	m_pMPBarUI->SetBarOwner(this);
	m_pMPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pMPBarUI->SetDistance(28.0f);
	m_pMPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pMPBarUI);

	/********************
		Unit 클래스
	********************/
	SetCurHP(m_unitProperty.GetMaxHP());
	SetCurMP(50);
	SetCurShield(m_unitProperty.GetMaxShield());
	SetCurSpeed(m_unitProperty.GetSpeed());
	SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds());
	SetTerranUnitType(ETerranUnitType::GHOST);
	
	/********************
		Ghost 클래스
	********************/
	SetGhostState(EGhostState::STOP);
}

void CGhost::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	RecoverMP();
	AnalyseCommand();
	UpdateDirection();
	ExecuteCommand();
}

void CGhost::LateUpdate()
{
	CUnit::LateUpdate();
}

void CGhost::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
}

void CGhost::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pMPBarUI);
}

void CGhost::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CGhost::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CGhost::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CGhost::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };

	switch (m_eGhostState)
	{
	case EGhostState::STOP:
	case EGhostState::MOVE:
	{
		tDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case EGhostState::ATTACK:
	case EGhostState::NUCLEAR_STRIKE:
	{
		if (m_pTarget == nullptr)
		{
			tDirection = m_tDstPosition - m_tPosition;
		}
		else
		{
			tDirection = m_pTarget->GetPosition() - m_tPosition;
		}
	}
	break;

	default:
		break;
	}

	tDirection.Normalize();
	m_fDegree = acosf(tDirection.m_fX) * 180.0f / PI;

	if (0.0f <= m_fDegree && m_fDegree < 22.5f)
	{
		m_eDirectionState = EDirectionState::EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_EAST;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH;
	}
	else if (112.5 <= m_fDegree && m_fDegree < 157.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_WEST;
	}
	else if (112.5 <= m_fDegree && m_fDegree < 157.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_WEST;
	}
	else if (157.5f <= m_fDegree && m_fDegree < 181.0f)
	{
		m_eDirectionState = EDirectionState::WEST;
	}
}

void CGhost::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetGhostState(EGhostState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (GetGhostState() == EGhostState::NUCLEAR_STRIKE) { break; }

		SetGhostState(EGhostState::MOVE);
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
		if (GetGhostState() == EGhostState::NUCLEAR_STRIKE) { break; }
		SetGhostState(EGhostState::STOP);
	}
	break;

	case ECommandType::ATTACK:
	{
		if (GetGhostState() == EGhostState::NUCLEAR_STRIKE) { break; }
		SetGhostState(EGhostState::ATTACK);
		m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;

		CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tDstTile);
		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}
	}
	break;

	case ECommandType::USE_NUCLEAR_STRIKE:
	{
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetGhostState(EGhostState::NUCLEAR_STRIKE);
		m_tDstTile = static_cast<CSkill*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CSkill*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CSkill*>(pCmd)->m_pTarget;

		CAStarManager::GetManager()->FindOptimalPath(m_queOptimalPath, m_vecOptimalPath, CGeometry::ToTilePosition(m_tPosition), m_tDstTile);
		if (!m_queOptimalPath.empty())
		{
			m_queOptimalPath.pop();
		}
	}
	break;

	// TODO: 락 다운
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CGhost::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eGhostState)
	{
	/****************
		정지 명령
	****************/
	case EGhostState::STOP:
	{
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
		AlertAround();
	}
	break;


	/****************
		이동 명령
	****************/
	case EGhostState::MOVE:
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
			SetGhostState(EGhostState::STOP);
		}
	}

	break;


	/****************
		공격 명령
	****************/
	case EGhostState::ATTACK:
	{
		// 목표가 없는 경우, 목표가 있는 곳으로 이동한다.
		if (m_pTarget == nullptr)
		{
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
				AlertAround();
			}
			else
			{
				SetGhostState(EGhostState::STOP);
			}
			break;
		}

		else if (m_pTarget->GetDead())
		{
			SetGhostState(EGhostState::STOP);
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
				
				// 공격 주기가 되었을 때
				if (m_fSumAttackDeltaSeconds >= m_fCurAttackDeltaSeconds)
				{
					SetAnimation(m_pUnitAttckAnim[(int32)m_eDirectionState]);
					CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

					// 목표의 체력이 0보다 클 때, 공격한다.
					if (pTarget->GetCurHP() > 0)
					{
						CSoundManager::GetManager()->PlaySoundEx(L"tghfir00.wav", ESoundChannel::UNIT, 1.0f);

						{
							// 투사체를 생성합니다.
							CGhstProjectile* pProjectile = new CGhstProjectile();
							pProjectile->SetPosition(m_tPosition);
							pProjectile->SetTarget(pTarget);
							pProjectile->SetDirectionState(m_eDirectionState);
							pProjectile->Initialize();
							CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
						}
						/*
						if (pTarget->GetAttacked(m_unitProperty.GetAttackPoint()) == true)
						{
							pTarget->SetDead(true);
							SetGhostState(EGhostState::STOP);
							SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
							m_pTarget = nullptr;
						}
						*/
						m_fSumAttackDeltaSeconds = 0.0f;
					}
					else
					{
						SetGhostState(EGhostState::STOP);
						SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
						m_pTarget = nullptr;
					}
				}
			}
			// 사거리보다 먼 경우
			else
			{
				m_fSumAttackMoveDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
				if (m_fSumAttackMoveDeltaSeconds <= 0.5f)
				{
					SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
					break;
				}

				// 목표가 있는 곳으로 이동한다.
				SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);

				Vector2 direction = m_pTarget->GetPosition() - m_tPosition;
				direction.Normalize();
				m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
			}
		}
	}
	break;


	/****************
		핵 공격 상태
	****************/
	case EGhostState::NUCLEAR_STRIKE:
	{
		if (m_pTarget->GetDead())
		{
			SetGhostState(EGhostState::STOP);
			SetTarget(nullptr);
			break;
		}


		// 사거리보다 짧은 경우
		if (m_tPosition.Distance(m_pTarget->GetPosition()) <= m_unitProperty.GetSight())
		{
			// TODO: 히팅 포인트 만들기
			SetAnimation(m_pNclrStrkAnim[(int32)m_eDirectionState]);
			CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

			if (!m_bUseNclrStrk)
			{
				// 보급품을 감소시킵니다.
				// 뉴클리어 업그레이드를 false로 만듭니다.
				CGameManager::GetManager()->IncreaseConsumedSupply(-8);
				CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::ARM_NUCLEAR_SILO, false);

				CSoundManager::GetManager()->PlaySoundEx(L"tghlas00.wav", ESoundChannel::UNIT, 1.0f);
				CSoundManager::GetManager()->PlaySoundEx(L"tnsfir00.wav", ESoundChannel::UNIT, 1.0f);
				m_bUseNclrStrk = true;
			}

			m_fNclrStrkDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
			if (m_fNclrStrkDeltaSeconds >= 2.0f && !m_bAlertNclrStrk)
			{
				CSoundManager::GetManager()->PlaySoundEx(L"tadupd04.wav", ESoundChannel::UNIT, 1.0f);
				m_bAlertNclrStrk = true;
			}

			if (m_fNclrStrkDeltaSeconds >= 8.0f)
			{
				{
					// 투사체를 생성합니다.
					CNuclearProjectile* pProjectile = new CNuclearProjectile();

					Vector2 tSpawnPosition = { m_pTarget->GetPosition().m_fX, m_pTarget->GetPosition().m_fY - 240.0f };
					pProjectile->SetPosition(tSpawnPosition);
					pProjectile->SetTarget(pTarget);
					pProjectile->SetDirectionState(m_eDirectionState);
					pProjectile->Initialize();
					CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
				}

				/*
				// 핵 공격 투사체를 생성합니다.
				CBtlcrsrYmtProjectile* pProjectile = new CBtlcrsrYmtProjectile();
				pProjectile->SetPosition(m_tPosition);
				pProjectile->SetTarget(pTarget);
				pProjectile->SetDirectionState(m_eDirectionState);
				pProjectile->Initialize();
				CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
				*/
				m_fNclrStrkDeltaSeconds = 0.0f;
				m_bUseNclrStrk = false;
				m_bAlertNclrStrk = false;

				SetGhostState(EGhostState::STOP);
				SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
				SetTarget(nullptr);
			}
		}

		// 사거리보다 먼 경우, 목표가 있는 곳으로 이동한다.
		else
		{
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
			}
			else
			{
				SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
			}
		}

	}
	break;

	/****************
		사망 상태
	****************/
	case EGhostState::DIE:
	{
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tghdth00.wav", ESoundChannel::UNIT, 1.0f);
			// CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tghdth0", L".wav");

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

	default:
	break;
	}
}

void CGhost::AlertAround()
{
	float fMinDistance = 8192.0f;
	CTerranObject* pNearestObject = nullptr;

	list<CObject*>& lstUnits = CSceneManager::GetManager()->GetCurScene()->GetUnits();
	for (const auto& pUnit : lstUnits)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pUnit);
		if (pTerranObject == this) { continue; }
		if (pTerranObject->GetDead() == true) { continue; }
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
		SetGhostState(EGhostState::ATTACK);
	}
}
