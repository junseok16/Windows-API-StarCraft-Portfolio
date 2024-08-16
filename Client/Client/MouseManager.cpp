#include "pch.h"
#include "MouseManager.h"

#include "SceneManager.h"
#include "Scene.h"

CMouseManager* CMouseManager::s_pMouseManager = nullptr;

void CMouseManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
}

void CMouseManager::Update()
{
	::GetCursorPos(&m_tMousePosition);
	::ScreenToClient(m_hWnd, &m_tMousePosition);

	Vector2 tCameraPosition = CSceneManager::GetManager()->GetCurScene()->GetCameraPosition();
	Vector2 tCameraLeftTopPosition(tCameraPosition.m_fX - FWINCX * 0.5f, tCameraPosition.m_fY - FWINCY * 0.5f);
	m_tCursorPosition = tCameraLeftTopPosition + GetMousePosition();
}

void CMouseManager::Release()
{
	VERIFY_NULLPTR(s_pMouseManager);
	SAFE_DELETE(s_pMouseManager);
}
