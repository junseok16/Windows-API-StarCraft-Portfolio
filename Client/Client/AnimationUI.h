#pragma once
#include "UI.h"

class CAnimation;

class CAnimationUI : public CUI
{
/***************
	�޼���
***************/
public:
	CAnimationUI() = default;
	virtual ~CAnimationUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetAnimation(CAnimation* _pAnimation) { m_pAnimation = _pAnimation; }
	CAnimation* GetAnimation() { return m_pAnimation; }

/***************
	������ ���
***************/
protected:
	CAnimation* m_pAnimation = nullptr;

private:
	float m_fSumDeltaSeconds = 0.0f;
	int32 m_iOffset = 0;
};

