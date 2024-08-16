#pragma once
#include "Unit.h"

enum class EMarineState
{
	STOP,
	MOVE,
	ALERT,
	ATTACK,
	DIE,
	ENUM_END,
};

class CRectangleColliderComponent;

class CMarine : public CUnit
{
public:
	CMarine(CUnitProperty& _unitProperty);
	virtual ~CMarine() = default;

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
	void SetMarineState(EMarineState _eMarineState) { m_eMarineState = _eMarineState; }
	EMarineState GetMarineState() const { return m_eMarineState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void AlertAround();
	
	void UpdateCoolTime();

private:
	// ¸¶¸° »óÅÂ
	EMarineState m_eMarineState = EMarineState::ENUM_END;

	// ½ºÆÀÆÑ »ç¿ë ¿©ºÎ
	bool m_bStimpack = false;

	// ½ºÆÀÆÑ Ä«¿îÅÍ
	float m_fSumStimpackDeltaSeconds = 0.0f;

	CRectangleColliderComponent* pRectCollider = nullptr;
};

