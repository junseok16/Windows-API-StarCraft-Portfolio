#include "pch.h"
#include "CircleColliderComponent.h"
#include "RectangleColliderComponent.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Object.h"
#include "Scene.h"

CCircleColliderComponent::CCircleColliderComponent()
	: CColliderComponent(EColliderType::CIRCLE)
{

}

void CCircleColliderComponent::Initialize()
{
	CColliderComponent::Initialize();
}

void CCircleColliderComponent::Update()
{
	CColliderComponent::Update();
}

void CCircleColliderComponent::LateUpdate()
{
	CColliderComponent::LateUpdate();
}

void CCircleColliderComponent::Render(HDC _hDC)
{
	CColliderComponent::Render(_hDC);

	if (m_bDebug == false) { return; }
	Vector2 tOwnerPosition = m_pComponentOwner->GetPosition();

	// 현재 신의 카메라 위치를 불러옵니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	// 현재 오브젝트의 위치를 스크롤로 보정합니다.
	tOwnerPosition.m_fX = tOwnerPosition.m_fX - (tCameraPosition.m_fX - FWINCX * 0.5f);
	tOwnerPosition.m_fY = tOwnerPosition.m_fY - (tCameraPosition.m_fY - FWINCY * 0.5f);
	
	// 원 콜라이더를 투명하게 렌더합니다.
	HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(_hDC, hBrush);
	CGeometry::DrawCircle(_hDC, tOwnerPosition, m_fRadius, 0);
	::SelectObject(_hDC, hOldBrush);
	::DeleteObject(hBrush);
}

void CCircleColliderComponent::Release()
{
	CColliderComponent::Release();
}

bool CCircleColliderComponent::IsCollided(CColliderComponent* _pColliderComponent)
{
	if (CColliderComponent::VerifyCollisionType(_pColliderComponent) == false)
	{
		return false;
	}

	switch (_pColliderComponent->GetColliderType())
	{
	case EColliderType::RECTANGLE:
		return CCollisionManager::IntersectRect2Circle(static_cast<CRectangleColliderComponent*>(_pColliderComponent), this);

	case EColliderType::CIRCLE:
		return CCollisionManager::IntersectCircle2Circle(this, static_cast<CCircleColliderComponent*>(_pColliderComponent));
	}
	return false;
}
