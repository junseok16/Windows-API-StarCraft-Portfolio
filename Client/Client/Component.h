#pragma once

class CObject;

class CComponent abstract
{
/***************
	�޼���
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
	������ ���
***************/
protected:
	// �� ������Ʈ�� ���� �ִ� ������Ʈ ������
	CObject* m_pComponentOwner = nullptr;
};

