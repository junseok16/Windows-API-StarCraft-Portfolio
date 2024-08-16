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
	데이터시트에 있는 속성들
******************************/
protected:
	// 건물 속성 데이터시트
	CBuildingProperty& m_buildingProperty;

	// 현재 체력
	int32 m_iCurHP = 0;

	// 현재 마력
	int32 m_iCurMP = 0;

	// 현재 실드
	int32 m_iCurShield = 0;

	// 현재 속도
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
	데이터시트에 없는 속성들
******************************/
protected:
	// 방향
	EDirectionState m_eDirectionState = EDirectionState::SOUTH;

	// 각도
	float m_iRadian = 0.0f;

	// 출발지 타일 위치
	Vector2Int m_tSrcTilePosition{ 0, 0 };

	// 도착지 타일 위치
	Vector2Int m_tDstTilePosition{ 0, 0 };

	// 출발지 위치
	Vector2 m_tSrcPosition{ 0.0f, 0.0f };

	// 도착지 위치
	Vector2 m_tDstPosition{ 0.0f, 0.0f };

	// 집결 지점 타일 위치
	Vector2Int m_tRallyTilePosition{ 0, 0 };
	
	// 집결 지점 위치
	Vector2 m_tRallyPosition{ 0.0f, 0.0f };

	// 집결 지점 여부
	bool m_bRallyPoint = false;

public:
	void SetRallyTilePosition(Vector2Int _tRallyTilePosition) { m_tRallyTilePosition = _tRallyTilePosition; }
	Vector2Int GetRallyTilePosition() const { return m_tRallyTilePosition; }

/******************************
	건물이 갖고 있는 명령들
******************************/
protected:
	// 건물 타입
	ETerranBuildingType m_eTerranBuildingType = ETerranBuildingType::ENUM_END;

	// 목표로 설정된 적군
	CTerranObject* m_pTarget = nullptr;

	// 공격 주기 카운터
	float m_fCurAttackDeltaSeconds = 0.0f;

	// 건설 시간 카운터
	float m_pCurCnstrctnDeltaSeconds = 0.0f;

	// 생산 시간 카운터
	float m_fCurBuildDeltaSecond = 0.0f;

	// 업그레이드 시간 카운터
	float m_fCurUpgradeDeltaSecond = 0.0f;

	// 생산 큐
	std::deque<ETerranUnitType> m_queBuildingUnits;

	// 업그레이드/리서치 큐
	std::deque<ETerranUpgradeType> m_queUpgrades;

public:
	ETerranBuildingType GetTerranBuildingType() const { return m_eTerranBuildingType; }
	void SetTerranBuildingType(ETerranBuildingType _eTerranBuildingType) { m_eTerranBuildingType = _eTerranBuildingType; }

	CTerranObject* GetTarget() const { return m_pTarget; }
	void SetTarget(CTerranObject* _pTarget) { m_pTarget = _pTarget; }

	std::deque<ETerranUnitType>& GetBuildingUnitsQueue() { return m_queBuildingUnits; }

	std::deque<ETerranUpgradeType>& GetUpgradesQueue() { return m_queUpgrades; }

/******************************
	건물의 스프라이트
******************************/
protected:
	// 건설 애니메이션
	CAnimation* m_pCnstrctnAnim = nullptr;

	// 지상 정지 애니메이션
	CAnimation* m_pLandAnim = nullptr;

	// 공중 정지 애니메이션
	CAnimation* m_pLiftAnim = nullptr;

	// 이륙 애니메이션
	CAnimation* m_pLiftingAnim = nullptr;

	// 착륙 애니메이션
	CAnimation* m_pLandingAnim = nullptr;

	// 생산 애니메이션
	CAnimation* m_pBuildAnim = nullptr;

	// 업그레이드/리서치 애니메이션
	CAnimation* m_pUpgradeAnim = nullptr;

	// 애드온 연결 애니메이션
	CAnimation* m_pAddOnConnectAnim = nullptr;

	// 부관 초상화
	CAnimation* m_pBuildingPortrait = nullptr;

	// 현재 체력 색
	int32 m_iCurHPColor = RGB(0, 255, 0);

	// 큰 와이어프레임 모음
	CSprite* m_pBigWireframe[6]{ nullptr };

	// 현재 체력의 와이어프레임
	CSprite* m_pCurBigWireframe = nullptr;

public:
	CAnimation* GetPortraitAnim() { return m_pBuildingPortrait; }
	void SetPortraitAnim(CAnimation* _pBuildingPortrait) { m_pBuildingPortrait = _pBuildingPortrait; }

	CSprite* GetCurBigWireframeSprite() { return m_pCurBigWireframe; }
	void SetCurBigWireframeSprite(CSprite* _pCurBigWireframe) { m_pCurBigWireframe = _pCurBigWireframe; }

	int32 GetCurHPColor() { return m_iCurHPColor; }
	void SetCurHPColor(int32 _iCurHPColor) { m_iCurHPColor = _iCurHPColor; }
};

