#pragma once

class CComponent;
class CColliderComponent;

class CObject
{
/***************
	메서드
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
	데이터 멤버
***************/
protected:
	// BitBlt 혹은 GdiTransparentBlt 렌더 여부
	bool m_bGdiRender = true;

	// 오브젝트의 레이어 타입
	EObjectType m_eObjectType = EObjectType::ENUM_END;

	// 오브젝트의 절대 위치(0.0f ~ 4096.f)
	Vector2 m_tPosition{ 0.0f, 0.0f };

	// 오브젝트의 크기
	Vector2Int m_tSize{ 0, 0 };

	// 오브젝트가 갖고 있는 컴포넌트
	std::list<CComponent*> m_lstComponents;
};

