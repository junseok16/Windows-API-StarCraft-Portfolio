#pragma once
#include "Unit.h"

enum class EGhostState
{
	STOP,
	MOVE,
	ATTACK,
	NUCLEAR_STRIKE,
	DIE,
	ENUM_END,
};

class CGhost : public CUnit
{
public:
	CGhost(CUnitProperty& _unitProperty);
	virtual ~CGhost() = default;

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
	void SetGhostState(EGhostState _eGhostState) { m_eGhostState = _eGhostState; }
	EGhostState GetGhostState() const { return m_eGhostState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void AlertAround();

private:
	// 고스트 상태
	EGhostState m_eGhostState = EGhostState::ENUM_END;

	bool m_bUseNclrStrk = false;

	bool m_bAlertNclrStrk = false;

	float m_fNclrStrkDeltaSeconds = 0.0f;

private:
	// 고스트 핵 공격 애니메이션 모음
	CAnimation* m_pNclrStrkAnim[(int32)EDirectionState::ENUM_END]{ nullptr };
};

