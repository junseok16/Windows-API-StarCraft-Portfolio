#include "pch.h"
#include "VultureProjectile.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "PropertyManager.h"

#include "TerranObject.h"
#include "Scene.h"

#include "UnitProperty.h"
#include "Unit.h"

void CVultureProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	/************************
		Projectile Å¬·¡½º
	************************/
	m_eProjectileState = EProjectileState::TRACE;
	m_fCurSpeed = 5.0f;

	m_pBulletStopAnim = CResourceManager::GetManager()->GetAnimation(L"VltrHted");
	m_pBulletMoveAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlE");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlNE");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlN");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlNW");
	m_pBulletMoveAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlW");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlSW");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlS");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"VltrPrjctlSE");

	m_pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
}

void CVultureProjectile::Update()
{
	CProjectile::Update();

	switch (m_eProjectileState)
	{
	case EProjectileState::TRACE:
	{
		SetAnimation(m_pBulletMoveAnim[(int32)m_eDirectionState]);
		Vector2 tDirection = m_pTarget->GetPosition() - m_tPosition;

		if (tDirection.Magnitude() < 6.0f)
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
		CSoundManager::GetManager()->RandomPlaySound(3, ESoundChannel::UNIT, L"tvuhit0", L".wav");
		if (pTarget->GetAttacked(m_pProperty->GetAttackPoint()) == true)
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

		if (m_fDeadDelay > 0.7f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
	break;
	}
}

void CVultureProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CVultureProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CVultureProjectile::Release()
{
	CProjectile::Release();
}
