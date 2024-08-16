#include "pch.h"
#include "IrradiateProjectile.h"

#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

#include "TerranObject.h"
#include "Scene.h"
#include "Unit.h"
using namespace std;

void CIrradiateProjectile::Initialize()
{
	CProjectile::Initialize();
	m_eObjectType = EObjectType::EFFECT;

	m_eProjectileState = EProjectileState::EXPLODE;
	m_pBulletStopAnim = CResourceManager::GetManager()->GetAnimation(L"Irdt");
}

void CIrradiateProjectile::Update()
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
		m_fActiveDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

		// ����� ���� ���
		if (m_pTarget->GetDead())
		{
			m_eProjectileState = EProjectileState::DIE;
			break;
		}

		if (m_fActiveDeltaSeconds < 30.0f)
		{
			SetPosition(m_pTarget->GetPosition());
			SetAnimation(m_pBulletStopAnim);

			m_fDamageDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

			if (m_fDamageDeltaSeconds >= 0.5f)
			{
				RECT tRangeRect{ (int32)m_tPosition.m_fX - 32, (int32)m_tPosition.m_fY - 32, (int32)m_tPosition.m_fX + 32, (int32)m_tPosition.m_fY + 32 };
				CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
				VERIFY_NULLPTR(pCurScene);

				list<CObject*>& lstUnits = pCurScene->GetUnits();

				for (const auto& pObject : lstUnits)
				{
					CUnit* pUnit = dynamic_cast<CUnit*>(pObject);

					// ��� ������ ���, �����մϴ�.
					if (pUnit->GetUnitAttributeType() == EUnitAttributeType::MECHANICAL)
					{
						continue;
					}

					// ������ �簢���� ���մϴ�.
					Vector2 tObjectPosition = pObject->GetPosition();
					Vector2Int tObjectSize = pObject->GetSize();
					RECT tObjectRect = CGeometry::GetRect(tObjectPosition, tObjectSize);

					// �浹�� �簢���� �����մϴ�.
					RECT tIntersectRect{};

					if (::IntersectRect(&tIntersectRect, &tRangeRect, &tObjectRect))
					{
						if (pUnit->GetAttacked(4) == true)
						{
							pUnit->SetDead(true);
							m_eProjectileState = EProjectileState::DIE;
						}
					}
				}
				m_fDamageDeltaSeconds = 0.0f;
			}
		}
		// �ð��� �� �� ���
		else
		{
			m_eProjectileState = EProjectileState::DIE;
		}
	}
	break;

	case EProjectileState::DIE:
	{
		m_fDeadDelay += CTimeManager::GetManager()->GetDeltaSeconds();

		if (m_fDeadDelay > 0.2f)
		{
			SetReady2Delete(true);
		}
	}
	break;

	default:
		break;
	}
}

void CIrradiateProjectile::LateUpdate()
{
	CProjectile::LateUpdate();
}

void CIrradiateProjectile::Render(HDC _hDC)
{
	CProjectile::Render(_hDC);
}

void CIrradiateProjectile::Release()
{
	CProjectile::Release();
}
