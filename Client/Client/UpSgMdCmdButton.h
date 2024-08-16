#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpSgMdCmdButton : public CCmdButton
{
public:
	CUpSgMdCmdButton() = default;
	virtual ~CUpSgMdCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

private:
	CUpgradeProperty* pSgMdProperty = nullptr;
};

