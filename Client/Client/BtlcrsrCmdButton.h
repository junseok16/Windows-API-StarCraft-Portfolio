#pragma once
#include "CmdButton.h"

class CBtlcrsrCmdButton : public CCmdButton
{
public:
	CBtlcrsrCmdButton() = default;
	virtual ~CBtlcrsrCmdButton() = default;

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

