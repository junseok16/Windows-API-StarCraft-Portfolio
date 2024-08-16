#pragma once
#include "TilemapObject.h"

class CDynamicTilemap : public CTilemapObject
{
public:
	CDynamicTilemap() = default;
	virtual ~CDynamicTilemap() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

