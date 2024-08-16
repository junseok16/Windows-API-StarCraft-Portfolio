#include "pch.h"
#include "Vulture.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "AStarManager.h"

#include "RectangleColliderComponent.h"

#include "UnitProperty.h"
#include "Command.h"
#include "Scene.h"
#include "Player.h"
#include "DynamicTilemapObject.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"

#include "VultureProjectile.h"
using namespace std;

CVulture::CVulture(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CVulture::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 30, 30 });
	SetGdiRender(true);

	// 벌쳐에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 30, 30 });

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
		m_pUnitStopAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST]		 = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH]		 = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST]		 = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH]		 = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"VltrStpMvAttkSE");

		m_pUnitDieAnim											= CResourceManager::GetManager()->GetAnimation(L"BangS");
		m_pUnitHitedAnim										= CResourceManager::GetManager()->GetAnimation(L"VltrHted");
		m_pUnitPortrait											= CResourceManager::GetManager()->GetAnimation(L"VltrPrtrt");

		m_pUnitHitingAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"VltrHtngE");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrHtngNE");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrHtngN");
		m_pUnitHitingAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrHtngNW");
		m_pUnitHitingAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"VltrHtngW");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrHtngSW");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrHtngS");
		m_pUnitHitingAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrHtngSE");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"VltrBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"VltrSmllWrfrm5");
		SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::SOUTH]);
	}

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::GROUND_UNIT);
	SetUnitAtributeType(EUnitAttributeType::MECHANICAL);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::MOVE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::STOP);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ATTACK);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct2"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(30.0f);
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
	SetTerranUnitType(ETerranUnitType::VULTURE);

	/********************
		Marine 클래스
	********************/
	SetVultureState(EVultureState::STOP);
}

void CVulture::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	AnalyseCommand();
	UpdateDirection();
	ExecuteCommand();
}

void CVulture::LateUpdate()
{
	CUnit::LateUpdate();
}

void CVulture::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
}

void CVulture::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CVulture::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };

	switch (m_eVultureState)
	{
	case EVultureState::STOP:
	case EVultureState::MOVE:
	{
		tDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case EVultureState::ATTACK:
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

void CVulture::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetVultureState(EVultureState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		SetVultureState(EVultureState::MOVE);
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
		SetVultureState(EVultureState::STOP);
	}
	break;

	case ECommandType::ATTACK:
	{
		SetVultureState(EVultureState::ATTACK);
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
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CVulture::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eVultureState)
	{
	case EVultureState::STOP:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
		AlertAround();
	}
	break;

	case EVultureState::MOVE:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);

		if (!m_queOptimalPath.empty())
		{
			Vector2Int tDstTilePosition = m_queOptimalPath.front();
			m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

			Vector2 direction = m_tDstPosition - m_tPosition;
			if (direction.Magnitude() < 3.0f)
			{
				m_queOptimalPath.pop();
				break;
			}

			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
		}
		else
		{
			SetVultureState(EVultureState::STOP);
		}
	}
	break;

	case EVultureState::ATTACK:
	{
		// 목표가 없는 경우, 경계하면서 이동한다.
		if (m_pTarget == nullptr)
		{
			SetCurHitingAnim(nullptr);
			//SetCurHitedAnim(nullptr);
			if (!m_queOptimalPath.empty())
			{
				Vector2Int tDstTilePosition = m_queOptimalPath.front();
				m_tDstPosition = { tDstTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tDstTilePosition.m_iY * FTILECY + FTILECY * 0.5f };

				Vector2 direction = m_tDstPosition - m_tPosition;
				if (direction.Magnitude() < 3.0f)
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
				SetVultureState(EVultureState::STOP);
			}

			break;
		}

		// 목표가 죽은 경우, 정지한다.
		else if (m_pTarget->GetDead())
		{
			SetCurHitingAnim(nullptr);
			//SetCurHitedAnim(nullptr);
			SetVultureState(EVultureState::STOP);
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
						CSoundManager::GetManager()->PlaySoundEx(L"tvufir00.wav", ESoundChannel::UNIT, 1.0f);

						{
							// 투사체를 생성합니다.
							CVultureProjectile* pProjectile = new CVultureProjectile();
							pProjectile->SetPosition(m_tPosition);
							pProjectile->SetTarget(pTarget);
							pProjectile->SetDirectionState(m_eDirectionState);
							pProjectile->Initialize();
							CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
						}

						SetCurHitingAnim(m_pUnitHitingAnim[(int32)m_eDirectionState]);
						//SetCurHitedAnim(m_pUnitHitedAnim);

						Vector2 tDirVector = m_pTarget->GetPosition() - m_tPosition;
						tDirVector.Normalize();

						SetHitingPosition(m_tPosition + tDirVector * 10.0f);
						//SetHitedPosition(m_pTarget->GetPosition());
						/*
						if (pTarget->GetAttacked(m_unitProperty.GetAttackPoint()) == true)
						{
							SetCurHitingAnim(nullptr);
							//SetCurHitedAnim(nullptr);
							pTarget->SetDead(true);
							SetVultureState(EVultureState::STOP);
							SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
							m_pTarget = nullptr;
						}*/
						m_fSumAttackDeltaSeconds = 0.0f;
					}
					else
					{
						SetCurHitingAnim(nullptr);
						//SetCurHitedAnim(nullptr);
						SetVultureState(EVultureState::STOP);
						SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
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

	case EVultureState::DIE:
	{
		SetCurHitingAnim(nullptr);
		//SetCurHitedAnim(nullptr);
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tvudth00.wav", ESoundChannel::UNIT, 1.0f);

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

void CVulture::AlertAround()
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
		SetVultureState(EVultureState::ATTACK);
	}
}

void CVulture::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CVulture::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CVulture::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}