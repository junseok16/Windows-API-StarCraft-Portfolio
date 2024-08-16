#include "pch.h"
#include "Firebat.h"
#include "RectangleColliderComponent.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "AStarManager.h"

#include "UnitProperty.h"
#include "Command.h"

#include "Scene.h"
#include "Player.h"
#include "DynamicTilemapObject.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
using namespace std;

CFirebat::CFirebat(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CFirebat::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 20, 30 });
	SetGdiRender(true);

	// 파이어뱃에 사각형 콜라이더 컴포넌트를 붙입니다.
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
		m_pUnitStopAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtStopSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtMoveSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"FrbtAttckSE");

		m_pUnitHitingAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngE");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngNE");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngN");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngNW");
		m_pUnitHitingAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngW");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngSW");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngS");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"FrbtHitngSE");

		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"BangS");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"FrbtPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"FrbtBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"FrbtSmllWrfrm5");

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
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::USE_STIMPACK);

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


	/********************
		Unit 클래스
	********************/
	SetCurHP(m_unitProperty.GetMaxHP());
	SetCurMP(m_unitProperty.GetMaxMP());
	SetCurShield(m_unitProperty.GetMaxShield());
	SetCurSpeed(m_unitProperty.GetSpeed());
	SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds());
	SetCurRange(m_unitProperty.GetRange());
	SetTerranUnitType(ETerranUnitType::FIREBAT);

	/********************
		Marine 클래스
	********************/
	SetFirebatState(EFirebatState::STOP);
}

void CFirebat::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	UpdateDirection();
	AnalyseCommand();
	ExecuteCommand();
	UpdateCoolTime();
}

void CFirebat::LateUpdate()
{
	CUnit::LateUpdate();
}

void CFirebat::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
}

void CFirebat::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CFirebat::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };

	switch (m_eFirebatState)
	{
	case EFirebatState::STOP:
	case EFirebatState::MOVE:
	{
		tDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case EFirebatState::ATTACK:
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

void CFirebat::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetFirebatState(EFirebatState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		SetFirebatState(EFirebatState::MOVE);
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
		SetFirebatState(EFirebatState::STOP);
	}
	break;

	case ECommandType::ATTACK:
	{
		SetFirebatState(EFirebatState::ATTACK);
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

	case ECommandType::USE_STIMPACK:
	{
		if (GetOwnerType() != EOwnerType::PLAYER) { break; }

		m_bStimpack = true;
		if (m_iCurHP <= 10) { break; }

		CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tmasti0", L".wav");
		m_iCurHP -= 10;

		SetCurSpeed(m_unitProperty.GetSpeed() * 1.5f);
		SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds() * 0.5f);
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CFirebat::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eFirebatState)
	{
	/****************
		정지 명령
	****************/
	case EFirebatState::STOP:
	{
		SetCurHitingAnim(nullptr);
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
		AlertAround();
	}
	break;


	/****************
		이동 명령
	****************/
	case EFirebatState::MOVE:
	{
		SetCurHitingAnim(nullptr);
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
			SetFirebatState(EFirebatState::STOP);
		}
	}
	break;


	/****************
		공격 명령
	****************/
	case EFirebatState::ATTACK:
	{
		// 목표가 없는 경우, 목표가 있는 곳으로 이동한다.
		if (m_pTarget == nullptr)
		{
			SetCurHitingAnim(nullptr);
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
				SetFirebatState(EFirebatState::STOP);
			}
			break;
		}

		else if (m_pTarget->GetDead())
		{
			SetCurHitingAnim(nullptr);
			SetFirebatState(EFirebatState::STOP);
			SetTarget(nullptr);
			break;
		}

		// 목표가 살아있는 경우
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
						CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tfbfir0", L".wav");
						
						// 화염 이펙트를 출력한다.
						SetCurHitingAnim(m_pUnitHitingAnim[(int32)m_eDirectionState]);
						Vector2 tDirVector = m_pTarget->GetPosition() - m_tPosition;
						tDirVector.Normalize();
						SetHitingPosition(m_tPosition + tDirVector * 2.0f);
						
						if (pTarget->GetAttacked(m_unitProperty.GetAttackPoint()) == true)
						{
							SetCurHitingAnim(nullptr);
							pTarget->SetDead(true);
							SetFirebatState(EFirebatState::STOP);
							SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
							m_pTarget = nullptr;
						}
						m_fSumAttackDeltaSeconds = 0.0f;
					}
					else
					{
						SetCurHitingAnim(nullptr);
						SetFirebatState(EFirebatState::STOP);
						SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
						m_pTarget = nullptr;
					}
				}
				else
				{
					SetCurHitingAnim(nullptr);
				}
			}
			// 사거리보다 먼 경우
			else
			{
				SetCurHitingAnim(nullptr);
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

	case EFirebatState::DIE:
	{
		SetCurHitingAnim(nullptr);
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->RandomPlaySound(3, ESoundChannel::UNIT, L"tfbdth0", L".wav");

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

void CFirebat::AlertAround()
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
		SetFirebatState(EFirebatState::ATTACK);
	}
}

void CFirebat::UpdateCoolTime()
{
	if (m_bStimpack == true)
	{
		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		m_fSumStimpackDeltaSeconds += fDeltaSeconds;

		if (m_fSumStimpackDeltaSeconds >= 10.0f)
		{
			SetCurSpeed(m_unitProperty.GetSpeed());
			SetCurAttackDeltaSeconds(m_unitProperty.GetAttackDeltaSeconds());
			m_fSumStimpackDeltaSeconds = 0.0f;
			m_bStimpack = false;
		}
	}
}

void CFirebat::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CFirebat::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CFirebat::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}
