#pragma once
#include "Projectile.h"

class CUnitProperty;

class CSiegeTankProjectile : public CProjectile
{
public:
	CSiegeTankProjectile() = default;
	virtual ~CSiegeTankProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	CUnitProperty* m_pProperty = nullptr;
};

