#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpInfWpnCmdButton : public CCmdButton
{
public:
	CUpInfWpnCmdButton() = default;
	virtual ~CUpInfWpnCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

private:
	void VerifyTechTree();
	bool VerifyResource();

private:
	CUpgradeProperty* pInfWpnProperty[3]{ nullptr };
};

