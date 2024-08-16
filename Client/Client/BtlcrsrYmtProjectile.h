#pragma once
#include "Projectile.h"

class CBtlcrsrYmtProjectile : public CProjectile
{
public:
	CBtlcrsrYmtProjectile() = default;
	virtual ~CBtlcrsrYmtProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

