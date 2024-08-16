#pragma once
#include "SliderUI.h"

class CTerranObject;

class CHPBarUI : public CSliderUI
{
public:
	CHPBarUI() = default;
	virtual ~CHPBarUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetBarOwner(CTerranObject* _pHPBarOwner) { m_pHPBarOwner = _pHPBarOwner; }
	CTerranObject* GetBarOwner() const { return m_pHPBarOwner; }

	void SetDistance(float _fDistance) { m_fDistance = _fDistance; }

private:
	void UpdateUIPosition();
	void UpdateFillAmount();

private:
	// 체력바를 소유한 주인
	CTerranObject* m_pHPBarOwner = nullptr;

	// 중심으로부터의 거리
	float m_fDistance = 0.0f;
};

