#pragma once
#include "Widget.h"

class CSpriteUI;
class CTextUI;
class CSprite;

class CResourceWidget : public CWidget
{
public:
	CResourceWidget() = default;
	virtual ~CResourceWidget() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetMineralSprite(CSprite* _pMineralSprite);
	void SetMineralText(std::wstring _strMineral);

	void SetGasSprite(CSprite* _pGasSprite);
	void SetGasText(std::wstring _strGas);

	void SetSupplySprite(CSprite* _pSupplySprite);
	void SetSupplyText(std::wstring _strSupply);

private:
	CSpriteUI* m_pMineralSpriteUI = nullptr;
	CTextUI* m_pMineralTextUI = nullptr;

	CSpriteUI* m_pGasSpriteUI = nullptr;
	CTextUI* m_pGasTextUI = nullptr;

	CSpriteUI* m_pSupplySpriteUI = nullptr;
	CTextUI* m_pSupplyTextUI = nullptr;
};

