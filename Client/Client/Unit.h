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
	�����ͽ�Ʈ�� �ִ� �Ӽ���
******************************/
protected:
	// ���� �Ӽ� �����ͽ�Ʈ
	CUnitProperty& m_unitProperty;

	// ���� ü��
	int32 m_iCurHP = 0;

	// ���� ����
	int32 m_iCurMP = 0;

	// ���� ȸ�� �ֱ�
	float m_fSumRecoverMPDS = 0.0f;

	// ���� �ǵ�
	int32 m_iCurShield = 0;

	// ���� �ӵ�
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
	�����ͽ�Ʈ�� ���� �Ӽ���
******************************/
protected:
	// ����
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// ����
	float m_fDegree = 0.0f;

	// ����� Ÿ�� ��ġ
	Vector2Int m_tSrcTile{ 0, 0 };

	// ������ Ÿ�� ��ġ
	Vector2Int m_tDstTile{ 0, 0 };

	// ����� ��ġ
	Vector2 m_tSrcPosition{ 0.0f, 0.0f };

	// ������ ��ġ
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	
	// ���� ���� �ֱ�
	float m_fCurAttackDeltaSeconds = 0.0f;

	// ���� ��Ÿ�
	int32 m_iCurRange = 0;

public:
	void SetCurAttackDeltaSeconds(float _fCurAttackDeltaSeconds) { m_fCurAttackDeltaSeconds = _fCurAttackDeltaSeconds; }
	float SetCurAttackDeltaSeconds() const { return m_fCurAttackDeltaSeconds; }

	void SetCurRange(int32 _iCurRange) { m_iCurRange = _iCurRange; }
	int32 GetCurRange() { return m_iCurRange; }

/******************************
	������ ���� �ִ� ��ɵ�
******************************/
protected:
	// ���� Ÿ��
	ETerranUnitType m_eTerranUnitType = ETerranUnitType::ENUM_END;

	EUnitAttributeType	m_eUnitAtributeType = EUnitAttributeType::ENUM_END;

	// ��ǥ�� ������ ����
	CTerranObject* m_pTarget = nullptr;

	// ���� �ֱ� ī����
	float m_fSumAttackDeltaSeconds = 0.0f;

	// ���� �̵� ��ȯ ī����
	float m_fSumAttackMoveDeltaSeconds = 0.0f;

public:
	ETerranUnitType GetTerranUnitType() const { return m_eTerranUnitType; }
	void SetTerranUnitType(ETerranUnitType _eTerranUnitType) { m_eTerranUnitType = _eTerranUnitType; }

	EUnitAttributeType GetUnitAttributeType() const { return m_eUnitAtributeType; }
	void SetUnitAtributeType(EUnitAttributeType _eUnitAtributeType) { m_eUnitAtributeType = _eUnitAtributeType; }

	CTerranObject* GetTarget() const { return m_pTarget; }
	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }


/******************************
	������ ��������Ʈ
******************************/
protected:
	// ���� ���� �ִϸ��̼� ����
	CAnimation* m_pUnitStopAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� �̵� �ִϸ��̼� ����
	CAnimation* m_pUnitMoveAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� ���� �ִϸ��̼� ����
	CAnimation* m_pUnitAttckAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� ��� �ִϸ��̼�
	CAnimation* m_pUnitDieAnim = nullptr;

	// ū ���̾������� ����
	CSprite* m_pUnitBigWireframes[6]{ nullptr };

	// ���� ���̾������� ����
	CSprite* m_pUnitSmallWireframes[6]{ nullptr };

	// ���� �ʻ�ȭ
	CAnimation* m_pUnitPortrait = nullptr;

	// ���� ü���� ū ���̾�������
	CSprite* m_pUnitCurBigWireframe = nullptr;

	// ���� ü���� ���� ���̾�������
	CSprite* m_pUnitCurSmallWireframe = nullptr;

	// ���� ü�� ��
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
	����, �ǰ� �ִϸ��̼�
****************************/
protected:
	// ��ǻ�� ���� �ǰ� �ִϸ��̼�(Hit)
	CAnimation* m_pUnitHitedAnim = nullptr;

	// �÷��̾� ���� ���� �ִϸ��̼�
	CAnimation* m_pUnitHitingAnim[(int32)EDirectionState::ENUM_END]{ nullptr };

	// ���� ��ǻ�� ���� �ǰ� �ִϸ��̼�
	CAnimation* m_pCurUnitHitedAnim = nullptr;

	// ���� �÷��̾� ���� ���� �ִϸ��̼�
	CAnimation* m_pCurUnitHitingAnim = nullptr;

	// �ǰ� �ִϸ��̼� ��ġ
	Vector2 m_tHitedPosition{ 0.0f, 0.0f };

	// ���� �ִϸ��̼� ��ġ
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

