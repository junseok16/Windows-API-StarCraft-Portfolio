#include "pch.h"
#include "StaticTilemapObject.h"

#include "Tilemap.h"

void CStaticTilemapObject::Initialize()
{
	CTilemapObject::Initialize();
}

void CStaticTilemapObject::Update()
{
	CTilemapObject::Update();
}

void CStaticTilemapObject::LateUpdate()
{
	CTilemapObject::LateUpdate();
}

void CStaticTilemapObject::Render(HDC _hDC)
{
	CTilemapObject::Render(_hDC);
}

void CStaticTilemapObject::Release()
{
	CTilemapObject::Release();
}

bool CStaticTilemapObject::IsImpassableStaticTiles(Vector2Int _tLeftTop, Vector2Int _tileSize)
{
	bool bImpassable = false;
	CTilemap* pTilemap = GetTilemap();
	for (int32 iX = 0; iX < _tileSize.m_iX; ++iX)
	{
		for (int32 iY = 0; iY < _tileSize.m_iY; ++iY)
		{
			if (pTilemap->GetTileAt(_tLeftTop.m_iX + iX, _tLeftTop.m_iY + iY).m_eTileType == ETileType::IMPASSABLE)
			{
				bImpassable = true;
				break;
			}
		}
	}

	return bImpassable;
}
