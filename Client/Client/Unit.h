#pragma once
#include "TerranObject.h"

class CUnitProperty;
class CAnimation;
class CSprite;

class CUnit : public CTerranObject {
public:
	CUnit(CUnitProperty& _unitProperty);
	virtual ~CUnit() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);
	virtual void OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);
	virtual void OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);

public:
	virtual bool GetAttacked(int32 _iAttackDamage);
	virtual bool GetHealed(int32 _iHeal);
	virtual void UpdateDirection();
	void RecoverMP();

private:
	void UpdateWireframe();
	void UpdateDynamicTilemap();
	void UpdateHitedSprite();
	void UpdateHitingSprite();
	void RenderHitedSprite(HDC _hDC);
	void RenderHitingSprite(HDC _hDC);

/******************************
	데이터시트에 있는 속성들
******************************/
protected:
	// 유닛 속성 데이터시트
	CUnitProperty& m_unitProperty;

	// 현재 체력
	int32 m_iCurHP = 0;

	// 현재 마력
	int32 m_iCurMP = 0;

	// 마력 회복 주기
	float m_fSumRecoverMPDS = 0.0f;

	// 현재 실드
	int32 m_iCurShield = 0;

	// 현재 속도
	float m_fCurSpeed = 0.0f;

public:
	CUnitProperty& GetUnitProperty() const { return m_unitProperty; }
	// void SetUnitProperty(CUnitProperty& _unitProperty) { m_unitProperty = _unitProperty; }

	int32 GetCurHP() const { return m_iCurHP; }
	void SetCurHP(int32 _iCurHP) { m_iCurHP = _iCurHP; }

	int32 GetCurMP() const { return m_iCurMP; }
	void SetCurMP(int32 _iCurMP) { m_iCurMP = _iCurMP; }

	int32 GetCurShield() const { return m_iCurShield; }
	void SetCurShield(int32 _iCurShield) { m_iCurShield = _iCurShield; }

	void SetCurSpeed(float _fSpeed) { m_fCurSpeed = _fSpeed; }
	float GetCurSpeed() const { return m_fCurSpeed; }

	void IncreaseHP(uint32 _iHP);
	void DecreaseHP(uint32 _iHP);

	void IncreaseMP(uint32 _iMP);
	void DecreaseMP(uint32 _iMP);

	void IncreaseShield(uint32 _iShield);
	void DecreaseShield(uint32 _iShield);

/******************************
	데이터시트에 없는 속성들
******************************/
protected:
	// 방향
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// 각도
	float m_fDegree = 0.0f;

	// 출발지 타일 위치
	Vector2Int m_tSrcTile{ 0, 0 };

	// 도착지 타일 위치
	Vector2Int m_tDstTile{ 0, 0 };

	// 출발지 위치
	Vector2 m_tSrcPosition{ 0.0f, 0.0f };

	// 도착지 위치
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	
	// 현재 공격 주기
	float m_fCurAttackDeltaSeconds = 0.0f;

	// 현재 사거리
	int32 m_iCurRange = 0;

public:
	void SetCurAttackDeltaSeconds(float _fCurAttackDeltaSeconds) { m_fCurAttackDeltaSeconds = _fCurAttackDeltaSeconds; }
	float SetCurAttackDeltaSeconds() const { return m_fCurAttackDeltaSeconds; }

	void SetCurRange(int32 _iCurRange) { m_iCurRange = _iCurRange; }
	int32 GetCurRange() { return m_iCurRange; }

/******************************
	유닛이 갖고 있는 명령들
******************************/
protected:
	// 유닛 타입
	ETerranUnitType m_eTerranUnitType = ETerranUnitType::ENUM_END;

	EUnitAttributeType	m_eUnitAtributeType = EUnitAttributeType::ENUM_END;

	// 목표로 설정된 적군
	CTerranObject* m_pTarget = nullptr;

	// 공격 주기 카운터
	float m_fSumAttackDeltaSeconds = 0.0f;

	// 공격 이동 전환 카운터
	float m_fSumAttackMoveDeltaSeconds = 0.0f;

public:
	ETerranUnitType GetTerranUnitType() const { return m_eTerranUnitType; }
	void SetTerranUnitType(ETerranUnitType _eTerranUnitType) { m_eTerranUnitType = _eTerranUnitType; }

	EUnitAttributeType GetUnitAttributeType() const { return m_eUnitAtributeType; }
	void SetUnitAtributeType(EUnitAttributeType _eUnitAtributeType) { m_eUnitAtributeType = _eUnitAtributeType; }

	CTerranObject* GetTarget() const { return m_pTarget; }
	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }


/******************************
	유닛의 스프라이트
******************************/
protected:
	// 유닛 정지 애니메이션 모음
	CAnimation* m_pUnitStopAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 유닛 이동 애니메이션 모음
	CAnimation* m_pUnitMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 유닛 공격 애니메이션 모음
	CAnimation* m_pUnitAttckAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 유닛 사망 애니메이션
	CAnimation* m_pUnitDieAnim = nullptr;

	// 큰 와이어프레임 모음
	CSprite* m_pUnitBigWireframes[6]{ nullptr };

	// 작은 와이어프레임 모음
	CSprite* m_pUnitSmallWireframes[6]{ nullptr };

	// 유닛 초상화
	CAnimation* m_pUnitPortrait = nullptr;

	// 현재 체력의 큰 와이어프레임
	CSprite* m_pUnitCurBigWireframe = nullptr;

	// 현재 체력의 작은 와이어프레임
	CSprite* m_pUnitCurSmallWireframe = nullptr;

	// 현재 체력 색
	int32 m_iCurHPColor = RGB(0, 255, 0);

public:
	CAnimation* GetPortraitAnim() { return m_pUnitPortrait; }
	void SetPortraitAnim(CAnimation* _pUnitPortrait) { m_pUnitPortrait = _pUnitPortrait; }

	CSprite* GetCurBigWireframeSprite() { return m_pUnitCurBigWireframe; }
	void SetCurBigWireframeSprite(CSprite* _pUnitCurBigWireframe) { m_pUnitCurBigWireframe = _pUnitCurBigWireframe; }

	CSprite* GetCurSmallWireframeSprite() { return m_pUnitCurSmallWireframe; }
	void SetCurSmallWireframeSprite(CSprite* _pUnitCurSmallWireframe) { m_pUnitCurSmallWireframe = _pUnitCurSmallWireframe; }

	int32 GetCurHPColor() { return m_iCurHPColor; }
	void SetCurHPColor(int32 _iCurHPColor) { m_iCurHPColor = _iCurHPColor; }

/****************************
	공격, 피격 애니메이션
****************************/
protected:
	// 컴퓨터 유닛 피격 애니메이션(Hit)
	CAnimation* m_pUnitHitedAnim = nullptr;

	// 플레이어 유닛 공격 애니메이션
	CAnimation* m_pUnitHitingAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// 현재 컴퓨터 유닛 피격 애니메이션
	CAnimation* m_pCurUnitHitedAnim = nullptr;

	// 현재 플레이어 유닛 공격 애니메이션
	CAnimation* m_pCurUnitHitingAnim = nullptr;

	// 피격 애니메이션 위치
	Vector2 m_tHitedPosition{ 0.0f, 0.0f };

	// 공격 애니메이션 위치
	Vector2 m_tHitingPosition{ 0.0f, 0.0f };

	float m_fHitedSumDeltaSeconds = 0.0f;

	int32 m_iHitedOffset = 0;

	float m_fHitingSumDeltaSeconds = 0.0f;

	int32 m_iHitingOffset = 0;

	bool m_bPlayHitingAnim = false;

	bool m_bPlayHitedAnim = false;

public:
	void SetCurHitedAnim(CAnimation* _pCurUnitHitedAnim);
	CAnimation* GetCurHitedAnim() { return m_pCurUnitHitedAnim; }

	void SetCurHitingAnim(CAnimation* _pCurUnitHitingAnim);
	CAnimation* GetCurHitingAnim() { return m_pCurUnitHitingAnim; }

	void SetHitedPosition(Vector2 _tHitedPosition) { m_tHitedPosition = _tHitedPosition; }
	Vector2 GetHitedPosition() const { return m_tHitedPosition; }

	void SetHitingPosition(Vector2 _tHitingPosition) { m_tHitingPosition = _tHitingPosition; }
	Vector2 GetHitngPosition() const { return m_tHitingPosition; }
};

