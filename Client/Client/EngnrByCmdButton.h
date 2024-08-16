#pragma once
#include "CmdButton.h"
class CEngnrByCmdButton : public CCmdButton
{
public:
	CEngnrByCmdButton() = default;
	virtual ~CEngnrByCmdButton() = default;

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
