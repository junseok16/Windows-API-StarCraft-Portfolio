#pragma once

class CMouseManager final
{
/***************
	메서드
***************/
private:
	CMouseManager() = default;

public:
	~CMouseManager() = default;
	CMouseManager(const CMouseManager& rhs) = delete;
	CMouseManager(CMouseManager&& rhs) = delete;
	CMouseManager& operator=(const CMouseManager& rhs) = delete;
	CMouseManager& operator=(CMouseManager&& rhs) = delete;

public:
	static CMouseManager* GetManager() {
		if (s_pMouseManager == nullptr)
		{
			s_pMouseManager = new CMouseManager();
		}
		return s_pMouseManager;
	}

public:
	void Initialize(HWND _hWnd);
	void Update();
	void Release();

public:
	// 마우스의 상대 좌표(0 ~ 800, 0 ~ 600)
	Vector2 GetMousePosition() { return Vector2::PointToVector2(m_tMousePosition); }

	// 커서의 절대 좌표
	Vector2 GetCursorPostion() { return m_tCursorPosition; }
	
/***************
	데이터 멤버
***************/
public:
	static CMouseManager* s_pMouseManager;

private:
	HWND m_hWnd{};
	POINT m_tMousePosition{ 0, 0 };
	Vector2 m_tCursorPosition{ 0.0f, 0.0f };
};

