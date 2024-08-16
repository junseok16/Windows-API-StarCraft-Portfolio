#pragma once
#include "Building.h"

enum class EFactoryState
{
	CONSTRUCTION,
	ADD_ON_CONSTRUCTION,
	LAND,
	LANDING,
	LIFT_OFF,
	LIFTING_OFF,
	BUILD,
	DIE,
	ENUM_END
};

class CUnitProperty;
class CBuildingProperty;

class CFactory : public CBuilding
{
public:
	CFactory(CBuildingProperty& _buildingProperty);
	virtual ~CFactory() = default;

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
	void SetFactoryState(EFactoryState _eFactoryState) { m_eFactoryState = _eFactoryState; }
	EFactoryState GetFactoryState() const { return m_eFactoryState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void BuildUnit();
	// void UpdateAnim();

private:
	// 팩토리의 상태
	EFactoryState m_eFactoryState = EFactoryState::ENUM_END;

private:
	CUnitProperty* m_pVultureProperty = nullptr;
	CUnitProperty* m_pTankProperty = nullptr;
	CUnitProperty* m_pSiegeTankProperty = nullptr;
	CUnitProperty* m_pGoliathProperty = nullptr;
	CBuildingProperty* m_pMachineShopProperty = nullptr;
};

