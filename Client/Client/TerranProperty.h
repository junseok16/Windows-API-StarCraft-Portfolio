#pragma once

class CTerranProperty
{
public:
	CTerranProperty(
		std::wstring _strName,		// 이름
		ERaceType _eRaceType,		// 종족
		Vector2Int _tTileSize,		// 차지하는 타일 크기
		int32 _iMaxHP,				// 최대 체력
		int32 _iMaxMP,				// 최대 마력
		int32 _iMaxShield,			// 최대 실드
		int32 _iAttackPoint,		// 공격력
		int32 _iDefensePoint,		// 방어력
		float _fSpeed,				// 이동 속도
		float _fAttackDeltaSeconds,	// 공격 주기
		int32 _iSight,				// 시야
		int32 _iRange,				// 사거리
		int32 _iMineral,			// 소비 미네랄
		int32 _iGas,				// 소비 가스
		int32 _iSeconds				// 생산 시간
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
	// 유닛, 건물 이름
	std::wstring m_strName = L"";

	// 종족 타입
	ERaceType m_eRaceType = ERaceType::ENUM_END;

	// 차지하는 타일 사이즈
	Vector2Int m_tTileSize{ 1, 1 };

	// 최대 체력
	int32 m_iMaxHP = 0;

	// 최대 마력
	int32 m_iMaxMP = 0;

	// 최대 실드
	int32 m_iMaxShield = 0;

	// 공격력
	int32 m_iAttackPoint = 0;

	// 방어력
	int32 m_iDefensePoint = 0;

	// 이동 속도
	float m_fSpeed = 0.0f;

	// 공격 주기
	float m_fAttackDeltaSeconds = 0.0f;

	// 시야
	int32 m_iSight = 0;

	// 사거리
	int32 m_iRange = 0;

	// 미네랄
	int32 m_iMineral = 0;

	// 가스
	int32 m_iGas = 0;

	// 생산 시간
	int32 m_iSeconds = 0;

	// 공격 타입(일반형, 진동형, 폭발형) > 우선순위 낮음

	// 크기 타입(소형, 중형, 대형) > 우선순위 낮음

	// 유닛 타입 (생체, 기계) > 우선순위 낮음

	// 애니메이션
};

