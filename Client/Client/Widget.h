#pragma once
#include "UI.h"

class CWidget : public CUI
{
public:
	CWidget() = default;
	virtual ~CWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetWidgetActive(bool _bWidgetActive);
	bool GetWidgetActive() const;

public:
	void InsertUI(CUI* _pUI);
	void EraseUI(CUI* _pUI);

protected:
	bool m_bWidgetActive = true;
	std::vector<CUI*> m_pUIs;
};

