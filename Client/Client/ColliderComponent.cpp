#include "pch.h"
#include "ColliderComponent.h"

#include "Object.h"
#include "TerranObject.h"

CColliderComponent::CColliderComponent(EColliderType _eColliderType)
	: m_eColliderType(_eColliderType)
{

}

void CColliderComponent::Initialize()
{

}

void CColliderComponent::Update()
{

}

void CColliderComponent::LateUpdate()
{
	
}

void CColliderComponent::Render(HDC _hDC)
{

}

void CColliderComponent::Release()
{

}

bool CColliderComponent::IsCollided(CColliderComponent* _pColliderComponent)
{
	return false;
}

void CColliderComponent::InsertCollider(CColliderComponent* _pColliderComponent)
{
	VERIFY_NULLPTR(_pColliderComponent);
	m_usetColliderComponents.insert(_pColliderComponent);
}

void CColliderComponent::EraseCollider(CColliderComponent* _pColliderComponent)
{
	VERIFY_NULLPTR(_pColliderComponent);
	m_usetColliderComponents.erase(_pColliderComponent);
}

bool CColliderComponent::VerifyCollisionType(CColliderComponent* _pColliderComponent)
{
	uint8 uiType = (uint8)_pColliderComponent->GetCollisionType();

	if (m_uiCollisionFlag & (1 << uiType))
	{
		return true;
	}

	return false;
}

void CColliderComponent::InsertCollisionFlag(ECollisionType _eCollisionType)
{
	m_uiCollisionFlag |= (1 << (uint32)_eCollisionType);
}

void CColliderComponent::EraseCollisionFlag(ECollisionType _eCollisionType)
{
	m_uiCollisionFlag &= ~(1 << (uint32)_eCollisionType);
}
