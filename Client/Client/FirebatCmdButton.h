#pragma once
#include "CmdButton.h"

class CFirebatCmdButton : public CCmdButton
{
public:
	CFirebatCmdButton() = default;
	virtual ~CFirebatCmdButton() = default;

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

