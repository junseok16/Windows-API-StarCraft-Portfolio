#pragma once
#include "Building.h"

enum class ENuclearSiloState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CNuclearSilo : public CBuilding
{
public:
	CNuclearSilo(CBuildingProperty& _buildingProperty);
	virtual ~CNuclearSilo() = default;

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
	void SetNuclearSiloState(ENuclearSiloState _eNuclearSiloState) { m_eNuclearSiloState = _eNuclearSiloState; }
	ENuclearSiloState GetNuclearSiloState() const { return m_eNuclearSiloState; }

private:
	ENuclearSiloState m_eNuclearSiloState = ENuclearSiloState::ENUM_END;

private:
	CUpgradeProperty* m_pArmNclrSloProperty = nullptr;
};

