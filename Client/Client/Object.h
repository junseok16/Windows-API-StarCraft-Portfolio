#pragma once

class CComponent;
class CColliderComponent;

class CObject
{
/***************
	�޼���
***************/
public:
	CObject() = default;
	virtual ~CObject() = default;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	Vector2 GetPosition() const { return m_tPosition; }
	void SetPosition(Vector2 _tPosition) { m_tPosition = _tPosition; }

	Vector2Int GetSize() const { return m_tSize; }
	void SetSize(Vector2Int _tSize) { m_tSize = _tSize; }

	EObjectType GetObjectType() const { return m_eObjectType; }
	void SetObjectType(EObjectType _eObjectType) { m_eObjectType = _eObjectType; }

	void SetGdiRender(bool _bGdiRender) { m_bGdiRender = _bGdiRender; }
	bool GetGdiRender() const { return m_bGdiRender; }

public:
	virtual void OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);
	virtual void OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);
	virtual void OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider);

	void InsertComponent(CComponent* _pComponent);
	void EraseComponent(CComponent* _pComponent);


/***************
	������ ���
***************/
protected:
	// BitBlt Ȥ�� GdiTransparentBlt ���� ����
	bool m_bGdiRender = true;

	// ������Ʈ�� ���̾� Ÿ��
	EObjectType m_eObjectType = EObjectType::ENUM_END;

	// ������Ʈ�� ���� ��ġ(0.0f ~ 4096.f)
	Vector2 m_tPosition{ 0.0f, 0.0f };

	// ������Ʈ�� ũ��
	Vector2Int m_tSize{ 0, 0 };

	// ������Ʈ�� ���� �ִ� ������Ʈ
	std::list<CComponent*> m_lstComponents;
};

