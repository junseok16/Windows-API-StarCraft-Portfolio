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
	// ü�¹ٸ� ������ ����
	CTerranObject* m_pHPBarOwner = nullptr;

	// �߽����κ����� �Ÿ�
	float m_fDistance = 0.0f;
};

