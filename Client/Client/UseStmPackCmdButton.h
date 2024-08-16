#pragma once
#include "CmdButton.h"

class CUseStmPackCmdButton : public CCmdButton
{
public:
	CUseStmPackCmdButton() = default;
	virtual ~CUseStmPackCmdButton() = default;

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
};

