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

			// 두 콜라이더가 충돌한 경우
			if (pSrc->IsCollided(pDst) == true)
			{
				// 이전에 충돌하지 않고 방금 충돌한 경우
				unordered_set<CColliderComponent*>& usetColliderComponents = pSrc->GetColliderComponents();
				if (usetColliderComponents.find(pDst) == usetColliderComponents.end())
				{
					pSrc->GetComponentOwner()->OnCollisionEnter2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionEnter2D(pDst, pSrc);

					// TODO: 참조로 전달하고 있으므로 값이 잘 저장되는지 확인해야 합니다.
					usetColliderComponents.insert(pSrc);
					usetColliderComponents.insert(pDst);
				}
				// 이전에 이미 충돌한 경우
				else
				{
					pSrc->GetComponentOwner()->OnCollisionStay2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionStay2D(pDst, pSrc);
				}
			}
			// 두 콜라이더가 충돌하지 않은 경우
			else
			{
				// 이전에 충돌했다가 방금 충돌하지 않은 경우
				unordered_set<CColliderComponent*>& usetColliderComponents = pSrc->GetColliderComponents();
				if (usetColliderComponents.find(pDst) != usetColliderComponents.end())
				{
					pSrc->GetComponentOwner()->OnCollisionExit2D(pSrc, pDst);
					pDst->GetComponentOwner()->OnCollisionExit2D(pDst, pSrc);

					// TODO: 참조로 전달하고 있으므로 값이 잘 저장되는지 확인해야 합니다.
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

		// 커서 오브젝트는 제외합니다.
		if (pTerranObject == nullptr)
		{
			iter++;
			continue;
		}

		// 죽은 오브젝트의 콜라이더 컴포넌트를 없앱니다.
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
	정적 함수
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
	// 첫 번째 사각형 콜라이더의 위치와 반지름을 구합니다.
	CObject* pScrObject = _pSrc->GetComponentOwner();
	Vector2 tSrcPosition = pScrObject->GetPosition();
	Vector2Int tSrcSize = pScrObject->GetSize();
	float fSrcRadius = (float)min(tSrcSize.m_iWidth, tSrcSize.m_iHeight);

	// 두 번째 원 콜라이더의 위치와 반지름을 구합니다.
	CObject* pDstObject = _pDst->GetComponentOwner();
	Vector2 tDstPosition = pDstObject->GetPosition();
	float fDstRadius = _pDst->GetRadius();

	return tSrcPosition.Distance(tDstPosition) <= fSrcRadius + fDstRadius;
}

bool CCollisionManager::IntersectCircle2Circle(CCircleColliderComponent* _pSrc, CCircleColliderComponent* _pDst)
{
	// 첫 번째 원 콜라이더의 위치와 반지름을 구합니다.
	CObject* pScrObject = _pSrc->GetComponentOwner();
	Vector2 tSrcPosition = pScrObject->GetPosition();
	float fSrcRadius = _pSrc->GetRadius();

	// 두 번째 원 콜라이더의 위치와 반지름을 구합니다.
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

		// 충돌한 사각형의 밑변과 높이를 구합니다.
		int32 iIntersectWidth = tIntersectRect.right - tIntersectRect.left;
		int32 iIntersectHeight = tIntersectRect.bottom - tIntersectRect.top;

		// 상하 충돌인지 확인합니다.
		if (iIntersectWidth > iIntersectHeight)
		{
			// 위에서 충돌한 경우, 높이만큼 위로 밉니다.
			if (tIntersectRect.top == tDst.top)
			{
				tSrcPosition.m_fY -= iIntersectHeight * _fRatio;
				tDstPosition.m_fY += iIntersectHeight * _fRatio;
			}
			// 아래에서 충돌한 경우, 높이만큼 아래로 밉니다.
			else if (tIntersectRect.bottom == tDst.bottom)
			{
				tSrcPosition.m_fY += iIntersectHeight * _fRatio;
				tDstPosition.m_fY -= iIntersectHeight * _fRatio;
			}
		}

		// 좌우 충돌인지 확인합니다.
		else
		{
			// 왼쪽에서 충돌한 경우, 너비만큼 위로 밉니다.
			if (tIntersectRect.left == tDst.left)
			{
				tSrcPosition.m_fX -= iIntersectWidth * _fRatio;
				tDstPosition.m_fX += iIntersectWidth * _fRatio;
			}
			// 오른쪽에서 충돌한 경우, 너비만큼 아래로 밉니다.
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

		// 충돌한 사각형의 밑변과 높이를 구합니다.
		int32 iIntersectWidth = tIntersectRect.right - tIntersectRect.left;
		int32 iIntersectHeight = tIntersectRect.bottom - tIntersectRect.top;

		// 상하 충돌인지 확인합니다.
		if (iIntersectWidth > iIntersectHeight)
		{
			// 위에서 충돌한 경우, 높이만큼 위로 밉니다.
			if (tIntersectRect.top == tDst.top)
			{
				tSrcPosition.m_fY -= iIntersectHeight * _fRatio;
			}
			// 아래에서 충돌한 경우, 높이만큼 아래로 밉니다.
			else if (tIntersectRect.bottom == tDst.bottom)
			{
				tSrcPosition.m_fY += iIntersectHeight * _fRatio;
			}
		}

		// 좌우 충돌인지 확인합니다.
		else
		{
			// 왼쪽에서 충돌한 경우, 너비만큼 위로 밉니다.
			if (tIntersectRect.left == tDst.left)
			{
				tSrcPosition.m_fX -= iIntersectWidth * _fRatio;
			}
			// 오른쪽에서 충돌한 경우, 너비만큼 아래로 밉니다.
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
