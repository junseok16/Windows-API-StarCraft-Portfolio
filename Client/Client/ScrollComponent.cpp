#include "pch.h"
#include "ScrollComponent.h"
#include "SceneManager.h"
#include "Object.h"
#include "Scene.h"
using namespace std;

void CScrollComponent::Initialize()
{

}

void CScrollComponent::Update()
{

}

void CScrollComponent::LateUpdate()
{
	VERIFY_NULLPTR(m_pComponentOwner);
	
	// 플레이어의 위치를 구합니다.
	Vector2 position = m_pComponentOwner->GetPosition();
	//position.m_fX = clamp(position.m_fX, FWINCX * 0.5f, FWORLDCX - FWINCX * 0.5f);
	//position.m_fY = clamp(position.m_fY, FWINCY * 0.5f, FWORLDCY - FWINCY * 0.5f);

	// 플레이어의 위치를 카메라 위치로 설정합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	pCurScene->SetCameraPosition(position);
}

void CScrollComponent::Render(HDC _hDC)
{

}

void CScrollComponent::Release()
{

}
