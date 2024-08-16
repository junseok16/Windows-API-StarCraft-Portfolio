#pragma once
#include "Building.h"

enum class EStarportState
{
	CONSTRUCTION,
	LAND,
	LANDING,
	LIFT_OFF,
	LIFTING_OFF,
	BUILD,
	ADD_ON_CONSTRUCTION,
	DIE,
	ENUM_END
};

class CUnitProperty;
class CBuildingProperty;

class CStarport : public CBuilding
{
public:
	CStarport(CBuildingProperty& _buildingProperty);
	virtual ~CStarport() = default;

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
	void SetStarportState(EStarportState _eStarportState) { m_eStarportState = _eStarportState; }
	EStarportState GetStarportState() const { return m_eStarportState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void BuildUnit();
	// void UpdateAnim();

private:
	// CUnitProperty* m_pWraithProperty = nullptr;

private:
	// 스타포트의 상태
	EStarportState m_eStarportState = EStarportState::ENUM_END;

private:
	// CUnitProperty* m_pWraithProperty = nullptr;
	// CUnitProperty* m_pDropshipProperty = nullptr;
	// CUnitProperty* m_pValkyrieProperty = nullptr;
	CUnitProperty* m_pScienceVesselProperty = nullptr;
	CUnitProperty* m_pBattlecruiserProperty = nullptr;

	CBuildingProperty* m_pContolTowerProperty = nullptr;
};

