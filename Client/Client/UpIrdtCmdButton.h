#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpIrdtCmdButton : public CCmdButton
{
public:
	CUpIrdtCmdButton() = default;
	virtual ~CUpIrdtCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

private:
	CUpgradeProperty* pIrradiateProperty = nullptr;
};

