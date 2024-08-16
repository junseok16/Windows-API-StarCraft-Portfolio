#pragma once
#include "CmdButton.h"

class CStrprtCmdButton : public CCmdButton
{
public:
	CStrprtCmdButton() = default;
	virtual ~CStrprtCmdButton() = default;

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

