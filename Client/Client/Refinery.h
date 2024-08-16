#pragma once
#include "Building.h"

enum class ERefineryState
{
	CONSTRUCTION,
	IDLE,
	DIE,
	ENUM_END
};

class CRefinery : public CBuilding
{
public:
	CRefinery(CBuildingProperty& _buildingProperty);
	virtual ~CRefinery() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;
	virtual void OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;
	virtual void OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;

public:
	void SetRefineryState(ERefineryState _eRefineryState) { m_eRefineryState = _eRefineryState; }
	ERefineryState GetRefineryState() const { return m_eRefineryState; }

private:
	void ExecuteCommand();

private:
	// 리파이너리의 상태
	ERefineryState m_eRefineryState = ERefineryState::ENUM_END;
};

