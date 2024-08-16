#pragma once
#include "SliderUI.h"

class CTerranObject;

class CMPBarUI : public CSliderUI
{
public:
	CMPBarUI() = default;
	virtual ~CMPBarUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetBarOwner(CTerranObject* _pMPBarOwner) { m_pMPBarOwner = _pMPBarOwner; }
	CTerranObject* GetBarOwner() const { return m_pMPBarOwner; }

	void SetDistance(float _fDistance) { m_fDistance = _fDistance; }

private:
	void UpdateUIPosition();
	void UpdateFillAmount();

private:
	// 마력바를 소유한 주인
	CTerranObject* m_pMPBarOwner = nullptr;

	// 중심으로부터의 거리
	float m_fDistance = 0.0f;
};

