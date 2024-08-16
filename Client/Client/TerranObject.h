#pragma once
#include "AnimationObject.h"

class CCommand;
class CSpriteUI;
class CSelectCircleUI;
class CHPBarUI;
class CMPBarUI;

class CTerranObject : public CAnimationObject
{
public:
	CTerranObject() = default;
	virtual ~CTerranObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;


/******************************
	유닛/건물, 소유자, 타일 위치
******************************/
protected:
	// 유닛, 건물 여부
	ETerranObjectType m_eTerranObjectType = ETerranObjectType::ENUM_END;

	// 소유자 여부
	EOwnerType m_eOwnerType = EOwnerType::ENUM_END;

	// 좌상단 기준 이전 타일 위치
	Vector2Int m_tPrevTilePosition{ 0, 0 };

	// 좌상단 기준 현재 타일 위치
	Vector2Int m_tCurTilePosition{ 0, 0 };

public:
	void SetTerranObjectType(ETerranObjectType _eTerranObjectType) { m_eTerranObjectType = _eTerranObjectType; }
	ETerranObjectType GetTerranObjectType() const { return m_eTerranObjectType; }

	void SetOwnerType(EOwnerType _eOwnerType) { m_eOwnerType = _eOwnerType; }
	EOwnerType GetOwnerType() const { return m_eOwnerType; }

	void SetPrevTilePosition(Vector2Int _tPrevTilePosition) { m_tPrevTilePosition = _tPrevTilePosition; }
	Vector2Int GetPrevTilePosition() const { return m_tPrevTilePosition; }

	void SetCurTilePosition(Vector2Int _tCurTilePosition) { m_tCurTilePosition = _tCurTilePosition; }
	Vector2Int GetCurTilePosition() const { return m_tCurTilePosition; }


/******************************
	사망, 메모리 해제
******************************/
protected:
	// 사망 여부
	bool m_bDead = false;

	// 메모리 해제 여부
	bool m_bReady2Delete = false;

	// 사망 처리 여부
	bool m_bDeadHandle = false;

	// 사망 전환 카운터
	float m_fDeadDelay = 0.0f;

public:
	void SetDead(bool _bDead) { m_bDead = _bDead; }

	bool GetDead() const { return m_bDead; }

	void SetReady2Delete(bool _bReady2Delete) { m_bReady2Delete = _bReady2Delete; }

	bool GetReady2Delete() const { return m_bReady2Delete; }


/******************************
	명령 큐, 명령 창
******************************/
protected:
	// 명령 큐
	std::queue<CCommand*> m_queCommands;

	// 유닛 명령창 상태
	ECommandWidgetState m_eCommandWidgetState = ECommandWidgetState::ENUM_END;

	// 유닛이 갖고 있는 명령어 모음
	std::vector<ECommandType> m_vecCommandTypes[(int32)ECommandWidgetState::ENUM_END];

public:
	void SetCurCommandWidgetState(ECommandWidgetState _eCommandWidgetState) { m_eCommandWidgetState = _eCommandWidgetState; }
	ECommandWidgetState GetCurCommandWidgetState() const { return m_eCommandWidgetState; }

	// void SetCurCommandTypes(ECommandWidgetState _eCommandWidgetState) { m_eCommandWidgetState = _eCommandWidgetState; }
	std::vector<ECommandType>& GetCurCommandTypes() { return m_vecCommandTypes[(int32)m_eCommandWidgetState]; }

	void PushCommandQueue(CCommand* _pCommand);

	void PopCommandQueue();

	CCommand* FrontCommandQueue();

	int32 SizeCommandQueue();

	bool IsEmptyCommandQueue();


/******************************
	A* 알고리즘 경로
******************************/
protected:
	// 길 찾기 경로
	std::queue<Vector2Int> m_queOptimalPath;

	std::vector<Vector2Int> m_vecOptimalPath;

public:
	std::queue<Vector2Int>& GetQueOptimalPath() { return m_queOptimalPath; }

	std::vector<Vector2Int>& GetVecOptimalPath() { return m_vecOptimalPath; }

/******************************
	인 게임 사용자 인터페이스
******************************/
protected:
	// 선택 여부
	bool m_bSelected = false;

	// 원 사용자 인터페이스
	CSelectCircleUI* m_pCircleUI = nullptr;

	// 체력바, 마력바 사용자 인터페이스
	CHPBarUI* m_pHPBarUI = nullptr;

	CMPBarUI* m_pMPBarUI = nullptr;

public:
	void SetSelected(bool _bSelected) { m_bSelected = _bSelected; }

	bool GetSelected() const { return m_bSelected; }
};

