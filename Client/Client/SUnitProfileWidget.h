#pragma once
#include "Widget.h"

class CSpriteUI;
class CTextUI;
class CAnimationUI;
class CButtonUI;

class CSprite;
class CAnimation;
class CBuilding;

class CSUnitProfileWidget : public CWidget
{
public:
	CSUnitProfileWidget() = default;
	virtual ~CSUnitProfileWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetBigWireSprite(CSprite* _pBigWireSprite);
	void SetHPText(std::wstring _strHP);
	void SetHPTextColor(int32 _iColor);
	void SetMPText(std::wstring _strMP);
	void SetMPTextColor(int32 _iColor);
	void SetNameText(std::wstring _strName);
	void SetRankText(std::wstring _strRank);
	void SetBuildingText(std::wstring _strRank);
	void SetPortraitAnim(CAnimation* _pPortraitAnim);

private:
	void VerifyBuildingUnit(CBuilding* _pBuilding);
	void VerifyUpgrade(CBuilding* _pBuilding);

private:
	CSpriteUI* m_pBigWireUI = nullptr;
	CTextUI* m_pHPUI = nullptr;
	CTextUI* m_pMPUI = nullptr;

	CTextUI* m_pNameUI = nullptr;
	CTextUI* m_pRankUI = nullptr;
	CAnimationUI* m_pPortraitUI = nullptr;

	CSpriteUI* m_pEmptyProgressBarUI = nullptr;
	CSpriteUI* m_pFullProgressBarUI = nullptr;

	CTextUI* m_pBuildingTextUI = nullptr;
	CSpriteUI* m_pBuildingQueueUI = nullptr;
	
	CSpriteUI* m_pBuildingUnit[5]{ nullptr };

	CSpriteUI* m_pFirstUI = nullptr;
	CSpriteUI* m_pSecondUI = nullptr;
	CSpriteUI* m_pThirdUI = nullptr;
	CSpriteUI* m_pFourthUI = nullptr;
	CSpriteUI* m_pFifthUI = nullptr;

	CSpriteUI* m_pUpgradeQueueUI = nullptr;
	CSpriteUI* m_pUpgradeUI = nullptr;
};

