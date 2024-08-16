#pragma once
#include "CmdButton.h"

class CRfnryCmdButton : public CCmdButton
{
public:
	CRfnryCmdButton() = default;
	virtual ~CRfnryCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

