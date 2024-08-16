#include "pch.h"
#include "Battlecruiser.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

#include "UnitProperty.h"
#include "Command.h"

#include "Scene.h"
#include "TerranObject.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"

#include "RectangleColliderComponent.h"
#include "BtlcrsrProjectile.h"
#include "BtlcrsrYmtProjectile.h"
using namespace std;

CBattlecruiser::CBattlecruiser(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) {
}

void CBattlecruiser::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 80, 80 });
	SetGdiRender(true);

	// 마린에 사각형 콜라이더 컴포넌트를 붙입니다.
	pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 80, 80 });

	pRectCollider->SetCollisionType(ECollisionType::AIR_UNIT);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::AIR_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);


	/********************
		AnimationObject 클래스
	********************/
	{
		m_pUnitStopAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST]= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST]= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrStpMvAtckSE");

		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"BangM");
		// m_pUnitHitedAnim = CResourceManager::GetManager()->GetAnimation(L"MrnHit");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"BtlcrsrPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"BtlcrsrSmllWrfrm5");
		SetAnimation(m_pUnitStopAnim[(int32)EDirectionState::SOUTH]);
	}

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::AIR_UNIT);
	SetUnitAtributeType(EUnitAttributeType::MECHANICAL);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::MOVE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::STOP);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::ATTACK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::USE_YAMATO_CANNON);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct6"));
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

	m_pMPBarUI = new CMPBarUI();
	m_pMPBarUI->SetUIActive(false);
	m_pMPBarUI->SetBarOwner(this);
	m_pMPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pMPBarUI->SetDistance(55.0f);
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
	SetCurRange(m_unitProperty.GetRange());
	SetTerranUnitType(ETerranUnitType::BATTLE_CRUISER);

	/********************
		Marine 클래스
	********************/
	SetBattlecruiserState(EBattlecruiserState::STOP);
}

void CBattlecruiser::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	RecoverMP();
	AnalyseCommand();
	UpdateDirection();
	ExecuteCommand();
}

void CBattlecruiser::LateUpdate()
{
	CUnit::LateUpdate();
}

void CBattlecruiser::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
}

void CBattlecruiser::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pMPBarUI);
}

void CBattlecruiser::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CBattlecruiser::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CBattlecruiser::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CBattlecruiser::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };

	switch (m_eBattlecruiserState)
	{
	case EBattlecruiserState::STOP:
	case EBattlecruiserState::MOVE:
	{
		tDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case EBattlecruiserState::ATTACK:
	case EBattlecruiserState::YAMATO_CANNON:
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

void CBattlecruiser::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetBattlecruiserState(EBattlecruiserState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		SetBattlecruiserState(EBattlecruiserState::MOVE);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTile = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;
	}
	break;

	case ECommandType::STOP:
	{
		SetBattlecruiserState(EBattlecruiserState::STOP);
	}
	break;

	case ECommandType::ATTACK:
	{
		SetBattlecruiserState(EBattlecruiserState::ATTACK);
		m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;
	}
	break;

	case ECommandType::USE_YAMATO_CANNON:
	{
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetBattlecruiserState(EBattlecruiserState::YAMATO_CANNON);
		m_pTarget = static_cast<CSkill*>(pCmd)->m_pTarget;
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CBattlecruiser::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eBattlecruiserState)
	{
	/****************
		정지 명령
	****************/
	case EBattlecruiserState::STOP:
	{
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
		AlertAround();
	}
	break;

	/****************
		이동 명령
	****************/
	case EBattlecruiserState::MOVE:
	{
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);

		Vector2 tDirection = m_tDstPosition - m_tPosition;
		if (tDirection.Magnitude() <= 1.0f)
		{
			SetBattlecruiserState(EBattlecruiserState::STOP);
		}

		tDirection.Normalize();
		m_tPosition += tDirection * fDeltaSeconds * m_fCurSpeed;
	}
	break;

	/****************
		공격 명령
	****************/
	case EBattlecruiserState::ATTACK:
	{
		// 목표가 없는 경우, 경계하면서 이동한다.
		if (m_pTarget == nullptr)
		{
			AlertAround();
			break;
		}

		// 목표가 죽은 경우, 정지한다.
		else if (m_pTarget->GetDead())
		{
			SetBattlecruiserState(EBattlecruiserState::STOP);
			SetTarget(nullptr);
			break;
		}

		// 목표가 살아있는 경우
		else
		{
			// 사거리보다 짧은 경우
			if (m_tPosition.Distance(m_pTarget->GetPosition()) <= m_iCurRange)
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
						CSoundManager::GetManager()->PlaySoundEx(L"tphfi100.wav", ESoundChannel::UNIT, 1.0f);

						{
							// 투사체를 생성합니다.
							CBtlcrsrProjectile* pProjectile = new CBtlcrsrProjectile();
							pProjectile->SetPosition(m_tPosition);
							pProjectile->SetTarget(pTarget);
							pProjectile->SetDirectionState(m_eDirectionState);
							pProjectile->Initialize();
							CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
						}
						
						m_fSumAttackDeltaSeconds = 0.0f;
					}
					else
					{
						SetBattlecruiserState(EBattlecruiserState::STOP);
						SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
						m_pTarget = nullptr;
					}
				}
			}
			// 사거리보다 먼 경우
			else
			{
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

	/****************
		야마토포 상태
	****************/
	case EBattlecruiserState::YAMATO_CANNON:
	{
		if (m_pTarget->GetDead())
		{
			SetBattlecruiserState(EBattlecruiserState::STOP);
			SetTarget(nullptr);
			break;
		}

		// 사거리보다 짧은 경우
		if (m_tPosition.Distance(m_pTarget->GetPosition()) <= m_unitProperty.GetRange())
		{
			SetAnimation(m_pUnitAttckAnim[(int32)m_eDirectionState]);
			CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

			// 목표의 체력이 0보다 클 때, 공격한다.
			if (pTarget->GetCurHP() > 0)
			{
				if (!m_bUseYmtCnn)
				{
					// TODO: 마력을 감소시킵니다.
					CSoundManager::GetManager()->PlaySoundEx(L"tbayam01.wav", ESoundChannel::UNIT, 1.0f);
					m_bUseYmtCnn = true;
				}

				m_fYmtDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
				if (m_fYmtDeltaSeconds >= 2.0f)
				{
					CSoundManager::GetManager()->PlaySoundEx(L"tbayam02.wav", ESoundChannel::UNIT, 1.0f);

					// 야마토포 투사체를 생성합니다.
					CBtlcrsrYmtProjectile* pProjectile = new CBtlcrsrYmtProjectile();
					pProjectile->SetPosition(m_tPosition);
					pProjectile->SetTarget(pTarget);
					pProjectile->SetDirectionState(m_eDirectionState);
					pProjectile->Initialize();
					CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
					
					m_fYmtDeltaSeconds = 0.0f;
					m_bUseYmtCnn = false;

					SetBattlecruiserState(EBattlecruiserState::STOP);
					SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
					SetTarget(nullptr);
				}
			}
			else
			{
				SetBattlecruiserState(EBattlecruiserState::STOP);
				SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
				SetTarget(nullptr);
			}
				
		}
		// 사거리보다 먼 경우, 목표가 있는 곳으로 이동한다.
		else
		{
			SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
			Vector2 direction = m_pTarget->GetPosition() - m_tPosition;
			direction.Normalize();
			m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
		}
		
	}
	break;

	/****************
		사망 상태
	****************/
	case EBattlecruiserState::DIE:
	{
		//SetCurHitedAnim(nullptr);
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tbadth00.wav", ESoundChannel::UNIT, 1.0f);

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

void CBattlecruiser::AlertAround()
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
		SetBattlecruiserState(EBattlecruiserState::ATTACK);
	}
}
