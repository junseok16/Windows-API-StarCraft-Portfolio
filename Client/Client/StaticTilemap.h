#pragma once
#include "TilemapObject.h"

class CStaticTilemap : public CTilemapObject
{
public:
	CStaticTilemap() = default;
	virtual ~CStaticTilemap() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

