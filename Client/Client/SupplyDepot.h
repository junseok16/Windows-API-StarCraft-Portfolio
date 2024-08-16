#pragma once
#include "Building.h"

enum class ESupplyDepotState
{
	CONSTRUCTION,
	IDLE,
	DIE,
	ENUM_END
};

class CSupplyDepot : public CBuilding
{
public:
	CSupplyDepot(CBuildingProperty& _buildingProperty);
	virtual ~CSupplyDepot() = default;

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
	void SetSupplyDepotState(ESupplyDepotState _eSupplyDepotState) { m_eSupplyDepotState = _eSupplyDepotState; }
	ESupplyDepotState GetSupplyDepotState() const { return m_eSupplyDepotState; }

private:
	void ExecuteCommand();

private:
	// 서플라이 디포의 상태
	ESupplyDepotState m_eSupplyDepotState = ESupplyDepotState::ENUM_END;
};

