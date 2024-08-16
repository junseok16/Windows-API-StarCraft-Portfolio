#pragma once

class CTimeManager final
{
/***************
	메서드
***************/
private:
	CTimeManager() = default;

public:
	~CTimeManager() = default;

public:
	static CTimeManager* GetManager()
	{
		if (s_pTimeManager == nullptr)
		{
			s_pTimeManager = new CTimeManager();
		}
		return s_pTimeManager;
	}

public:
	void Initialize(HWND _hWnd);
	void Update();
	void Render(HDC _hDC);
	void Release();

private:
	void UpdateDeltaTime();
	void UpdateFramePerSecond();

public:
	uint32 GetFPS() const { return m_uiFPS; };
	float GetDeltaSeconds() const { return m_fDeltaSeconds; };


/***************
	데이터 멤버
***************/
public:
	static CTimeManager* s_pTimeManager;

private:
	HWND m_hWnd{};
	uint64 m_ullFrequency = 0;
	uint64 m_ullPreCount = 0;
	float m_fDeltaSeconds = 0.0f;

	uint32 m_uiFrameCount = 0;
	float m_fFrameSeconds = 0.0f;
	uint32 m_uiFPS = 0;
};

