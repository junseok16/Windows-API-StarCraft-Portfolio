#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpInfArmrCmdButton : public CCmdButton
{
public:
	CUpInfArmrCmdButton() = default;
	virtual ~CUpInfArmrCmdButton() = default;

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
	CUpgradeProperty* pInfArmrProperty[3]{ nullptr };
};

