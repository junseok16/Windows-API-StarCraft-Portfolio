#pragma once
#include "Projectile.h"
class CNuclearProjectile : public CProjectile
{
public:
	CNuclearProjectile() = default;
	virtual ~CNuclearProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	float m_fExplosionDeltaSeconds = 0.0f;
};

