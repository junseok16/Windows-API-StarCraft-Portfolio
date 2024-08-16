#pragma once
#include "CmdButton.h"

class CUpgradeProperty;

class CUpIonThrstrCmdButton : public CCmdButton
{
public:
	CUpIonThrstrCmdButton() = default;
	virtual ~CUpIonThrstrCmdButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

private:
	CUpgradeProperty* pIonThrstrProperty = nullptr;
};

