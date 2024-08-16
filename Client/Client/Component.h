#pragma once

class CObject;

class CComponent abstract
{
/***************
	메서드
***************/
public:
	CComponent() = default;
	virtual ~CComponent() = default;

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC _hDC) = 0;
	virtual void Release() = 0;

public:
	CObject* GetComponentOwner() const { return m_pComponentOwner; }
	void SetComponentOwner(CObject* _pComponentOwner) { m_pComponentOwner = _pComponentOwner; }

/***************
	데이터 멤버
***************/
protected:
	// 이 컴포넌트를 갖고 있는 오브젝트 포인터
	CObject* m_pComponentOwner = nullptr;
};

