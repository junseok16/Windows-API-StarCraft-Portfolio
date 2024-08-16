#pragma once
#include "Projectile.h"

class CIrradiateProjectile : public CProjectile
{
public:
	CIrradiateProjectile() = default;
	virtual ~CIrradiateProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	float m_fActiveDeltaSeconds = 0.0f;
	float m_fDamageDeltaSeconds = 0.0f;
};

