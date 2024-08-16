#pragma once
#include "Building.h"

enum class EScienceFacilityState {
	CONSTRUCTION,
	LAND,
	LANDING,
	LIFT_OFF,
	LIFTING_OFF,
	UPGRADE,
	ADD_ON_CONSTRUCTION,
	DIE,
	ENUM_END
};

class CUpgradeProperty;
class CBuildingProperty;

class CScienceFacility : public CBuilding {
public:
	CScienceFacility(CBuildingProperty& _buildingProperty);
	virtual ~CScienceFacility() = default;

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
	void SetScienceFacilityState(EScienceFacilityState _eScienceFacilityState) { m_eScienceFacilityState = _eScienceFacilityState; }
	EScienceFacilityState GetScienceFacilityState() const { return m_eScienceFacilityState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void Upgrade();

private:
	// 사이언스 퍼실리티 상태
	EScienceFacilityState m_eScienceFacilityState = EScienceFacilityState::ENUM_END;

private:
	CUpgradeProperty* m_pIrradiateProperty = nullptr;

	CBuildingProperty* m_pCovertOpsProperty = nullptr;
	CBuildingProperty* m_pPhysicsLabProperty = nullptr;
};

