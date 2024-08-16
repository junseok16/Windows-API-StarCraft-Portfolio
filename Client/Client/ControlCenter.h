#pragma once
#include "SpriteUI.h"

class CControlCenter : public CSpriteUI
{
public:
	CControlCenter() = default;
	virtual ~CControlCenter() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

