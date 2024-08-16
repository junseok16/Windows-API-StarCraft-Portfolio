#include "pch.h"
#include "Geometry.h"
using namespace std;

void CGeometry::DrawRectangle(HDC _hDC, Vector2 _tPosition, Vector2Int _tSize, int32 _iColor)
{
	HPEN hPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	HGDIOBJ hOldPen = SelectObject(_hDC, hPen);

	HBRUSH hBrush = ::CreateSolidBrush(_iColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(_hDC, hBrush);
	
	int32 iLeft = (int32)(_tPosition.m_fX - _tSize.m_iWidth * 0.5f);
	int32 iTop = (int32)(_tPosition.m_fY - _tSize.m_iHeight * 0.5f);
	int32 iRight = (int32)(_tPosition.m_fX + _tSize.m_iWidth * 0.5f);
	int32 iBottom = (int32)(_tPosition.m_fY + _tSize.m_iHeight * 0.5f);
	::Rectangle(_hDC, iLeft, iTop, iRight, iBottom);

	::SelectObject(_hDC, hOldBrush);
	::DeleteObject(hBrush);

	SelectObject(_hDC, hOldPen);
	DeleteObject(hPen);
}

void CGeometry::DrawTransparentRectangle(HDC _hDC, Vector2 _tPosition, Vector2Int _tSize, int32 _iColor)
{
	HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(_hDC, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 2, _iColor);
	HGDIOBJ hOldPen = SelectObject(_hDC, hPen);

	int32 iLeft = (int32)(_tPosition.m_fX - _tSize.m_iWidth * 0.5f);
	int32 iTop = (int32)(_tPosition.m_fY - _tSize.m_iHeight * 0.5f);
	int32 iRight = (int32)(_tPosition.m_fX + _tSize.m_iWidth * 0.5f);
	int32 iBottom = (int32)(_tPosition.m_fY + _tSize.m_iHeight * 0.5f);
	::Rectangle(_hDC, iLeft, iTop, iRight, iBottom);

	SelectObject(_hDC, hOldPen);
	DeleteObject(hPen);

	::SelectObject(_hDC, hOldBrush);
	::DeleteObject(hBrush);
}

void CGeometry::DrawCircle(HDC _hDC, Vector2 _tPosition, float _fRadius, int32 _iColor)
{
	// TODO: 색상
	::Ellipse(_hDC, (int32)(_tPosition.m_fX - _fRadius), (int32)(_tPosition.m_fY - _fRadius), (int32)(_tPosition.m_fX + _fRadius), (int32)(_tPosition.m_fY + _fRadius));
}

void CGeometry::DrawLine(HDC _hDC, Vector2 _tBeginPosition, Vector2 _tEndPosition, int32 _iColor)
{
	// TODO: 색상
	HPEN hPen = ::CreatePen(PS_SOLID, 1, _iColor);
	HPEN hOldPen = (HPEN)::SelectObject(_hDC, hPen);
	::MoveToEx(_hDC, (int32)_tBeginPosition.m_fX, (int32)_tBeginPosition.m_fY, nullptr);
	::LineTo(_hDC, (int32)_tEndPosition.m_fX, (int32)_tEndPosition.m_fY);
	::SelectObject(_hDC, hOldPen);
	::DeleteObject(hPen);
}

void CGeometry::DrawString(HDC _hDC, Vector2 _tPosition, const wstring& _wStr, int32 _iColor)
{
	// 텍스트의 색상을 설정합니다.
	::SetTextColor(_hDC, _iColor);
	::SetBkMode(_hDC, TRANSPARENT);
	::TextOut(_hDC, (int32)_tPosition.m_fX, (int32)_tPosition.m_fY, _wStr.c_str(), (int32)_wStr.size());
	::SetTextColor(_hDC, RGB(0, 0, 0));
	::SetBkMode(_hDC, OPAQUE);
}

RECT CGeometry::GetRect(Vector2 _tPosition, Vector2Int _tSize)
{
	return RECT
	{
		(int32)(_tPosition.m_fX - _tSize.m_iWidth * 0.5f),
		(int32)(_tPosition.m_fY - _tSize.m_iHeight * 0.5f),
		(int32)(_tPosition.m_fX + _tSize.m_iWidth * 0.5f),
		(int32)(_tPosition.m_fY + _tSize.m_iHeight * 0.5f)
	};
}

Vector2Int CGeometry::ToTilePosition(Vector2 _tPosition)
{
	return Vector2Int{ (int32)(_tPosition.m_fX) / ITILECX, (int32)(_tPosition.m_fY) / ITILECY };
}
