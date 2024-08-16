#pragma once
#include "Unit.h"

enum class EBattlecruiserState
{
	STOP,
	MOVE,
	ALERT,
	ATTACK,
	YAMATO_CANNON,
	DIE,
	ENUM_END,
};

class CRectangleColliderComponent;

class CBattlecruiser : public CUnit
{
public:
	CBattlecruiser(CUnitProperty& _unitProperty);
	virtual ~CBattlecruiser() = default;

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
	void SetBattlecruiserState(EBattlecruiserState _eBattlecruiserState) { m_eBattlecruiserState = _eBattlecruiserState; }
	EBattlecruiserState GetBattlecruiserState() const { return m_eBattlecruiserState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void AlertAround();

private:
	EBattlecruiserState m_eBattlecruiserState = EBattlecruiserState::ENUM_END;

	CRectangleColliderComponent* pRectCollider = nullptr;

	float m_bUseYmtCnn = false;

	float m_fYmtDeltaSeconds = 0.0f;
};

