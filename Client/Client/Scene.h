#pragma once

class CObject;
class CPlayer;
class CCursor;
class CUI;
class CTilemapObject;

class CScene
{
/***************
	메서드
***************/
public:
	CScene() = default;
	virtual ~CScene() = default;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void SetCameraPosition(Vector2 _tCameraPosition) { m_tCameraPosition = _tCameraPosition; }
	Vector2 GetCameraPosition() const { return m_tCameraPosition; }

	void SetPlayer(CPlayer* _pPlayer) { s_pPlayer = _pPlayer; }
	CPlayer* GetPlayer() const { return s_pPlayer; }

	CTilemapObject* GetStaticTilemapObject() const { return m_pStaticTilemapObject; }

	CTilemapObject* GetDynamicTilemapObject() const { return m_pDynamicTilemapObject; }

public:
	std::list<CObject*>& GetUnits() { return m_lstObjects[(int32)EObjectType::UNIT]; }
	
	std::list<CObject*>& GetBuildings() { return m_lstObjects[(int32)EObjectType::BUILDING]; }

	std::list<CUI*>& GetStaticUIs() { return m_lstStaticUIs; }

	void InsertObject(CObject* _pObject);
	void EraseObject(CObject* _pObject);

	void InsertStaticUI(CUI* _pUI);
	void EraseStaticUI(CUI* _pUI);

	void InsertDynamicUI(CUI* _pUI);
	void EraseDynamicUI(CUI* _pUI);

/***************
	데이터 멤버
***************/
public:
	// 신에 있는 플레이어
	static CPlayer* s_pPlayer;

	// 신에 있는 커서
	static CCursor* s_pCursor;

protected:
	// 카메라의 중심 위치
	Vector2 m_tCameraPosition{ FWINCX * 0.5f, FWINCY * 0.5f };

	// 신에 있는 정적 타일맵 오브젝트
	CTilemapObject* m_pStaticTilemapObject = nullptr;

	// 신에 있는 동적 타일맵 오브젝트
	CTilemapObject* m_pDynamicTilemapObject = nullptr;

	// 신에 있는 모든 오브젝트
	std::list<CObject*> m_lstObjects[(int32)EObjectType::ENUM_END];

	// 신에 있는 모든 UI
	std::list<CUI*> m_lstStaticUIs;

	std::list<CUI*> m_lstDynamicUIs;
};

