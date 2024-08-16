#pragma once
#include "CmdButton.h"
class CCancelLastCmdButton : public CCmdButton
{
public:
	CCancelLastCmdButton() = default;
	virtual ~CCancelLastCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

