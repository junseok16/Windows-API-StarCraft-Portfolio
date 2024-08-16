#include "pch.h"
#include "NuclearProjectile.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "PropertyManager.h"

#include "Unit.h"
#include "Scene.h"
using namespace std;

void CNuclearProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	/************************
		Projectile 클래스
	************************/
	m_eProjectileState = EProjectileState::TRACE;
	m_fCurSpeed = 0.7f;

	m_pBulletStopAnim										= CResourceManager::GetManager()->GetAnimation(L"NclrFlame");
	m_pBulletMoveAnim[(int32)EDirectionState::EAST]			= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH]		= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::NORTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::WEST]			= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_WEST]	= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH]		= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
	m_pBulletMoveAnim[(int32)EDirectionState::SOUTH_EAST]	= CResourceManager::GetManager()->GetAnimation(L"NclrPrjtl");
}

void CNuclearProjectile::Update()
{
	CProjectile::Update();

	switch (m_eProjectileState)
	{
	case EProjectileState::TRACE:
	{
		SetAnimation(m_pBulletMoveAnim[(int32)EDirectionState::SOUTH]);
		Vector2 tDirection = m_pTarget->GetPosition() - m_tPosition;

		if (tDirection.Magnitude() < 3.0f)
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

		m_fExplosionDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_fExplosionDeltaSeconds <= 0.3f) { break; }
		m_fExplosionDeltaSeconds = 0.0f;
		CSoundManager::GetManager()->PlaySoundEx(L"tnshit00.wav", ESoundChannel::EFFECT, 1.0f);

		RECT tRangeRect{ (int32)m_tPosition.m_fX - 128, (int32)m_tPosition.m_fY - 128, (int32)m_tPosition.m_fX + 128, (int32)m_tPosition.m_fY + 128 };
		CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
		VERIFY_NULLPTR(pCurScene);

		list<CObject*>& lstUnits = pCurScene->GetUnits();

		for (const auto& pObject : lstUnits)
		{
			CUnit* pUnit = dynamic_cast<CUnit*>(pObject);

			// 유닛의 사각형을 구합니다.
			Vector2 tObjectPosition = pObject->GetPosition();
			Vector2Int tObjectSize = pObject->GetSize();
			RECT tObjectRect = CGeometry::GetRect(tObjectPosition, tObjectSize);

			// 충돌한 사각형을 선언합니다.
			RECT tIntersectRect{};

			if (::IntersectRect(&tIntersectRect, &tRangeRect, &tObjectRect))
			{
				if (pUnit->GetAttacked(500) == true)
				{
					pUnit->SetDead(true);
					m_eProjectileState = EProjectileState::DIE;
				}
			}
		}
		m_eProjectileState = EProjectileState::DIE;
	}
	break;

	case EProjectileState::DIE:
	{
		m_fDeadDelay += CTimeManager::GetManager()->GetDeltaSeconds();

		if (m_fDeadDelay > 3.0f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
		break;
	}
}

void CNuclearProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CNuclearProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CNuclearProjectile::Release()
{
	CProjectile::Release();
}
