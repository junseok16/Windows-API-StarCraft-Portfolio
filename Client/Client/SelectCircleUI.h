#pragma once
#include "SpriteUI.h"

class CTerranObject;

class CSelectCircleUI : public CSpriteUI
{
public:
	CSelectCircleUI() = default;
	virtual ~CSelectCircleUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetCircleOwner(CTerranObject* _pCircleOwner) { m_pCircleOwner = _pCircleOwner; }
	CTerranObject* GetCircleOwner() const { return m_pCircleOwner; }

private:
	void UpdateUIPosition();

private:
	// 선택 원을 소유한 주인
	CTerranObject* m_pCircleOwner = nullptr;
};

