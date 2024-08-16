#include "pch.h"
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Object.h"
#include "Scene.h"

CRectangleColliderComponent::CRectangleColliderComponent()
	: CColliderComponent(EColliderType::RECTANGLE)
{

}

void CRectangleColliderComponent::Initialize()
{
	CColliderComponent::Initialize();
}

void CRectangleColliderComponent::Update()
{
	CColliderComponent::Update();
}

void CRectangleColliderComponent::LateUpdate()
{
	CColliderComponent::LateUpdate();
}

void CRectangleColliderComponent::Render(HDC _hDC)
{
	CColliderComponent::Render(_hDC);

	if (m_bDebug == false) { return; }
	Vector2 tOwnerPosition = m_pComponentOwner->GetPosition();
	
	if (m_bScroll == true)
	{
		// ���� ���� ī�޶� ��ġ�� �ҷ��ɴϴ�.
		CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
		Vector2 tCameraPosition = pCurScene->GetCameraPosition();

		// ���� ������Ʈ�� ��ġ�� ��ũ�ѷ� �����մϴ�.
		tOwnerPosition.m_fX = tOwnerPosition.m_fX - (tCameraPosition.m_fX - FWINCX * 0.5f);
		tOwnerPosition.m_fY = tOwnerPosition.m_fY - (tCameraPosition.m_fY - FWINCY * 0.5f);
	}

	// �簢�� �ݶ��̴��� �����մϴ�.
	CGeometry::DrawRectangle(_hDC, tOwnerPosition, m_tColliderSize, RGB(255, 255, 0));
}

void CRectangleColliderComponent::Release()
{
	CColliderComponent::Release();
}

bool CRectangleColliderComponent::IsCollided(CColliderComponent* _pColliderComponent)
{
	if (CColliderComponent::VerifyCollisionType(_pColliderComponent) == false)
	{
		return false;
	}

	switch (_pColliderComponent->GetColliderType())
	{
	case EColliderType::RECTANGLE:
		return CCollisionManager::IntersectRect2Rect(this, static_cast<CRectangleColliderComponent*>(_pColliderComponent));

	case EColliderType::CIRCLE:
		return CCollisionManager::IntersectRect2Circle(this, static_cast<CCircleColliderComponent*>(_pColliderComponent));
	}
	return false;
}

RECT CRectangleColliderComponent::GetRect()
{
	CObject* pOwner = GetComponentOwner();
	Vector2Int tOwnerSize = pOwner->GetSize();
	Vector2 tOwnerPosition = pOwner->GetPosition();

	return RECT
	{ 
		(int32)(tOwnerPosition.m_fX - (tOwnerSize.m_iWidth * 0.5f)),
		(int32)(tOwnerPosition.m_fY - (tOwnerSize.m_iHeight * 0.5f)),
		(int32)(tOwnerPosition.m_fX + (tOwnerSize.m_iWidth * 0.5f)),
		(int32)(tOwnerPosition.m_fY + (tOwnerSize.m_iHeight * 0.5f))
	};
}
