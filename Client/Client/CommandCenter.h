#pragma once
#include "Building.h"

enum class ECommandCenterState
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

class CCommandCenter : public CBuilding
{
public:
	CCommandCenter(CBuildingProperty& _buildingProperty);
	virtual ~CCommandCenter() = default;

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
	void SetCommandCenterState(ECommandCenterState _eCommandCenterState) { m_eCommandCenterState = _eCommandCenterState; }
	ECommandCenterState GetCommandCenterState() const { return m_eCommandCenterState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void BuildUnit();

private:
	ECommandCenterState m_eCommandCenterState = ECommandCenterState::ENUM_END;

private:
	CUnitProperty* m_pSCVProperty = nullptr;
	CBuildingProperty* m_pNuclearSiloProperty = nullptr;
};

