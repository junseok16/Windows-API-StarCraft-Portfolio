#include "pch.h"
#include "ScienceVessel.h"
#include "RectangleColliderComponent.h"

#include "CollisionManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "Sprite.h"
#include "Scene.h"

#include "UnitProperty.h"
#include "Command.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "MPBarUI.h"

#include "DfnsvMtrxProjectile.h"
#include "IrradiateProjectile.h"

CScienceVessel::CScienceVessel(CUnitProperty& _unitProperty)
	: CUnit(_unitProperty) { }

void CScienceVessel::Initialize()
{
	CUnit::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::UNIT);
	SetSize({ 70, 60 });
	SetGdiRender(true);

	// 사이언스 베슬에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 70, 60 });

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
		m_pUnitStopAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckNE");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckN");
		m_pUnitStopAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckNW");
		m_pUnitStopAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckSW");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckS");
		m_pUnitStopAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckSE");

		m_pUnitMoveAnim[(int32)EDirectionState::EAST]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckNE");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckN");
		m_pUnitMoveAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckNW");
		m_pUnitMoveAnim[(int32)EDirectionState::WEST]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckSW");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckS");
		m_pUnitMoveAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"ScncVslStpMvAtckSE");

		m_pUnitDieAnim = CResourceManager::GetManager()->GetAnimation(L"BangM");
		m_pUnitPortrait = CResourceManager::GetManager()->GetAnimation(L"ScncVslPrtrt");

		m_pUnitBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm0");
		m_pUnitBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm1");
		m_pUnitBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm2");
		m_pUnitBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm3");
		m_pUnitBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm4");
		m_pUnitBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"ScncVslBgWrfrm5");

		m_pUnitSmallWireframes[0] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm0");
		m_pUnitSmallWireframes[1] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm1");
		m_pUnitSmallWireframes[2] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm2");
		m_pUnitSmallWireframes[3] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm3");
		m_pUnitSmallWireframes[4] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm4");
		m_pUnitSmallWireframes[5] = CResourceManager::GetManager()->GetSprite(L"ScncVslSmllWrfrm5");
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
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::USE_DEFENSIVE_MATRIX);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::USE_IRRADIATE);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

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
	m_pHPBarUI->SetDistance(35.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	m_pMPBarUI = new CMPBarUI();
	m_pMPBarUI->SetUIActive(false);
	m_pMPBarUI->SetBarOwner(this);
	m_pMPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pMPBarUI->SetDistance(42.0f);
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
	SetTerranUnitType(ETerranUnitType::SCIENCE_VESSEL);

	/********************
		Science Vessel 클래스
	********************/
	m_ScncVslHdSprite[0] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdE");
	m_ScncVslHdSprite[1] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdNE");
	m_ScncVslHdSprite[2] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdN");
	m_ScncVslHdSprite[3] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdNW");
	m_ScncVslHdSprite[4] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdW");
	m_ScncVslHdSprite[5] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdSW");
	m_ScncVslHdSprite[6] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdS");
	m_ScncVslHdSprite[7] = CResourceManager::GetManager()->GetSprite(L"ScncVslHdSE");
	m_pCurHdSprite = m_ScncVslHdSprite[0];

	SetScienceVesselState(EScienceVesselState::STOP);
}

void CScienceVessel::Update()
{
	CUnit::Update();
	RecoverMP();
	UpdateDirection();
	UpdateHead();
	AnalyseCommand();
	ExecuteCommand();
}

void CScienceVessel::LateUpdate()
{
	CUnit::LateUpdate();
}

void CScienceVessel::Render(HDC _hDC)
{
	CUnit::Render(_hDC);
	RenderHead(_hDC);
}

void CScienceVessel::Release()
{
	CUnit::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pMPBarUI);
}

void CScienceVessel::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
	CUnit::OnCollisionEnter2D(_pSrcCollider, _pDstCollider);
}

void CScienceVessel::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
	CUnit::OnCollisionStay2D(_pSrcCollider, _pDstCollider);
}

void CScienceVessel::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CScienceVessel::UpdateDirection()
{
	Vector2 tDirection{ 0.0f, 0.0f };
	tDirection = m_tDstPosition - m_tPosition;
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

void CScienceVessel::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetScienceVesselState(EScienceVesselState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		SetScienceVesselState(EScienceVesselState::MOVE);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTile = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;
	}
	break;

	case ECommandType::STOP:
	{
		SetScienceVesselState(EScienceVesselState::STOP);
	}
	break;

	
	case ECommandType::USE_DEFENSIVE_MATRIX:
	{
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetScienceVesselState(EScienceVesselState::DEFENSIVE_MATRIX);
		m_pTarget = static_cast<CSkill*>(pCmd)->m_pTarget;
	}
	break;

	case ECommandType::USE_IRRADIATE:
	{
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		SetScienceVesselState(EScienceVesselState::IRRADIATE);
		m_pTarget = static_cast<CSkill*>(pCmd)->m_pTarget;
	}
	break;
	
	case ECommandType::CANCEL:
	{
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CScienceVessel::ExecuteCommand()
{
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	switch (m_eScienceVesselState)
	{
	case EScienceVesselState::STOP:
	{
		SetAnimation(m_pUnitStopAnim[(int32)m_eDirectionState]);
		m_tDstPosition = m_tPosition;
	}
	break;

	case EScienceVesselState::MOVE:
	{
		SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);

		Vector2 tDirection = m_tDstPosition - m_tPosition;
		if (tDirection.Magnitude() <= 1.0f)
		{
			SetScienceVesselState(EScienceVesselState::STOP);
		}

		tDirection.Normalize();
		m_tPosition += tDirection * fDeltaSeconds * m_fCurSpeed;
	}
	break;

	/****************
		디펜시브 매트릭스, 이레디에이트 상태
	****************/
	case EScienceVesselState::DEFENSIVE_MATRIX:
	{
		if (m_pTarget->GetDead())
		{
			SetScienceVesselState(EScienceVesselState::STOP);
			SetTarget(nullptr);
			break;
		}

		else
		{
			// 사거리보다 짧은 경우
			if (m_tPosition.Distance(m_pTarget->GetPosition()) <= 256)
			{
				SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
				CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

				// 목표의 체력이 0보다 클 때, 공격한다.
				if (pTarget->GetCurHP() > 0)
				{
					// 마력을 감소시킵니다.
					CSoundManager::GetManager()->PlaySoundEx(L"tvedef00.wav", ESoundChannel::UNIT, 1.0f);

					// 이레디에이트 투사체를 생성합니다.
					CDfnsvMtrxProjectile* pProjectile = new CDfnsvMtrxProjectile();
					pProjectile->SetPosition(m_tPosition);
					pProjectile->SetTarget(pTarget);
					pProjectile->SetDirectionState(m_eDirectionState);
					pProjectile->Initialize();
					CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
				}

				SetScienceVesselState(EScienceVesselState::STOP);
				SetTarget(nullptr);
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
	}
	break;

	case EScienceVesselState::IRRADIATE:
	{
		if (m_pTarget->GetDead())
		{
			SetScienceVesselState(EScienceVesselState::STOP);
			SetTarget(nullptr);
			break;
		}

		else
		{
			// 사거리보다 짧은 경우
			if (m_tPosition.Distance(m_pTarget->GetPosition()) <= 256)
			{
				SetAnimation(m_pUnitMoveAnim[(int32)m_eDirectionState]);
				CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);

				// 목표의 체력이 0보다 클 때, 공격한다.
				if (pTarget->GetCurHP() > 0)
				{
					// 마력을 감소시킵니다.
					CSoundManager::GetManager()->PlaySoundEx(L"tveirr00.wav", ESoundChannel::UNIT, 1.0f);

					// 이레디에이트 투사체를 생성합니다.
					CIrradiateProjectile* pProjectile = new CIrradiateProjectile();
					pProjectile->SetPosition(m_tPosition);
					pProjectile->SetTarget(pTarget);
					pProjectile->SetDirectionState(m_eDirectionState);
					pProjectile->Initialize();
					CSceneManager::GetManager()->GetCurScene()->InsertObject(pProjectile);
				}

				SetScienceVesselState(EScienceVesselState::STOP);
				SetTarget(nullptr);
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
	}
	break;

	case EScienceVesselState::DIE:
	{
		m_pCurHdSprite = nullptr;
		SetAnimation(m_pUnitDieAnim);
		SetTarget(nullptr);

		// 사망 후 처리를 합니다.
		if (!m_bDeadHandle)
		{
			// 사망 사운드를 출력합니다.
			CSoundManager::GetManager()->PlaySoundEx(L"tvedth00.wav", ESoundChannel::UNIT, 1.0f);

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

void CScienceVessel::UpdateHead()
{
	m_tHdPosition = m_tPosition + Vector2{ 0.0f, 8.0f };

	switch (m_eDirectionState)
	{
	case EDirectionState::EAST:
		m_pCurHdSprite = m_ScncVslHdSprite[0];
		break;

	case EDirectionState::NORTH_EAST:
		m_pCurHdSprite = m_ScncVslHdSprite[1];
		break;

	case EDirectionState::NORTH:
		m_pCurHdSprite = m_ScncVslHdSprite[2];
		break;

	case EDirectionState::NORTH_WEST:
		m_pCurHdSprite = m_ScncVslHdSprite[3];
		break;

	case EDirectionState::WEST:
		m_pCurHdSprite = m_ScncVslHdSprite[4];
		break;

	case EDirectionState::SOUTH_WEST:
		m_pCurHdSprite = m_ScncVslHdSprite[5];
		break;

	case EDirectionState::SOUTH:
		m_pCurHdSprite = m_ScncVslHdSprite[6];
		break;

	case EDirectionState::SOUTH_EAST:
		m_pCurHdSprite = m_ScncVslHdSprite[7];
		break;
	}
}

void CScienceVessel::RenderHead(HDC _hDC)
{
	VERIFY_NULLPTR(m_pCurHdSprite);
	tagSpriteInfo tSpriteInfo = m_pCurHdSprite->GetSpriteInfo();

	Vector2Int tSize = tSpriteInfo.m_tSize;
	Vector2Int tPosition = tSpriteInfo.m_tPosition;
	uint32 uiAlpha = m_pCurHdSprite->GetTextureAlpha();

	// 스크롤된 위치를 구합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		::BitBlt(_hDC,																				// 사본 이미지의 DC
			(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),	// 사본 이미지에서 원본 이미지가 렌더될 좌상단 위치
			(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
			tSize.m_iWidth,																			// 원본 이미지의 밑변
			tSize.m_iHeight,																		// 원본 이미지의 높이
			m_pCurHdSprite->GetTextureDC(),																// 원본 이미지의 DC
			tPosition.m_iX,																			// 원본 이미지의 좌상단 위치
			tPosition.m_iY,
			SRCCOPY);
	}
	else
	{
		GdiTransparentBlt(_hDC,
			(int32)(m_tHdPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
			(int32)(m_tHdPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
			tSize.m_iWidth,
			tSize.m_iHeight,
			m_pCurHdSprite->GetTextureDC(),
			tPosition.m_iX,
			tPosition.m_iY,
			tSize.m_iWidth,
			tSize.m_iHeight,
			uiAlpha);
	}
}
