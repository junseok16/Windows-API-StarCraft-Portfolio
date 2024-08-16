#pragma once
#include "Component.h"

class CScrollComponent : public CComponent
{
public:
	CScrollComponent() = default;
	virtual ~CScrollComponent() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

