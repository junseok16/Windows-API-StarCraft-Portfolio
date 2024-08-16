#pragma once
#include "CmdButton.h"

class CMarineCmdButton : public CCmdButton
{
public:
	CMarineCmdButton() = default;
	virtual ~CMarineCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

