#include "pch.h"
#include "Game.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "PropertyManager.h"
#include "SoundManager.h"
#include "AStarManager.h"
#include "GameManager.h"

CGame::CGame() {}

CGame::~CGame()
{
	_CrtDumpMemoryLeaks();
}

void CGame::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hDC = ::GetDC(_hWnd);

	// 더블 버퍼링
	::GetClientRect(_hWnd, &m_tRect);
	m_hDCBack = ::CreateCompatibleDC(m_hDC);
	m_hBitmapBack = ::CreateCompatibleBitmap(m_hDC, m_tRect.right, m_tRect.bottom);
	HBITMAP hBitmap = (HBITMAP)::SelectObject(m_hDCBack, m_hBitmapBack);
	::DeleteObject(hBitmap);

	CPropertyManager::GetManager()->Initialize();
	CKeyManager::GetManager()->Initialize();
	CMouseManager::GetManager()->Initialize(_hWnd);
	CTimeManager::GetManager()->Initialize(_hWnd);
	CSoundManager::GetManager()->Initialize();

	CSceneManager::GetManager()->Initialize();
	CCollisionManager::GetManager()->Initialize();
	CResourceManager::GetManager()->Initialize(_hWnd, L"D:\\GitHub\\Windows-API-Portfolio\\Client\\Resources\\");
	
	// 테스트 신으로 이동합니다.
	CSceneManager::GetManager()->OpenScene(ESceneType::TEST);
	
	// 신에 들어간 이후로 활성화되어야 합니다.
	CAStarManager::GetManager()->Initialize();
	CGameManager::GetManager()->Initialize();
}

void CGame::Update()
{
	CKeyManager::GetManager()->Update();
	CMouseManager::GetManager()->Update();
	CTimeManager::GetManager()->Update();
	CCollisionManager::GetManager()->Update();
	CSceneManager::GetManager()->Update();
	CGameManager::GetManager()->Update();
}

void CGame::LateUpdate()
{
	CCollisionManager::GetManager()->LateUpdate();
	CSceneManager::GetManager()->LateUpdate();
	CGameManager::GetManager()->LateUpdate();
}

void CGame::Render()
{
	CTimeManager::GetManager()->Render(m_hDCBack);
	CSceneManager::GetManager()->Render(m_hDCBack);

	// 더블 버퍼링
	::BitBlt(m_hDC, 0, 0, m_tRect.right, m_tRect.bottom, m_hDCBack, 0, 0, SRCCOPY);
	::PatBlt(m_hDCBack, 0, 0, m_tRect.right, m_tRect.bottom, WHITENESS);
}

void CGame::Release()
{
	CMouseManager::GetManager()->Release();
	CKeyManager::GetManager()->Release();
	CTimeManager::GetManager()->Release();
	CSceneManager::GetManager()->Release();
	CCollisionManager::GetManager()->Release();
	CResourceManager::GetManager()->Release();
	CPropertyManager::GetManager()->Release();
	CSoundManager::GetManager()->Release();
	CAStarManager::GetManager()->Release();
	CGameManager::GetManager()->Release();
	ReleaseDC(m_hWnd, m_hDC);
}
