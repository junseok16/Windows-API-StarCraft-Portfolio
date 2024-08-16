#pragma once

class CGeometry final
{
public:
	static void DrawRectangle(HDC _hDC, Vector2 _tPosition, Vector2Int _tSize, int32 _iColor);

	static void DrawTransparentRectangle(HDC _hDC, Vector2 _tPosition, Vector2Int _tSize, int32 _iColor);

	static void DrawCircle(HDC _hDC, Vector2 _tPosition, float _fRadius, int32 _iColor);

	static void DrawLine(HDC _hDC, Vector2 _tFromPosition, Vector2 _tToPosition, int32 _iColor);

	static void DrawString(HDC _hDC, Vector2 _tPosition, const std::wstring& _wStr, int32 _iColor);

	static RECT GetRect(Vector2 _tPosition, Vector2Int _tSize);

	static Vector2Int ToTilePosition(Vector2 _tPosition);
};

