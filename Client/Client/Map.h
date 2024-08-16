#pragma once
#include "SpriteUI.h"

class CMapUI : public CSpriteUI
{
public:
	CMapUI() = default;
	virtual ~CMapUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

