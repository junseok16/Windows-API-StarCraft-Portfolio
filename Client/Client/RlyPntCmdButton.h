#pragma once
#include "CmdButton.h"
class CRlyPntCmdButton : public CCmdButton
{
public:
	CRlyPntCmdButton() = default;
	virtual ~CRlyPntCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

