#pragma once
#include "ButtonUI.h"

class CCmdButton : public CButtonUI
{
public:
	CCmdButton() = default;
	virtual ~CCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

