#pragma once
#include "TerranObject.h"

enum class EProjectileState
{
	TRACE,
	EXPLODE,
	DIE,
	ENUM_END
};

class CProjectile : public CTerranObject
{
public:
	CProjectile() = default;
	virtual ~CProjectile() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

protected:
	// ����ü�� ����
	EProjectileState m_eProjectileState = EProjectileState::TRACE;

	// ���� �ӵ�
	float m_fCurSpeed = 0.0f;

	// ����
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// ��ǥ�� ������ ����
	CTerranObject* m_pTarget = nullptr;

	// ����ü ���� �ִϸ��̼� ����
	CAnimation* m_pBulletStopAnim = nullptr;

	// ����ü �̵� �ִϸ��̼� ����
	CAnimation* m_pBulletMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

public:
	float GetCurSpeed() const { return m_fCurSpeed; }

	void SetCurSpeed(float _fSpeed) { m_fCurSpeed = _fSpeed; }

	CTerranObject* GetTarget() const { return m_pTarget; }

	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }

	void SetDirectionState(EDirectionState _eDirectionState) { m_eDirectionState = _eDirectionState; }
};

