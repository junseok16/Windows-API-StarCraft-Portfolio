#pragma once
#include "Building.h"

enum class EArmoryState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CArmory : public CBuilding
{
public:
	CArmory(CBuildingProperty& _buildingProperty);
	virtual ~CArmory() = default;

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
	void SetArmoryState(EArmoryState _eArmoryState) { m_eArmoryState = _eArmoryState; }
	EArmoryState GetArmoryState() const { return m_eArmoryState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void Upgrade();

	void UpgradeVihicleWeapon();
	void UpgradeVihiclePlating();

private:
	// 아머리의 상태
	EArmoryState m_eArmoryState = EArmoryState::ENUM_END;

	CUpgradeProperty* m_pVhclWeaponProperty[3]{ nullptr };

	CUpgradeProperty* m_pVhclPlatingProperty[3]{ nullptr };
};

