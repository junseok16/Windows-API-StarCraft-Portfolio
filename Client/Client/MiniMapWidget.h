#pragma once
#include "Widget.h"

class CSpriteUI;

class CMiniMapWidget : public CWidget
{
public:
	CMiniMapWidget() = default;
	virtual ~CMiniMapWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	CSpriteUI* m_pMiniMapSpriteUI = nullptr;

	float m_fSumRefreshDeltaSeconds = 0.0f;

	std::vector<std::vector<tagTileInfo>> m_vecDynamicTiles;
};

