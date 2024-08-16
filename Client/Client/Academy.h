#pragma once
#include "Building.h"

enum class EAcademyState
{
	CONSTRUCTION,
	IDLE,
	UPGRADE,
	DIE,
	ENUM_END
};

class CUpgradeProperty;

class CAcademy : public CBuilding
{
public:
	CAcademy(CBuildingProperty& _buildingProperty);
	virtual ~CAcademy() = default;

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
	void SetAcademyState(EAcademyState _eAcademyState) { m_eAcademyState = _eAcademyState; }
	EAcademyState GetAcademyState() const { return m_eAcademyState; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void Upgrade();

private:
	// 아카데미의 상태
	EAcademyState m_eAcademyState = EAcademyState::ENUM_END;

private:
	CUpgradeProperty* m_pU238ShellsProperty = nullptr;
	CUpgradeProperty* m_pStimpackTechProperty = nullptr;
};

