#include "pch.h"
#include "TankProjectile.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "PropertyManager.h"

#include "TerranObject.h"
#include "Scene.h"

#include "UnitProperty.h"
#include "Unit.h"

void CTankProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	/************************
		Projectile Å¬·¡½º
	************************/
	m_eProjectileState = EProjectileState::EXPLODE;
	m_fCurSpeed = 0.0f;

	m_pBulletStopAnim = CResourceManager::GetManager()->GetAnimation(L"TnkHdHted");
	m_pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
}

void CTankProjectile::Update()
{
	CProjectile::Update();

	switch (m_eProjectileState)
	{
	case EProjectileState::TRACE:
	{

	}
	break;

	case EProjectileState::EXPLODE:
	{
		SetPosition(m_pTarget->GetPosition());
		SetAnimation(m_pBulletStopAnim);

		CUnit* pTarget = dynamic_cast<CUnit*>(m_pTarget);
		//CSoundManager::GetManager()->PlaySoundEx(L"ttafir00.wav", ESoundChannel::UNIT, 1.0f);
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

		if (m_fDeadDelay > 0.4f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
		break;
	}
}

void CTankProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CTankProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CTankProjectile::Release()
{
	CProjectile::Release();
}
