#pragma once
#include "CmdButton.h"

class CMoveCmdButton : public CCmdButton
{
public:
	CMoveCmdButton() = default;
	virtual ~CMoveCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;
};

