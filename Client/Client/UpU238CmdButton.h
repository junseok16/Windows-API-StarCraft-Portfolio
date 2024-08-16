#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpU238CmdButton : public CCmdButton
{
public:
	CUpU238CmdButton() = default;
	virtual ~CUpU238CmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

private:
	CUpgradeProperty* pU238ShllProperty = nullptr;
};

