#include "pch.h"
#include "SliderUI.h"

void CSliderUI::Initialize()
{
	CUI::Initialize();
}

void CSliderUI::Update()
{
	CUI::Update();
}

void CSliderUI::LateUpdate()
{
	CUI::LateUpdate();
}

void CSliderUI::Render(HDC _hDC)
{
	CUI::Render(_hDC);
	CGeometry::DrawRectangle(_hDC, m_tBackRectPosition, m_tBackRectSize, m_iBackColor);
	float fOffset = m_tFillRectSize.m_iX * m_fFillAmount;
	CGeometry::DrawRectangle(_hDC, { m_tFillRectPosition.m_fX - (int32)(fOffset * 0.5f), m_tFillRectPosition.m_fY }, { (int32)fOffset, m_tFillRectSize.m_iY }, m_iFillColor);
}

void CSliderUI::Release()
{
	CUI::Release();
}
