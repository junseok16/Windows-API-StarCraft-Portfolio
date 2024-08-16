#pragma once
#include "Projectile.h"

class CUnitProperty;

class CGhstProjectile : public CProjectile
{
public:
	CGhstProjectile() = default;
	virtual ~CGhstProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	CUnitProperty* m_pProperty = nullptr;
};

