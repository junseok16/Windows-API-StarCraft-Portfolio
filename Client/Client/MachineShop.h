#pragma once
#include "Building.h"

enum class EMachineShopState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CMachineShop : public CBuilding
{
public:
	CMachineShop(CBuildingProperty& _buildingProperty);
	virtual ~CMachineShop() = default;

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
	void SetMachineShopState(EMachineShopState _eMachineShopState) { m_eMachineShopState = _eMachineShopState; }
	EMachineShopState GetMachineShopState() const { return m_eMachineShopState; }

private:
	EMachineShopState m_eMachineShopState = EMachineShopState::ENUM_END;

private:
	CUpgradeProperty* m_pIonThrustersProperty = nullptr;
	CUpgradeProperty* m_pSiegeTechProperty = nullptr;
};
