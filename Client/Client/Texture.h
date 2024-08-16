#pragma once
#include "ResourceEx.h"

class CTexture : public CResourceEx
{
public:
	CTexture() = default;
	virtual ~CTexture() = default;

public:
	void Release();

public:
	void LoadBMP(HWND _hWnd, const std::wstring& _strPath);
	void LoadPNG(HWND _hWnd, const std::wstring& _strPath);

public:
	Vector2Int GetSize() const { return m_tSize; }
	void SetSize(Vector2Int _tSize) { m_tSize = _tSize; }

	uint32 GetAlpha() const { return m_uiAlpha; }
	void SetTransparency(uint32 _uiAlpha) { m_uiAlpha = _uiAlpha; }

	HDC GetDC() const { return m_hCompatibleDC; }

	Gdiplus::Image* GetImage() { return m_pImage; }

private:
	HDC m_hCompatibleDC{};
	HBITMAP m_hBitmap{};
	HBITMAP m_hOldBitmap{};

	// TODO: png 파일 테스트
	Gdiplus::Image* m_pImage = nullptr;

	// 텍스처의 가로, 세로 길이
	Vector2Int m_tSize{ 0, 0 };

	// 투명하게 할 색상
	uint32 m_uiAlpha = RGB(255, 0, 255);
};

