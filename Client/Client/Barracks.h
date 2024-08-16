#pragma once
#include "Building.h"

enum class EBarracksState
{
	CONSTRUCTION,
	LAND,
	LANDING,
	LIFT_OFF,
	LIFTING_OFF,
	MOVE,
	BUILD,
	DIE,
	ENUM_END
};

class CUnitProperty;

class CBarracks : public CBuilding
{
public:
	CBarracks(CBuildingProperty& _buildingProperty);
	virtual ~CBarracks() = default;

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
	void SetBarracksState(EBarracksState _eBarracksState) { m_eBarracksState = _eBarracksState; }
	EBarracksState GetBarracksState() const { return m_eBarracksState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void BuildUnit();

private:
	// 배럭의 상태
	EBarracksState m_eBarracksState = EBarracksState::ENUM_END;

private:
	CUnitProperty* m_pMarineProperty = nullptr;
	CUnitProperty* m_pFirebatProperty = nullptr;
	CUnitProperty* m_pMedicProperty = nullptr;
	CUnitProperty* m_pGhostProperty = nullptr;
};
