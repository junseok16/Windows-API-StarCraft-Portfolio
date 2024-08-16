#include "pch.h"
#include "Texture.h"

void CTexture::Release()
{
	SAFE_DELETE(m_pImage);
}

void CTexture::LoadBMP(HWND _hWnd, const std::wstring& _strPath)
{
	HDC hDC = ::GetDC(_hWnd);
	m_hCompatibleDC = ::CreateCompatibleDC(hDC);

	m_hBitmap = (HBITMAP)::LoadImage(nullptr,
		_strPath.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (m_hBitmap == 0)
	{
		::MessageBox(_hWnd, _strPath.c_str(), L"Texture.cpp 오류", MB_ICONWARNING | MB_OK);
		return;
	}

	m_hOldBitmap = (HBITMAP)::SelectObject(m_hCompatibleDC, m_hBitmap);
	::DeleteObject(m_hOldBitmap);

	// bmp 파일의 가로, 세로 길이를 저장합니다.
	BITMAP bitmap{};
	::GetObject(m_hBitmap, sizeof(m_hBitmap), &bitmap);
	m_tSize.m_iWidth = bitmap.bmWidth;
	m_tSize.m_iHeight = bitmap.bmHeight;
}

void CTexture::LoadPNG(HWND _hWnd, const std::wstring& _strPath)
{
	HDC hDC = ::GetDC(_hWnd);
	m_hCompatibleDC = ::CreateCompatibleDC(hDC);

	m_pImage = Gdiplus::Image::FromFile(_strPath.c_str());
	m_tSize.m_iWidth = m_pImage->GetWidth();
	m_tSize.m_iHeight = m_pImage->GetHeight();
}
