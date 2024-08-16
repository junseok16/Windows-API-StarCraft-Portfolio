#pragma once
#include "CmdButton.h"

class CUseHealCmdButton : public CCmdButton
{
public:
	CUseHealCmdButton() = default;
	virtual ~CUseHealCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

