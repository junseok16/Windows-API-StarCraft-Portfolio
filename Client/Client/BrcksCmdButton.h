#pragma once
#include "CmdButton.h"

class CBrcksCmdButton : public CCmdButton
{
public:
	CBrcksCmdButton() = default;
	virtual ~CBrcksCmdButton() = default;

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

