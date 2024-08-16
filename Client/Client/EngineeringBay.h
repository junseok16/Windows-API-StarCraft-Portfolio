#pragma once
#include "Building.h"

enum class EEngineeringBayState
{
	CONSTRUCTION,
	LAND,
	LANDING,
	MOVE,
	LIFT,
	LIFTING,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CEngineeringBay : public CBuilding {
public:
	CEngineeringBay(CBuildingProperty& _buildingProperty);
	virtual ~CEngineeringBay() = default;

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
	void SetEngineeringBayState(EEngineeringBayState _eEngineeringBayState) { m_eEngineeringBayState = _eEngineeringBayState; }
	EEngineeringBayState GetEngineeringBayState() const { return m_eEngineeringBayState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void Upgrade();

	void UpgradeInfantyWeapon();
	void UpgradeInfantyArmor();

private:
	// 엔지니어링 베이의 상태
	EEngineeringBayState m_eEngineeringBayState = EEngineeringBayState::ENUM_END;

	CUpgradeProperty* m_pInfWeaponProperty[3]{ nullptr };

	CUpgradeProperty* m_pInfArmorProperty[3]{ nullptr };
};

