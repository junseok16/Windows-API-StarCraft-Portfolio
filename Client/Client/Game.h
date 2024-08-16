#pragma once

class CGame final {
public:
	CGame();
	~CGame();

public:
	void Initialize(HWND _hWnd);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:


private:
	HWND m_hWnd{};
	HDC m_hDC{};

	// 더블 버퍼링
	RECT m_tRect{};
	HDC m_hDCBack{};
	HBITMAP m_hBitmapBack{};
};

