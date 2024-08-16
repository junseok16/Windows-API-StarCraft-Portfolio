#pragma once
#include "Building.h"

enum class ECovertOpsState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CCovertOps : public CBuilding
{
public:
	CCovertOps(CBuildingProperty& _buildingProperty);
	virtual ~CCovertOps() = default;

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
	void SetCovertOpsState(ECovertOpsState _eCovertOpsState) { m_eCovertOpsState = _eCovertOpsState; }
	ECovertOpsState GetCovertOpsState() const { return m_eCovertOpsState; }

private:
	ECovertOpsState m_eCovertOpsState = ECovertOpsState::ENUM_END;

private:
	// CUpgradeProperty* m_pIonThrustersProperty = nullptr;
	// CUpgradeProperty* m_pSiegeTechProperty = nullptr;
};

