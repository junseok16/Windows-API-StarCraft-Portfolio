#pragma once
#include "UI.h"

class CTextUI : public CUI
{
public:
	CTextUI() = default;
	virtual ~CTextUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetFontColor(int32 _iFontColor) { m_iFontColor = _iFontColor; }
	int32 GetFontColor() const { return m_iFontColor; }

	void SetFontWeight(int32 _iFontWeight) { m_iFontWeight = _iFontWeight; }
	int32 GetFontWeight() const { return m_iFontWeight; }
	
	void SetFontHeight(int32 _iFontHeight) { m_iFontHeight = _iFontHeight; }
	int32 GetFontHeight() const { return m_iFontHeight; }

	void SetText(std::wstring _strText) { m_strText = _strText; }
	std::wstring GetText() const { return m_strText; }

protected:
	int32 m_iFontColor = RGB(0, 0, 0);
	int32 m_iFontWeight = 0;
	int32 m_iFontHeight = 0;
	std::wstring m_strText = L"Sample";
};

