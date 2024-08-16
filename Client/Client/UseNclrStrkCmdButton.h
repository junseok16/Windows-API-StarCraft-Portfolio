#pragma once
#include "CmdButton.h"

class CUseNclrStrkCmdButton : public CCmdButton
{
public:
	CUseNclrStrkCmdButton() = default;
	virtual ~CUseNclrStrkCmdButton() = default;

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

