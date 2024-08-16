#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CArmNukeCmdButton : public CCmdButton
{
public:
	CArmNukeCmdButton() = default;
	virtual ~CArmNukeCmdButton() = default;

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

private:
	CUpgradeProperty* pArmNukeProperty = nullptr;
};

