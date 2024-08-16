#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpVhclWpnCmdButton : public CCmdButton
{
public:
	CUpVhclWpnCmdButton() = default;
	virtual ~CUpVhclWpnCmdButton() = default;

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
	CUpgradeProperty* pVhclWpnProperty[3]{ nullptr };
};

