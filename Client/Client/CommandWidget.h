#pragma once
#include "Widget.h"

class CCmdButton;
class CSprite;

class CCommandWidget : public CWidget
{
public:
	CCommandWidget() = default;
	virtual ~CCommandWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	// 모든 버튼들
	CCmdButton* m_pCmdButtons[(int32)ECommandType::ENUM_END]{ nullptr };
};

