#pragma once
#include "TilemapObject.h"

class CDynamicTilemapObject : public CTilemapObject
{
public:
	CDynamicTilemapObject() = default;
	virtual ~CDynamicTilemapObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void InsertDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize, tagTileInfo _tTileInfo);
	void EraseDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize, tagTileInfo _tTileInfo);
	bool IsImpassableDynamicTiles(Vector2Int _tLeftTop, Vector2Int _tileSize);
};

