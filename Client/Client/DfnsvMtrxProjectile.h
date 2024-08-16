#pragma once
#include "Projectile.h"

class CDfnsvMtrxProjectile : public CProjectile
{
public:
	CDfnsvMtrxProjectile() = default;
	virtual ~CDfnsvMtrxProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	float m_fActiveDeltaSeconds = 0.0f;
};

