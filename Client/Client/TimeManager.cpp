#include "pch.h"
#include "TimeManager.h"
using namespace std;

CTimeManager* CTimeManager::s_pTimeManager = nullptr;

void CTimeManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
    ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_ullPreCount));
    ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_ullFrequency));
}

void CTimeManager::Update()
{
	UpdateDeltaTime();
	UpdateFramePerSecond();
}

void CTimeManager::Render(HDC _hDC)
{
	// TODO: 프레임율과 델타 타임을 렌더합니다.
}

void CTimeManager::Release()
{
	VERIFY_NULLPTR(s_pTimeManager);
	SAFE_DELETE(s_pTimeManager);
}

void CTimeManager::UpdateDeltaTime()
{
	uint64 ullCurCount = 0;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&ullCurCount));
	m_fDeltaSeconds = (ullCurCount - m_ullPreCount) / static_cast<float>(m_ullFrequency);
	m_ullPreCount = ullCurCount;
}

void CTimeManager::UpdateFramePerSecond()
{
	++m_uiFrameCount;
	m_fFrameSeconds += m_fDeltaSeconds;

	if (m_fFrameSeconds >= 1.0f)
	{
		m_uiFPS = static_cast<uint32>(m_uiFrameCount / m_fFrameSeconds);
		m_fFrameSeconds = 0.0f;
		m_uiFrameCount = 0;
	}
}
