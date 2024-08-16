#include "pch.h"
#include "SiegeTankProjectile.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "PropertyManager.h"

#include "TerranObject.h"
#include "Scene.h"

#include "UnitProperty.h"
#include "Unit.h"
using namespace std;

void CSiegeTankProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	/************************
		Projectile 클래스
	************************/
	m_eProjectileState = EProjectileState::EXPLODE;
	m_fCurSpeed = 0.0f;

	m_pBulletStopAnim = CResourceManager::GetManager()->GetAnimation(L"SgTnkHdHted");
	m_pProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
}

void CSiegeTankProjectile::Update()
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

		RECT tRangeRect{ (int32)m_tPosition.m_fX - 24, (int32)m_tPosition.m_fY - 24, (int32)m_tPosition.m_fX + 24, (int32)m_tPosition.m_fY + 24 };
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
				if (pUnit->GetAttacked(m_pProperty->GetAttackPoint()) == true)
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

void CSiegeTankProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CSiegeTankProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CSiegeTankProjectile::Release()
{
	CProjectile::Release();
}
