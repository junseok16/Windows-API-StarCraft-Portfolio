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
	// 투사체의 상태
	EProjectileState m_eProjectileState = EProjectileState::TRACE;

	// 현재 속도
	float m_fCurSpeed = 0.0f;

	// 방향
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// 목표로 설정된 적군
	CTerranObject* m_pTarget = nullptr;

	// 투사체 정지 애니메이션 모음
	CAnimation* m_pBulletStopAnim = nullptr;

	// 투사체 이동 애니메이션 모음
	CAnimation* m_pBulletMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

public:
	float GetCurSpeed() const { return m_fCurSpeed; }

	void SetCurSpeed(float _fSpeed) { m_fCurSpeed = _fSpeed; }

	CTerranObject* GetTarget() const { return m_pTarget; }

	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }

	void SetDirectionState(EDirectionState _eDirectionState) { m_eDirectionState = _eDirectionState; }
};

