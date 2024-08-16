#pragma once

class CMouseManager final
{
/***************
	�޼���
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
	// ���콺�� ��� ��ǥ(0 ~ 800, 0 ~ 600)
	Vector2 GetMousePosition() { return Vector2::PointToVector2(m_tMousePosition); }

	// Ŀ���� ���� ��ǥ
	Vector2 GetCursorPostion() { return m_tCursorPosition; }
	
/***************
	������ ���
***************/
public:
	static CMouseManager* s_pMouseManager;

private:
	HWND m_hWnd{};
	POINT m_tMousePosition{ 0, 0 };
	Vector2 m_tCursorPosition{ 0.0f, 0.0f };
};

