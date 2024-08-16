#pragma once
#include "CmdButton.h"
class CSiegeTankCmdButton : public CCmdButton
{
public:
	CSiegeTankCmdButton() = default;
	virtual ~CSiegeTankCmdButton() = default;

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

