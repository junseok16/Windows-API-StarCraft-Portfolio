#pragma once
#include "ColliderComponent.h"

class CRectangleColliderComponent : public CColliderComponent
{
public:
	CRectangleColliderComponent();
	virtual ~CRectangleColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

	virtual bool IsCollided(CColliderComponent* _pColliderComponent) override;

public:
	RECT GetRect();

	Vector2Int GetColliderSize() const { return m_tColliderSize; }
	void SetColliderSize(Vector2Int _tColliderSize) { m_tColliderSize = _tColliderSize; }

private:
	Vector2Int m_tColliderSize{ 0, 0 };
};

