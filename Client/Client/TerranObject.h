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
	����/�ǹ�, ������, Ÿ�� ��ġ
******************************/
protected:
	// ����, �ǹ� ����
	ETerranObjectType m_eTerranObjectType = ETerranObjectType::ENUM_END;

	// ������ ����
	EOwnerType m_eOwnerType = EOwnerType::ENUM_END;

	// �»�� ���� ���� Ÿ�� ��ġ
	Vector2Int m_tPrevTilePosition{ 0, 0 };

	// �»�� ���� ���� Ÿ�� ��ġ
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
	���, �޸� ����
******************************/
protected:
	// ��� ����
	bool m_bDead = false;

	// �޸� ���� ����
	bool m_bReady2Delete = false;

	// ��� ó�� ����
	bool m_bDeadHandle = false;

	// ��� ��ȯ ī����
	float m_fDeadDelay = 0.0f;

public:
	void SetDead(bool _bDead) { m_bDead = _bDead; }

	bool GetDead() const { return m_bDead; }

	void SetReady2Delete(bool _bReady2Delete) { m_bReady2Delete = _bReady2Delete; }

	bool GetReady2Delete() const { return m_bReady2Delete; }


/******************************
	��� ť, ��� â
******************************/
protected:
	// ��� ť
	std::queue<CCommand*> m_queCommands;

	// ���� ���â ����
	ECommandWidgetState m_eCommandWidgetState = ECommandWidgetState::ENUM_END;

	// ������ ���� �ִ� ��ɾ� ����
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
	A* �˰��� ���
******************************/
protected:
	// �� ã�� ���
	std::queue<Vector2Int> m_queOptimalPath;

	std::vector<Vector2Int> m_vecOptimalPath;

public:
	std::queue<Vector2Int>& GetQueOptimalPath() { return m_queOptimalPath; }

	std::vector<Vector2Int>& GetVecOptimalPath() { return m_vecOptimalPath; }

/******************************
	�� ���� ����� �������̽�
******************************/
protected:
	// ���� ����
	bool m_bSelected = false;

	// �� ����� �������̽�
	CSelectCircleUI* m_pCircleUI = nullptr;

	// ü�¹�, ���¹� ����� �������̽�
	CHPBarUI* m_pHPBarUI = nullptr;

	CMPBarUI* m_pMPBarUI = nullptr;

public:
	void SetSelected(bool _bSelected) { m_bSelected = _bSelected; }

	bool GetSelected() const { return m_bSelected; }
};

