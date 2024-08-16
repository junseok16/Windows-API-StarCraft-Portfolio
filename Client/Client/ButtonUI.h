#pragma once
#include "UI.h"

class CSprite;

class CButtonUI : public CUI
{
public:
	CButtonUI() = default;
	virtual ~CButtonUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

	virtual void OnButtonClick();

public:
	EButtonState GetButtonState() const { return m_eButtonState; }
	void SetButtonState(EButtonState _eButtonState);

	CSprite* GetCurSprite() const { return m_pCurSprite; }
	void SetCurSprite(CSprite* _pCurSprite) { m_pCurSprite = _pCurSprite; }

	CSprite* GetSpriteAt(EButtonState _eButtonState) const { return m_arrSprites[(int32)_eButtonState]; }
	void SetSpriteAt(EButtonState _eButtonState, CSprite* _pSprite) { m_arrSprites[(int32)_eButtonState] = _pSprite; }

	//void SetActive(bool _bActive) { m_bActive = _bActive; }
	//bool GetActive() const { return m_bActive; }

private:
	void UpdateButtonState();

protected:
	// ��ư Ȱ��ȭ ����
	//bool m_bActive = true;

	// Ŭ���� �����ϱ� ���� ����
	float m_fSumDeltaSeconds = 0.0f;

	// ��ư ����
	EButtonState m_eButtonState = EButtonState::RELEASE;

	// ���� ��������Ʈ
	CSprite* m_pCurSprite = nullptr;
	
	// ��ư ���¿� ���� ����� ��������Ʈ
	std::array<CSprite*, (int32)EButtonState::ENUM_END> m_arrSprites{ nullptr };

public:
	template<typename T>
	void InsertOnClickDelegate(T* _pOwner, void(T::*function)())
	{
		m_fpOnClick = [_pOwner, function]()
		{
			(_pOwner->*function)();
		};
	}

public:
	std::function<void(void)> m_fpOnClick = nullptr;
};

