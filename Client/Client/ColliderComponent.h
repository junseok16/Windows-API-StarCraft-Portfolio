#pragma once
#include "Component.h"

class CColliderComponent : public CComponent
{
/***************
	�޼���
***************/
public:
	CColliderComponent(EColliderType _eColliderType);
	virtual ~CColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

	virtual bool IsCollided(CColliderComponent* _pColliderComponent);

public:
	EColliderType GetColliderType() const { return m_eColliderType; }
	void SetColliderType(EColliderType _eColliderType) { m_eColliderType = _eColliderType; }
	
	bool GetDebug() const { return m_bDebug; }
	void SetDebug(bool _bDebug) { m_bDebug = _bDebug; }

	bool GetScroll() const { return m_bScroll; }
	void SetScroll(bool _bScroll) { m_bScroll = _bScroll; }

	void InsertCollider(CColliderComponent* _pColliderComponent);
	void EraseCollider(CColliderComponent* _pColliderComponent);

	std::unordered_set<CColliderComponent*>& GetColliderComponents() { return m_usetColliderComponents; }

protected:
	// �ݶ��̴� ���(�簢��, �� ��)
	EColliderType m_eColliderType = EColliderType::ENUM_END;

	// �ݶ��̴� �׵θ� �׸���
	bool m_bDebug = false;

	// ���콺 �ݶ��̴��� ��ũ�ѵ��� �ʵ��� �Ѵ�.
	bool m_bScroll = true;

	// �浹�� �ݶ��̴� ������Ʈ��
	std::unordered_set<CColliderComponent*> m_usetColliderComponents;

public:
	virtual bool VerifyCollisionType(CColliderComponent* _pColliderComponent);

	ECollisionType GetCollisionType() const { return m_eCollisionType; }
	void SetCollisionType(ECollisionType _eCollisionType) { m_eCollisionType = _eCollisionType; }

	void SetCollisionFlag(uint32 _uiCollisionFlag) { m_uiCollisionFlag = _uiCollisionFlag; }

	uint32 GetCollisionFlag() { return m_uiCollisionFlag; }

	void ResetCollisionFlag() { m_uiCollisionFlag = 0; }

	void InsertCollisionFlag(ECollisionType _eCollisionType);

	void EraseCollisionFlag(ECollisionType _eCollisionType);

protected:
	// �ݸ��� Ÿ��
	ECollisionType m_eCollisionType = ECollisionType::ENUM_END;

	uint32 m_uiCollisionFlag = 0x0000'0000;
};

