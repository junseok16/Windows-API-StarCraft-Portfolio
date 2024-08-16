#include "pch.h"
#include "DfnsvMtrxProjectile.h"

#include "ResourceManager.h"
#include "TimeManager.h"

#include "Unit.h"
#include "TerranObject.h"

void CDfnsvMtrxProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	m_eProjectileState = EProjectileState::TRACE;
	m_pBulletMoveAnim[(int32)EDirectionState::EAST]  = CResourceManager::GetManager()->GetAnimation(L"DfnsvMtrxS");// S
	m_pBulletMoveAnim[(int32)EDirectionState::WEST]  = CResourceManager::GetManager()->GetAnimation(L"DfnsvMtrxM");// M
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"DfnsvMtrxL");// L
}

void CDfnsvMtrxProjectile::Update()
{
	CProjectile::Update();

	switch (m_eProjectileState)
	{
	case EProjectileState::TRACE:
	{
		// 대상이 죽은 경우
		if (m_pTarget->GetDead())
		{
			m_eProjectileState = EProjectileState::DIE;
		}
		CUnit* pUnit = dynamic_cast<CUnit*>(m_pTarget);
		pUnit->IncreaseShield(250);
		m_eProjectileState = EProjectileState::EXPLODE;
	}
	break;

	case EProjectileState::EXPLODE:
	{
		m_fActiveDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

		// 대상이 죽은 경우
		if (m_pTarget->GetDead())
		{
			m_eProjectileState = EProjectileState::DIE;
			break;
		}

		CUnit* pUnit = dynamic_cast<CUnit*>(m_pTarget);
		if (m_fActiveDeltaSeconds < 60.0f)
		{
			SetPosition(m_pTarget->GetPosition());
			SetAnimation(m_pBulletMoveAnim[(int32)EDirectionState::WEST]);

			// 실드가 다 닳은 경우
			
			if (pUnit->GetCurShield() <= 0)
			{
				m_eProjectileState = EProjectileState::DIE;
			}
		}
		// 시간이 다 된 경우
		else
		{
			m_eProjectileState = EProjectileState::DIE;
			pUnit->SetCurShield(0);
		}
	}
	break;

	case EProjectileState::DIE:
	{
		m_fDeadDelay += CTimeManager::GetManager()->GetDeltaSeconds();

		if (m_fDeadDelay > 0.3f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
		break;
	}
}

void CDfnsvMtrxProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CDfnsvMtrxProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CDfnsvMtrxProjectile::Release()
{
	CProjectile::Release();
}
