#pragma once
#include "ButtonUI.h"

#include "Unit.h"

class CSmallProfileButton : public CButtonUI
{
public:
	CSmallProfileButton() = default;
	virtual ~CSmallProfileButton() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnButtonClick() override;

public:
	void SetButtonOwner(CUnit* _pButtonOwner) { m_pButtonOwner = _pButtonOwner; }
	CUnit* GetButtonOwner() const { return m_pButtonOwner; }

private:
	// 버튼을 소유한 주인
	CUnit* m_pButtonOwner = nullptr;
};

