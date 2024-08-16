#include "pch.h"
#include "BtlcrsrYmtProjectile.h"

#include "ResourceManager.h"
#include "TimeManager.h"
#include "PropertyManager.h"

#include "TerranObject.h"
#include "Scene.h"

#include "UnitProperty.h"
#include "Unit.h"

void CBtlcrsrYmtProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	/************************
		Projectile Å¬·¡½º
	************************/
	m_eProjectileState = EProjectileState::TRACE;
	m_fCurSpeed = 6.0f;

	m_pBulletStopAnim										= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrPrjctlStp");
	m_pBulletMoveAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtE");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtNE");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtN");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtNW");
	m_pBulletMoveAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtW");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtSW");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtS");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"BtlcrsrYmtSE");
}

void CBtlcrsrYmtProjectile::Update()
{
	CProjectile::Update();

	switch (m_eProjectileState)
	{
	case EProjectileState::TRACE:
	{
		SetAnimation(m_pBulletMoveAnim[(int32)m_eDirectionState]);
		Vector2 tDirection = m_pTarget->GetPosition() - m_tPosition;

		if (tDirection.Magnitude() < 16.0f)
		{
			m_eProjectileState = EProjectileState::EXPLODE;
			break;
		}

		tDirection.Normalize();
		m_tPosition += tDirection * m_fCurSpeed;
	}
	break;

	case EProjectileState::EXPLODE:
	{
		SetPosition(m_pTarget->GetPosition());
		SetAnimation(m_pBulletStopAnim);

		CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);
		if (pTarget->GetAttacked(240) == true)
		{
			pTarget->SetDead(true);
			m_pTarget = nullptr;
		}

		m_eProjectileState = EProjectileState::DIE;
	}
	break;

	case EProjectileState::DIE:
	{
		m_fDeadDelay += CTimeManager::GetManager()->GetDeltaSeconds();

		if (m_fDeadDelay > 0.5f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
		break;
	}
}

void CBtlcrsrYmtProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CBtlcrsrYmtProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CBtlcrsrYmtProjectile::Release()
{
	CProjectile::Release();
}
