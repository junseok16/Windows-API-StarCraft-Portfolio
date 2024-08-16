#pragma once
#include "TerranObject.h"

class CBuildingProperty;
class CAnimation;
class CSprite;

class CBuilding : public CTerranObject
{
public:
	CBuilding(CBuildingProperty& _buildingProperty);
	virtual ~CBuilding() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	void UpdateWireframe();

	//std::vector<ECommandType>& GetCommandTypes() { return m_eCommandTypes; }
	//void InsertCommand(ECommandType _eCommandType) { m_eCommandTypes.push_back(_eCommandType); }

/******************************
	�����ͽ�Ʈ�� �ִ� �Ӽ���
******************************/
protected:
	// �ǹ� �Ӽ� �����ͽ�Ʈ
	CBuildingProperty& m_buildingProperty;

	// ���� ü��
	int32 m_iCurHP = 0;

	// ���� ����
	int32 m_iCurMP = 0;

	// ���� �ǵ�
	int32 m_iCurShield = 0;

	// ���� �ӵ�
	float m_fSpeed = 0.0f;

public:
	CBuildingProperty& GetBuildingProperty() const { return m_buildingProperty; }

	int32 GetCurHP() const { return m_iCurHP; }
	void SetCurHP(int32 _iCurHP) { m_iCurHP = _iCurHP; }

	int32 GetCurMP() const { return m_iCurMP; }
	void SetCurMP(int32 _iCurMP) { m_iCurMP = _iCurMP; }

	int32 GetCurShield() const { return m_iCurShield; }
	void SetCurShield(int32 _iCurShield) { m_iCurShield = _iCurShield; }


/******************************
	�����ͽ�Ʈ�� ���� �Ӽ���
******************************/
protected:
	// ����
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// ����
	float m_iRadian = 0.0f;

	// ����� Ÿ�� ��ġ
	Vector2Int m_tSrcTilePosition{ 0, 0 };

	// ������ Ÿ�� ��ġ
	Vector2Int m_tDstTilePosition{ 0, 0 };

	// ����� ��ġ
	Vector2 m_tSrcPosition{ 0.0f, 0.0f };

	// ������ ��ġ
	Vector2 m_tDstPosition{ 0.0f, 0.0f };

	// ���� ���� Ÿ�� ��ġ
	Vector2Int m_tRallyTilePosition{ 0, 0 };
	
	// ���� ���� ��ġ
	Vector2 m_tRallyPosition{ 0.0f, 0.0f };

	// ���� ���� ����
	bool m_bRallyPoint = false;

public:
	void SetRallyTilePosition(Vector2Int _tRallyTilePosition) { m_tRallyTilePosition = _tRallyTilePosition; }
	Vector2Int GetRallyTilePosition() const { return m_tRallyTilePosition; }

/******************************
	�ǹ��� ���� �ִ� ��ɵ�
******************************/
protected:
	// �ǹ� Ÿ��
	ETerranBuildingType m_eTerranBuildingType = ETerranBuildingType::ENUM_END;

	// ��ǥ�� ������ ����
	CTerranObject* m_pTarget = nullptr;

	// ���� �ֱ� ī����
	float m_fCurAttackDeltaSeconds = 0.0f;

	// �Ǽ� �ð� ī����
	float m_pCurCnstrctnDeltaSeconds = 0.0f;

	// ���� �ð� ī����
	float m_fCurBuildDeltaSecond = 0.0f;

	// ���׷��̵� �ð� ī����
	float m_fCurUpgradeDeltaSecond = 0.0f;

	// ���� ť
	std::deque<ETerranUnitType> m_queBuildingUnits;

	// ���׷��̵�/����ġ ť
	std::deque<ETerranUpgradeType> m_queUpgrades;

public:
	ETerranBuildingType GetTerranBuildingType() const { return m_eTerranBuildingType; }
	void SetTerranBuildingType(ETerranBuildingType _eTerranBuildingType) { m_eTerranBuildingType = _eTerranBuildingType; }

	CTerranObject* GetTarget() const { return m_pTarget; }
	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }

	std::deque<ETerranUnitType>& GetBuildingUnitsQueue() { return m_queBuildingUnits; }

	std::deque<ETerranUpgradeType>& GetUpgradesQueue() { return m_queUpgrades; }

/******************************
	�ǹ��� ��������Ʈ
******************************/
protected:
	// �Ǽ� �ִϸ��̼�
	CAnimation* m_pCnstrctnAnim = nullptr;

	// ���� ���� �ִϸ��̼�
	CAnimation* m_pLandAnim = nullptr;

	// ���� ���� �ִϸ��̼�
	CAnimation* m_pLiftAnim = nullptr;

	// �̷� �ִϸ��̼�
	CAnimation* m_pLiftingAnim = nullptr;

	// ���� �ִϸ��̼�
	CAnimation* m_pLandingAnim = nullptr;

	// ���� �ִϸ��̼�
	CAnimation* m_pBuildAnim = nullptr;

	// ���׷��̵�/����ġ �ִϸ��̼�
	CAnimation* m_pUpgradeAnim = nullptr;

	// �ֵ�� ���� �ִϸ��̼�
	CAnimation* m_pAddOnConnectAnim = nullptr;

	// �ΰ� �ʻ�ȭ
	CAnimation* m_pBuildingPortrait = nullptr;

	// ���� ü�� ��
	int32 m_iCurHPColor = RGB(0, 255, 0);

	// ū ���̾������� ����
	CSprite* m_pBigWireframe[6]{ nullptr };

	// ���� ü���� ���̾�������
	CSprite* m_pCurBigWireframe = nullptr;

public:
	CAnimation* GetPortraitAnim() { return m_pBuildingPortrait; }
	void SetPortraitAnim(CAnimation* _pBuildingPortrait) { m_pBuildingPortrait = _pBuildingPortrait; }

	CSprite* GetCurBigWireframeSprite() { return m_pCurBigWireframe; }
	void SetCurBigWireframeSprite(CSprite* _pCurBigWireframe) { m_pCurBigWireframe = _pCurBigWireframe; }

	int32 GetCurHPColor() { return m_iCurHPColor; }
	void SetCurHPColor(int32 _iCurHPColor) { m_iCurHPColor = _iCurHPColor; }
};

