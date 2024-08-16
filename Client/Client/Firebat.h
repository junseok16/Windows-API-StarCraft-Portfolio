#pragma once
#include "Unit.h"

enum class EFirebatState
{
	STOP,
	MOVE,
	ATTACK,
	ALERT,
	DIE,
	ENUM_END,
};

class CFirebat : public CUnit
{
public:
	CFirebat(CUnitProperty& _unitProperty);
	virtual ~CFirebat() = default;

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
	void SetFirebatState(EFirebatState _eFirebatState) { m_eFirebatState = _eFirebatState; }
	EFirebatState GetFirebatState() const { return m_eFirebatState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void AlertAround();

	void UpdateCoolTime();

private:
	// ÆÄÀÌ¾î¹î »óÅÂ
	EFirebatState m_eFirebatState = EFirebatState::ENUM_END;

	// ½ºÆÀÆÑ »ç¿ë ¿©ºÎ
	bool m_bStimpack = false;

	// ½ºÆÀÆÑ Ä«¿îÅÍ
	float m_fSumStimpackDeltaSeconds = 0.0f;
};

