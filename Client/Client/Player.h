#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer() = default;
	virtual ~CPlayer() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void UpdatePosition();
};

