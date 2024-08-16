#pragma once
#include "Projectile.h"

class CUnitProperty;

class CTankProjectile : public CProjectile
{
public:
	CTankProjectile() = default;
	virtual ~CTankProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	CUnitProperty* m_pProperty = nullptr;
};

