#include "pch.h"
#include "TextUI.h"

void CTextUI::Initialize()
{
	CUI::Initialize();
}

void CTextUI::Update()
{
	CUI::Update();
	if (!m_bUIActive) { return; }
}

void CTextUI::LateUpdate()
{
	CUI::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CTextUI::Render(HDC _hDC)
{
	CUI::Render(_hDC);
	if (!m_bUIActive) { return; }

	HFONT hFont = ::CreateFont(
		m_iFontHeight,	// cHeight
		0,				// cWidth
		0,				// cEscapement
		0,				// cOrientation
		m_iFontWeight,	// cWeight
		0,				// bItalic
		0,				// bUnderline
		0,				// bStrikeOut
		ANSI_CHARSET,	// iCharSet
		0,				// iOutPrecision
		0,				// iClipPrecision
		0,				// iQuality
		0,				// iPitchAndFamily
		L"Calibri"		// pszFaceName
		);

	HFONT hOldFont = (HFONT)::SelectObject(_hDC, hFont);
	CGeometry::DrawString(_hDC, m_tPosition, m_strText, m_iFontColor);
	::SelectObject(_hDC, hOldFont);
	::DeleteObject(hFont);
}

void CTextUI::Release()
{
	CUI::Release();
}
