#pragma once
#include "Unit.h"

enum class EGoliathState
{
	STOP,
	MOVE,
	ATTACK,
	DIE,
	ENUM_END,
};

class CAnimation;
class CUnitProperty;

class CGoliath : public CUnit
{
public:
	CGoliath(CUnitProperty& _unitProperty);
	virtual ~CGoliath() = default;

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
	void SetMarineState(EGoliathState _eGoliathState) { m_eGoliathState = _eGoliathState; }
	EGoliathState GetMarineState() const { return m_eGoliathState; }

	virtual void UpdateDirection() override;

private:
	void UpdateCommand();
	void UpdateState();

private:
	// 목표로 설정된 적군
	CObject* m_pTarget = nullptr;

	// 공격 주기 카운터
	float m_fCurAttackDeltaSeconds = 0.0f;

	// 공격 이동 전환 카운터
	float m_fCurAttackMoveDeltaSeconds = 0.0f;

	// 마린 상태
	EGoliathState m_eGoliathState = EGoliathState::ENUM_END;

	// 마린 정지 애니메이션 모음
	CAnimation* m_pGoliathStopAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 마린 이동 애니메이션 모음
	CAnimation* m_pGoliathMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 마린 공격 애니메이션 모음
	CAnimation* m_pGoliathAttckAnim[(int32)EDirectionState::ENUM_END]{ nullptr };
};

