#pragma once
#include "CmdButton.h"

class CStopCmdButton : public CCmdButton
{
public:
	CStopCmdButton() = default;
	virtual ~CStopCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

