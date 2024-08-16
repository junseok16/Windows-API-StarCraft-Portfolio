#pragma once
#include "ColliderComponent.h"

class CCircleColliderComponent : public CColliderComponent
{
public:
	CCircleColliderComponent();
	virtual ~CCircleColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

	virtual bool IsCollided(CColliderComponent* _pColliderComponent) override;

public:
	float GetRadius() const { return m_fRadius; }
	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

private:
	float m_fRadius = 0.0f;
};

