#pragma once
#include "Building.h"

enum class EControlTowerState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CControlTower : public CBuilding
{
public:
	CControlTower(CBuildingProperty& _buildingProperty);
	virtual ~CControlTower() = default;

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

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void Upgrade();

public:
	void SetControlTowerState(EControlTowerState _eControlTowerState) { m_eControlTowerState = _eControlTowerState; }
	EControlTowerState GetControlTowerState() const { return m_eControlTowerState; }

private:
	EControlTowerState m_eControlTowerState = EControlTowerState::ENUM_END;

private:
	// CUpgradeProperty* m_pIonThrustersProperty = nullptr;
	// CUpgradeProperty* m_pSiegeTechProperty = nullptr;
};

