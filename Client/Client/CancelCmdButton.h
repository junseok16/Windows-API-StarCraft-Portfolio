#pragma once
#include "CmdButton.h"

class CCancelCmdButton : public CCmdButton
{
public:
	CCancelCmdButton() = default;
	virtual ~CCancelCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

