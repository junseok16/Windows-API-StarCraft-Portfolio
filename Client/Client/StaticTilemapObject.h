#pragma once
#include "TilemapObject.h"

class CStaticTilemapObject : public CTilemapObject
{
public:
	CStaticTilemapObject() = default;
	virtual ~CStaticTilemapObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	bool IsImpassableStaticTiles(Vector2Int _tLeftTop, Vector2Int _tileSize);
};

