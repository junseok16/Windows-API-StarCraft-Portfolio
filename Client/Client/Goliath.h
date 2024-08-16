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
	// ��ǥ�� ������ ����
	CObject* m_pTarget = nullptr;

	// ���� �ֱ� ī����
	float m_fCurAttackDeltaSeconds = 0.0f;

	// ���� �̵� ��ȯ ī����
	float m_fCurAttackMoveDeltaSeconds = 0.0f;

	// ���� ����
	EGoliathState m_eGoliathState = EGoliathState::ENUM_END;

	// ���� ���� �ִϸ��̼� ����
	CAnimation* m_pGoliathStopAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� �̵� �ִϸ��̼� ����
	CAnimation* m_pGoliathMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� ���� �ִϸ��̼� ����
	CAnimation* m_pGoliathAttckAnim[(int32)EDirectionState::ENUM_END]{ nullptr };
};

