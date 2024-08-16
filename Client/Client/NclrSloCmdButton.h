#pragma once
#include "CmdButton.h"
class CNclrSloCmdButton : public CCmdButton
{
public:
	CNclrSloCmdButton() = default;
	virtual ~CNclrSloCmdButton() = default;

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

