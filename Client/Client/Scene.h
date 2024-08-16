#pragma once

class CObject;
class CPlayer;
class CCursor;
class CUI;
class CTilemapObject;

class CScene
{
/***************
	�޼���
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
	������ ���
***************/
public:
	// �ſ� �ִ� �÷��̾�
	static CPlayer* s_pPlayer;

	// �ſ� �ִ� Ŀ��
	static CCursor* s_pCursor;

protected:
	// ī�޶��� �߽� ��ġ
	Vector2 m_tCameraPosition{ FWINCX * 0.5f, FWINCY * 0.5f };

	// �ſ� �ִ� ���� Ÿ�ϸ� ������Ʈ
	CTilemapObject* m_pStaticTilemapObject = nullptr;

	// �ſ� �ִ� ���� Ÿ�ϸ� ������Ʈ
	CTilemapObject* m_pDynamicTilemapObject = nullptr;

	// �ſ� �ִ� ��� ������Ʈ
	std::list<CObject*> m_lstObjects[(int32)EObjectType::ENUM_END];

	// �ſ� �ִ� ��� UI
	std::list<CUI*> m_lstStaticUIs;

	std::list<CUI*> m_lstDynamicUIs;
};

