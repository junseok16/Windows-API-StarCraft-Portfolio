#pragma once
#include "Unit.h"

enum class EVultureState
{
	STOP,
	MOVE,
	ATTACK,
	ALERT,
	DIE,
	ENUM_END,
};

class CUnitProperty;

class CVulture : public CUnit
{
public:
	CVulture(CUnitProperty& _unitProperty);
	virtual ~CVulture() = default;

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
	void SetVultureState(EVultureState _eVultureState) { m_eVultureState = _eVultureState; }
	EVultureState GetVultureState() const { return m_eVultureState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void AlertAround();

private:
	EVultureState m_eVultureState = EVultureState::ENUM_END;
};

