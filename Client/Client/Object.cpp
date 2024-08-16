#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "ColliderComponent.h"

void CObject::Initialize()
{

}

void CObject::Update()
{
	for (CComponent* component : m_lstComponents)
	{
		component->Update();
	}
}

void CObject::LateUpdate()
{
	for (CComponent* component : m_lstComponents)
	{
		component->LateUpdate();
	}
}

void CObject::Render(HDC _hDC)
{
	for (CComponent* component : m_lstComponents)
	{
		component->Render(_hDC);
	}
}

void CObject::Release()
{
	for_each(m_lstComponents.begin(), m_lstComponents.end(), SAFE_DELETE_FUNCTOR());
	m_lstComponents.clear();
}

void CObject::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CObject::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CObject::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CObject::InsertComponent(CComponent* _pComponent)
{
	VERIFY_NULLPTR(_pComponent);
	m_lstComponents.push_back(_pComponent);
}

void CObject::EraseComponent(CComponent* _pComponent)
{
	// TODO: remove?
	VERIFY_NULLPTR(_pComponent);
	m_lstComponents.remove(_pComponent);
}
