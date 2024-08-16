#include "pch.h"
#include "DynamicTilemapObject.h"

#include "Tilemap.h"

void CDynamicTilemapObject::Initialize()
{
	CTilemapObject::Initialize();
}

void CDynamicTilemapObject::Update()
{
	CTilemapObject::Update();
}

void CDynamicTilemapObject::LateUpdate()
{
	CTilemapObject::LateUpdate();
}

void CDynamicTilemapObject::Render(HDC _hDC)
{
	CTilemapObject::Render(_hDC);
}

void CDynamicTilemapObject::Release()
{
	CTilemapObject::Release();
}

void CDynamicTilemapObject::InsertDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize, tagTileInfo _tTileInfo)
{
	CTilemap* pTilemap = GetTilemap();
	for (int32 iX = 0; iX < _tileSize.m_iX; ++iX)
	{
		for (int32 iY = 0; iY < _tileSize.m_iY; ++iY)
		{
			pTilemap->SetTileAt(_tLeftTop.m_iX + iX, _tLeftTop.m_iY + iY, _tTileInfo);
		}
	}
}

void CDynamicTilemapObject::EraseDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize, tagTileInfo _tTileInfo)
{
	CTilemap* pTilemap = GetTilemap();
	for (int32 iX = 0; iX < _tileSize.m_iX; ++iX)
	{
		for (int32 iY = 0; iY < _tileSize.m_iY; ++iY)
		{
			pTilemap->SetTileAt(_tLeftTop.m_iX + iX, _tLeftTop.m_iY + iY, _tTileInfo);
		}
	}
}

bool CDynamicTilemapObject::IsImpassableDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize)
{
	bool bImpassable = false;
	CTilemap* pTilemap = GetTilemap();
	for (int32 iX = 0; iX < _tileSize.m_iX; ++iX)
	{
		for (int32 iY = 0; iY < _tileSize.m_iY; ++iY)
		{
			ETileType tTileType = pTilemap->GetTileAt(_tLeftTop.m_iX + iX, _tLeftTop.m_iY + iY).m_eTileType;
			if (tTileType != ETileType::PASSABLE)
			{
				bImpassable = true;
				break;
			}
		}
	}

	return bImpassable;
}
