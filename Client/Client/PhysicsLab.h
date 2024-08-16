#pragma once
#include "Building.h"

enum class EPhysicsLabState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CPhysicsLab : public CBuilding
{
public:
	CPhysicsLab(CBuildingProperty& _buildingProperty);
	virtual ~CPhysicsLab() = default;

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
	void SetPhysicsLabState(EPhysicsLabState _ePhysicsLabState) { m_ePhysicsLabState = _ePhysicsLabState; }
	EPhysicsLabState GetPhysicsLabState() const { return m_ePhysicsLabState; }

private:
	EPhysicsLabState m_ePhysicsLabState = EPhysicsLabState::ENUM_END;

private:
	CUpgradeProperty* m_pYamatoCannonProperty = nullptr;
	// CUpgradeProperty* m_pSiegeTechProperty = nullptr;
};

