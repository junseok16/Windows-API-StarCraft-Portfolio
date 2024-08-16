#include "pch.h"
#include "CollisionManager.h"
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Object.h"
#include "TerranObject.h"
using namespace std;

CCollisionManager* CCollisionManager::s_pCollisionManager = nullptr;

void CCollisionManager::Initialize()
{

}

void CCollisionManager::Update()
{
	vector<CColliderComponent*>& vecColliderComponents = m_vecColliderComponents;
	
	uint32 uiSize = vecColliderComponents.size();
	for (uint32 outerLoopIndex = 0; outerLoopIndex < uiSize; ++outerLoopIndex)
	{
		for (uint32 innerLoopIndex = outerLoopIndex + 1; innerLoopIndex < uiSize; ++innerLoopIndex)
		{
			CColliderComponent* pSrc = vecColliderComponents[innerLoopIndex];
			CColliderComponent* pDst = vecColliderComponents[outerLoopIndex];

			// �� �ݶ��̴��� �浹�� ���
			if (pSrc->IsCollided(pDst) == true)
			{
				// ������ �浹���� �ʰ� ��� �浹�� ���
				unordered_set<CColliderComponent*>& usetColliderComponents = pSrc->GetColliderComponents();
				if (usetColliderComponents.find(pDst) == usetColliderComponents.end())
				{
					pSrc->GetComponentOwner()->OnCollisionEnter2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionEnter2D(pDst, pSrc);

					// TODO: ������ �����ϰ� �����Ƿ� ���� �� ����Ǵ��� Ȯ���ؾ� �մϴ�.
					usetColliderComponents.insert(pSrc);
					usetColliderComponents.insert(pDst);
				}
				// ������ �̹� �浹�� ���
				else
				{
					pSrc->GetComponentOwner()->OnCollisionStay2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionStay2D(pDst, pSrc);
				}
			}
			// �� �ݶ��̴��� �浹���� ���� ���
			else
			{
				// ������ �浹�ߴٰ� ��� �浹���� ���� ���
				unordered_set<CColliderComponent*>& usetColliderComponents = pSrc->GetColliderComponents();
				if (usetColliderComponents.find(pDst) != usetColliderComponents.end())
				{
					pSrc->GetComponentOwner()->OnCollisionExit2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionExit2D(pDst, pSrc);

					// TODO: ������ �����ϰ� �����Ƿ� ���� �� ����Ǵ��� Ȯ���ؾ� �մϴ�.
					usetColliderComponents.erase(pSrc);
					usetColliderComponents.erase(pDst);
				}
			}
		}
	}
}

void CCollisionManager::LateUpdate()
{
	for (auto iter = m_vecColliderComponents.begin(); iter != m_vecColliderComponents.end();)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>((*iter)->GetComponentOwner());

		// Ŀ�� ������Ʈ�� �����մϴ�.
		if (pTerranObject == nullptr)
		{
			iter++;
			continue;
		}

		// ���� ������Ʈ�� �ݶ��̴� ������Ʈ�� ���۴ϴ�.
		if (pTerranObject->GetDead())
		{
			iter = m_vecColliderComponents.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void CCollisionManager::Release()
{
	VERIFY_NULLPTR(s_pCollisionManager);
	SAFE_DELETE(s_pCollisionManager);
}

void CCollisionManager::InsertColliderComponent(CColliderComponent* _pColliderComponent)
{
	VERIFY_NULLPTR(_pColliderComponent);
	m_vecColliderComponents.push_back(_pColliderComponent);
}

void CCollisionManager::EraseColliderComponent(CColliderComponent* _pColliderComponent)
{
	VERIFY_NULLPTR(_pColliderComponent);
	m_vecColliderComponents.erase(remove(m_vecColliderComponents.begin(), m_vecColliderComponents.end(), _pColliderComponent), m_vecColliderComponents.end());
}

/***************
	���� �Լ�
***************/
bool CCollisionManager::IntersectRect2Rect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst)
{
	RECT tRect{};
	CObject* pSrcOwner = _pSrc->GetComponentOwner();
	CObject* pDstOwner = _pDst->GetComponentOwner();
	
	RECT tSrcRect = CGeometry::GetRect(pSrcOwner->GetPosition(), pSrcOwner->GetSize());
	RECT tDstRect = CGeometry::GetRect(pDstOwner->GetPosition(), pDstOwner->GetSize());
	return ::IntersectRect(&tRect, &tSrcRect, &tDstRect);
}

bool CCollisionManager::IntersectRect2Circle(CRectangleColliderComponent* _pSrc, CCircleColliderComponent* _pDst)
{
	// ù ��° �簢�� �ݶ��̴��� ��ġ�� �������� ���մϴ�.
	CObject* pScrObject = _pSrc->GetComponentOwner();
	Vector2 tSrcPosition = pScrObject->GetPosition();
	Vector2Int tSrcSize = pScrObject->GetSize();
	float fSrcRadius = (float)min(tSrcSize.m_iWidth, tSrcSize.m_iHeight);

	// �� ��° �� �ݶ��̴��� ��ġ�� �������� ���մϴ�.
	CObject* pDstObject = _pDst->GetComponentOwner();
	Vector2 tDstPosition = pDstObject->GetPosition();
	float fDstRadius = _pDst->GetRadius();

	return tSrcPosition.Distance(tDstPosition) <= fSrcRadius + fDstRadius;
}

bool CCollisionManager::IntersectCircle2Circle(CCircleColliderComponent* _pSrc, CCircleColliderComponent* _pDst)
{
	// ù ��° �� �ݶ��̴��� ��ġ�� �������� ���մϴ�.
	CObject* pScrObject = _pSrc->GetComponentOwner();
	Vector2 tSrcPosition = pScrObject->GetPosition();
	float fSrcRadius = _pSrc->GetRadius();

	// �� ��° �� �ݶ��̴��� ��ġ�� �������� ���մϴ�.
	CObject* pDstObject = _pDst->GetComponentOwner();
	Vector2 tDstPosition = pDstObject->GetPosition();
	float fDstRadius = _pDst->GetRadius();

	return tSrcPosition.Distance(tDstPosition) <= fSrcRadius + fDstRadius;
}

void CCollisionManager::BlockRect2Rect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst, float _fRatio)
{
	RECT tSrc = _pSrc->GetRect();
	RECT tDst = _pDst->GetRect();
	RECT tIntersectRect{};

	if (::IntersectRect(&tIntersectRect, &tSrc, &tDst))
	{
		Vector2 tSrcPosition = _pSrc->GetComponentOwner()->GetPosition();
		Vector2 tDstPosition = _pDst->GetComponentOwner()->GetPosition();

		// �浹�� �簢���� �غ��� ���̸� ���մϴ�.
		int32 iIntersectWidth = tIntersectRect.right - tIntersectRect.left;
		int32 iIntersectHeight = tIntersectRect.bottom - tIntersectRect.top;

		// ���� �浹���� Ȯ���մϴ�.
		if (iIntersectWidth > iIntersectHeight)
		{
			// ������ �浹�� ���, ���̸�ŭ ���� �Ӵϴ�.
			if (tIntersectRect.top == tDst.top)
			{
				tSrcPosition.m_fY -= iIntersectHeight * _fRatio;
				tDstPosition.m_fY += iIntersectHeight * _fRatio;
			}
			// �Ʒ����� �浹�� ���, ���̸�ŭ �Ʒ��� �Ӵϴ�.
			else if (tIntersectRect.bottom == tDst.bottom)
			{
				tSrcPosition.m_fY += iIntersectHeight * _fRatio;
				tDstPosition.m_fY -= iIntersectHeight * _fRatio;
			}
		}

		// �¿� �浹���� Ȯ���մϴ�.
		else
		{
			// ���ʿ��� �浹�� ���, �ʺ�ŭ ���� �Ӵϴ�.
			if (tIntersectRect.left == tDst.left)
			{
				tSrcPosition.m_fX -= iIntersectWidth * _fRatio;
				tDstPosition.m_fX += iIntersectWidth * _fRatio;
			}
			// �����ʿ��� �浹�� ���, �ʺ�ŭ �Ʒ��� �Ӵϴ�.
			else if (tIntersectRect.right == tDst.right)
			{
				tSrcPosition.m_fX += iIntersectWidth * _fRatio;
				tSrcPosition.m_fX -= iIntersectWidth * _fRatio;
			}
		}

		_pSrc->GetComponentOwner()->SetPosition(tSrcPosition);
		_pDst->GetComponentOwner()->SetPosition(tDstPosition);
	}
}

void CCollisionManager::BlockSrcRectFromDstRect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst, float _fRatio)
{
	RECT tSrc = _pSrc->GetRect();
	RECT tDst = _pDst->GetRect();
	RECT tIntersectRect{};

	if (::IntersectRect(&tIntersectRect, &tSrc, &tDst))
	{
		Vector2 tSrcPosition = _pSrc->GetComponentOwner()->GetPosition();
		Vector2 tDstPosition = _pDst->GetComponentOwner()->GetPosition();

		// �浹�� �簢���� �غ��� ���̸� ���մϴ�.
		int32 iIntersectWidth = tIntersectRect.right - tIntersectRect.left;
		int32 iIntersectHeight = tIntersectRect.bottom - tIntersectRect.top;

		// ���� �浹���� Ȯ���մϴ�.
		if (iIntersectWidth > iIntersectHeight)
		{
			// ������ �浹�� ���, ���̸�ŭ ���� �Ӵϴ�.
			if (tIntersectRect.top == tDst.top)
			{
				tSrcPosition.m_fY -= iIntersectHeight * _fRatio;
			}
			// �Ʒ����� �浹�� ���, ���̸�ŭ �Ʒ��� �Ӵϴ�.
			else if (tIntersectRect.bottom == tDst.bottom)
			{
				tSrcPosition.m_fY += iIntersectHeight * _fRatio;
			}
		}

		// �¿� �浹���� Ȯ���մϴ�.
		else
		{
			// ���ʿ��� �浹�� ���, �ʺ�ŭ ���� �Ӵϴ�.
			if (tIntersectRect.left == tDst.left)
			{
				tSrcPosition.m_fX -= iIntersectWidth * _fRatio;
			}
			// �����ʿ��� �浹�� ���, �ʺ�ŭ �Ʒ��� �Ӵϴ�.
			else if (tIntersectRect.right == tDst.right)
			{
				tSrcPosition.m_fX += iIntersectWidth * _fRatio;
			}
		}

		_pSrc->GetComponentOwner()->SetPosition(tSrcPosition);
	}
}

void CCollisionManager::BlockCircle2Circle(CCircleColliderComponent* _pSrc, CCircleColliderComponent* _pDst, float _fRatio)
{

}
