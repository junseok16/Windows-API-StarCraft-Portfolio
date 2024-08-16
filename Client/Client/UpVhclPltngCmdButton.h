#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpVhclPltngCmdButton : public CCmdButton
{
public:
	CUpVhclPltngCmdButton() = default;
	virtual ~CUpVhclPltngCmdButton() = default;

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
	CUpgradeProperty* pVhclPltngProperty[3]{ nullptr };
};

