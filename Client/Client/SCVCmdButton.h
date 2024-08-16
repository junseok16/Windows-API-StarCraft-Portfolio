#pragma once
#include "CmdButton.h"

class CSCVCmdButton : public CCmdButton
{
public:
	CSCVCmdButton() = default;
	virtual ~CSCVCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

