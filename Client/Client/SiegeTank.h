#pragma once
#include "Unit.h"

enum class ESiegeTankState
{
    STOP,
    MOVE,
    ATTACK,
	TO_SIEGE_MODE,
	TO_TANK_MODE,
	ALERT,
    DIE,
    ENUM_END
};

enum class ESiegeTankMode
{
	TANK_MODE,
	SIEGE_MODE,
};

class CAnimation;
class CUnitProperty;

class CSiegeTank : public CUnit
{
public:
	CSiegeTank(CUnitProperty& _tnkProperty, CUnitProperty& _sgTnkProperty);
	virtual ~CSiegeTank() = default;

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
	void SetSiegeTankState(ESiegeTankState _eSiegeTankState) { m_eSiegeTankState = _eSiegeTankState; }
	ESiegeTankState GetSiegeTankState() const { return m_eSiegeTankState; }

	void SetSiegeTankMode(ESiegeTankMode _eSiegeTankMode) { m_eSiegeTankMode = _eSiegeTankMode; }
	ESiegeTankMode GetSiegeTankMode() const { return m_eSiegeTankMode; }


	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	
	void UpdateBarrelAnim();
	void UpdateBarrelPosition();
	void RenderBarrel(HDC _hDC);

	void SetHdAnimation(CAnimation* _pAnimation);
	void AlertAround(CUnitProperty& _unitProperty);

private:
	ESiegeTankState m_eSiegeTankState = ESiegeTankState::ENUM_END;

	ESiegeTankMode m_eSiegeTankMode = ESiegeTankMode::TANK_MODE;

	bool m_bPlayBdySgMd = false;

	bool m_bPlayHdSgMd = false;

	float m_fBdySgMdDeltaSeconds = 0.0f;

	float m_fHdSgMdDeltaSeconds = 0.0f;

	CUnitProperty& m_pSiegeTankProperty;

	CAnimation* m_pTnkHdAnim = nullptr;

private:
	Vector2 m_tHdPosition{ 0.0f, 0.0f };

	Vector2 m_tHdNormalVector{ 0.0f, 0.0f };

	EDirectionState m_eTnkHdDirectionState = EDirectionState::SOUTH;

	float m_iHdDegree = 0.0f;

	float m_fHdSumDeltaSeconds = 0.0f;

	int32 m_iHdOffset = 0;

private:
	// 탱크 몸체 모드 변환하는 애니메이션
	CAnimation* m_pBdySiegeModingAnim = nullptr;
	CAnimation* m_pBdyTankModingAnim = nullptr;

	// 탱크 포신 모드 변환하는 애니메이션
	CAnimation* m_pHdSiegeModingAnim = nullptr;
	CAnimation* m_pHdTankModingAnim = nullptr;

	/*************************************************************************/

	// 탱크 몸체 정지 애니메이션 모음
	CAnimation* m_pTnkBdyStopAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 탱크 몸체 이동 애니메이션 모음
	CAnimation* m_pTnkBdyMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 탱크 몸체 사망 애니메이션
	CAnimation* m_pTankBdyDieAnim = nullptr;

	// 탱크 포신 정지, 회전 애니메이션 모음
	CAnimation* m_pTnkHdStpRotAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 탱크 포신 사망 애니메이션
	CAnimation* m_pTnkHdDieAnim = nullptr;

	/*************************************************************************/

	// 시즈 탱크 몸체 정지 애니메이션 모음
	CAnimation* m_pSgTnkBdyStpAnim[(int32)EDirectionState::ENUM_END]{ nullptr };
	
	// 시즈 탱크 포신 정지, 회전 애니메이션 모음
	CAnimation* m_pSgTnkHdStpRotAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	/*************************************************************************/

	// 탱크 포신 공격 애니메이션 모음
	CAnimation* m_pTnkHdHtngAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 탱크 포신 피격 애니메이션
	CAnimation* m_pTnkHdHtedAnim = nullptr;

	// 시즈 탱크 공격 애니메이션 모음
	CAnimation* m_pSgTnkHdHtngAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 시즈 탱크 피격 애니메이션
	CAnimation* m_pSgTnkHdHtedAnim = nullptr;
};

