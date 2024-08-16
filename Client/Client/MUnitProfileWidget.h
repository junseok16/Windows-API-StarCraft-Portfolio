#pragma once
#include "Widget.h"

class CSmallProfileButton;
class CSprite;
class CSpriteUI;
class CAnimation;
class CAnimationUI;

class CMUnitProfileWidget : public CWidget
{
public:
	CMUnitProfileWidget() = default;
	virtual ~CMUnitProfileWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetButtonSprite(int32 _iRow, int32 _iColumn, EButtonState _eButtonState, CSprite* _pButton00Sprite);
	void SetPortraitAnim(CAnimation* _pPortraitAnim);

private:
	CSmallProfileButton* m_pButton[2][6]{ nullptr };

	CSpriteUI* m_pBlueButtonBox[2][6]{ nullptr };

	CAnimationUI* m_pPortraitUI = nullptr;
};

