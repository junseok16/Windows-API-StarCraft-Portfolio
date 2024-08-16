#include "pch.h"
#include "Medic.h"
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
#include "DynamicTilemapObject.h"

#include "Scene.h"
#include "TerranObject.h"
#include "Player.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"
using namespace std;

CMedic::CMedic(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CMedic::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 20, 30 });
	SetGdiRender(true);

	// 메딕에 사각형 콜라이더 컴포넌트를 붙입니다.
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
		m_pUnitStopAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"MdcStopN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"MdcStopS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcStopSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcMoveSE");

		m_pUnitAttckAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealNE");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"MdcHealN");
		m_pUnitAttckAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealNW");
		m_pUnitAttckAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealSW");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"MdcHealS");
		m_pUnitAttckAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"MdcHealSE");

		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"MdcDie");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"MdcPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"MdcBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"MdcSmllWrfrm5");
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
	SetTerranUnitType(ETerranUnitType::MEDIC);

	/********************
		Medic 클래스
	********************/
	SetMedicState(EMedicState::STOP);
}

void CMedic::Update()
{
	CUnit::Update();
	m_fSumAttackDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
	RecoverMP();
	AnalyseCommand();
	UpdateDirection();
	ExecuteCommand();
}

void CMedic::LateUpdate()
{
	CUnit::LateUpdate();
}

void CMedic::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
}

void CMedic::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pMPBarUI);
}

void CMedic::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CMedic::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CMedic::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CMedic::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };

	switch (m_eMedicState)
	{
	case EMedicState::STOP:
	case EMedicState::MOVE:
	{
		tDirection = m_tDstPosition - m_tPosition;
	}
	break;

	case EMedicState::HEAL:
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

void CMedic::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetMedicState(EMedicState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		SetMedicState(EMedicState::MOVE);
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
		SetMedicState(EMedicState::STOP);
	}
	break;


	case ECommandType::USE_HEAL:
	{
		SetMedicState(EMedicState::HEAL);
		m_tDstTile = static_cast<CAttack*>(pCmd)->m_tDstTile;
		m_tDstPosition = static_cast<CAttack*>(pCmd)->m_tDstPosition;
		m_pTarget = static_cast<CAttack*>(pCmd)->m_pTarget;
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CMedic::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eMedicState)
	{
	case EMedicState::STOP:
	{
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;

		float fMinDistance = 8192.0f;
		CTerranObject* pNearestObject = nullptr;

		list<CObject*>& lstUnits = CSceneManager::GetManager()->GetCurScene()->GetUnits();
		for (const auto& pUnit : lstUnits)
		{
			CUnit* pTerranObject = dynamic_cast<CUnit*>(pUnit);
			if (pTerranObject == this) { continue; }
			if (pTerranObject->GetDead() == true) { continue; }
			if (GetOwnerType() == EOwnerType::COMPUTER && pTerranObject->GetOwnerType() == EOwnerType::PLAYER) { continue; }
			if (GetOwnerType() == EOwnerType::PLAYER && pTerranObject->GetOwnerType() == EOwnerType::COMPUTER) { continue; }

			// 최대 체력인 경우
			if (pTerranObject->GetCurHP() >= pTerranObject->GetUnitProperty().GetMaxHP()) { continue; }

			// 건물이거나 기계 유닛인 경우
			if (pTerranObject->GetUnitAttributeType() == EUnitAttributeType::MECHANICAL) { continue; }

			// 시야보다 짧은 경우
			Vector2 tAllyPosition = pTerranObject->GetPosition();
			float fDistance = m_tPosition.Distance(tAllyPosition);

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
			SetMedicState(EMedicState::HEAL);
		}
	}
	break;

	case EMedicState::MOVE:
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
			SetMedicState(EMedicState::STOP);
		}
	}
	break;

	case EMedicState::HEAL:
	{
		// 목표가 없는 경우, 목표가 있는 곳으로 이동한다.
		if (m_pTarget == nullptr)
		{
			//SetMedicState(EMedicState::ALERT);
			break;
		}

		else if (m_pTarget->GetDead())
		{
			SetMedicState(EMedicState::STOP);
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

				// TODO: 힐을 시작하는 애니메이션
				
				// 힐 주기가 되었을 때
				if (m_fSumAttackDeltaSeconds >= m_fCurAttackDeltaSeconds)
				{
					SetAnimation(m_pUnitAttckAnim[(int32)m_eDirectionState]);
					CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

					// 목표의 체력이 최대 체력보다 작을 때, 치료한다.
					if (0 < GetCurMP() && 0 < pTarget->GetCurHP() && pTarget->GetCurHP() < pTarget->GetUnitProperty().GetMaxHP())
					{
						CSoundManager::GetManager()->PlaySoundEx(L"tmedheal.wav", ESoundChannel::UNIT, 1.0f);

						DecreaseMP(3);
						if (pTarget->GetHealed(m_unitProperty.GetAttackPoint()) == true)
						{
							SetMedicState(EMedicState::STOP);
							m_pTarget = nullptr;
						}
						m_fSumAttackDeltaSeconds = 0.0f;
					}
					// 목표가 죽은 경우
					else
					{
						SetMedicState(EMedicState::STOP);
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
				// SetMarineState(EMarineState::ALERT);

				Vector2 direction = m_pTarget->GetPosition() - m_tPosition;
				direction.Normalize();
				m_tPosition += direction * fDeltaSeconds * m_fCurSpeed;
			}
		}
	}
	break;

	case EMedicState::DIE:
	{
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tmddth00.wav", ESoundChannel::UNIT, 1.0f);

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
