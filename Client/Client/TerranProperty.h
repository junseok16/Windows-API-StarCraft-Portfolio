#pragma once

class CTerranProperty
{
public:
	CTerranProperty(
		std::wstring _strName,		// �̸�
		ERaceType _eRaceType,		// ����
		Vector2Int _tTileSize,		// �����ϴ� Ÿ�� ũ��
		int32 _iMaxHP,				// �ִ� ü��
		int32 _iMaxMP,				// �ִ� ����
		int32 _iMaxShield,			// �ִ� �ǵ�
		int32 _iAttackPoint,		// ���ݷ�
		int32 _iDefensePoint,		// ����
		float _fSpeed,				// �̵� �ӵ�
		float _fAttackDeltaSeconds,	// ���� �ֱ�
		int32 _iSight,				// �þ�
		int32 _iRange,				// ��Ÿ�
		int32 _iMineral,			// �Һ� �̳׶�
		int32 _iGas,				// �Һ� ����
		int32 _iSeconds				// ���� �ð�
	);

	virtual ~CTerranProperty() = default;

public:
	std::wstring GetName() const { return m_strName; }
	
	ERaceType GetRaceType() const { return m_eRaceType; }
	
	Vector2Int GetTileSize() const { return m_tTileSize; }
	
	int32 GetMaxHP() const { return m_iMaxHP; }
	
	int32 GetMaxMP() const { return m_iMaxMP; }
	void SetMaxMP(int32 _iMaxMP) { m_iMaxMP = _iMaxMP; }

	int32 GetMaxShield() const { return m_iMaxShield; }
	void SetMaxShield(int32 _iMaxShield) { m_iMaxShield = _iMaxShield; }

	int32 GetAttackPoint() const { return m_iAttackPoint; }
	void SetAttackPoint(int32 _iAttackPoint) { m_iAttackPoint = _iAttackPoint; }
	
	int32 GetDefensePoint() const { return m_iDefensePoint; }
	void SetDefensePoint(int32 _iDefensePoint) { m_iDefensePoint = _iDefensePoint; }
	
	float GetSpeed() const { return m_fSpeed; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	
	float GetAttackDeltaSeconds() const { return m_fAttackDeltaSeconds; }
	void SetAttackDeltaSeconds(float _fAttackDeltaSeconds) { m_fAttackDeltaSeconds = _fAttackDeltaSeconds; }

	int32 GetSight() const { return m_iSight; }
	
	int32 GetRange() const { return m_iRange; }
	void SetRange(int32 _iRange) { m_iRange = _iRange; }

	int32 GetMineral() const { return m_iMineral; }
	
	int32 GetGas() const { return m_iGas; }
	
	int32 GetSeconds() const { return m_iSeconds; }

protected:
	// ����, �ǹ� �̸�
	std::wstring m_strName = L"";

	// ���� Ÿ��
	ERaceType m_eRaceType = ERaceType::ENUM_END;

	// �����ϴ� Ÿ�� ������
	Vector2Int m_tTileSize{ 1, 1 };

	// �ִ� ü��
	int32 m_iMaxHP = 0;

	// �ִ� ����
	int32 m_iMaxMP = 0;

	// �ִ� �ǵ�
	int32 m_iMaxShield = 0;

	// ���ݷ�
	int32 m_iAttackPoint = 0;

	// ����
	int32 m_iDefensePoint = 0;

	// �̵� �ӵ�
	float m_fSpeed = 0.0f;

	// ���� �ֱ�
	float m_fAttackDeltaSeconds = 0.0f;

	// �þ�
	int32 m_iSight = 0;

	// ��Ÿ�
	int32 m_iRange = 0;

	// �̳׶�
	int32 m_iMineral = 0;

	// ����
	int32 m_iGas = 0;

	// ���� �ð�
	int32 m_iSeconds = 0;

	// ���� Ÿ��(�Ϲ���, ������, ������) > �켱���� ����

	// ũ�� Ÿ��(����, ����, ����) > �켱���� ����

	// ���� Ÿ�� (��ü, ���) > �켱���� ����

	// �ִϸ��̼�
};

