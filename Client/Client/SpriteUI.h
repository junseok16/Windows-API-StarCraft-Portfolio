#pragma once
#include "UI.h"

class CSprite;

class CSpriteUI : public CUI
{
public:
	CSpriteUI() = default;
	virtual ~CSpriteUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	CSprite* GetSprite() const { return m_pSprite; }
	void SetSprite(CSprite* _pSprite) { m_pSprite = _pSprite; }

protected:
	CSprite* m_pSprite = nullptr;
};

