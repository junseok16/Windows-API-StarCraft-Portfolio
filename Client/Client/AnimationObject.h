#pragma once
#include "Object.h"

class CAnimation;

class CAnimationObject : public CObject
{
/***************
	메서드
***************/
public:
	CAnimationObject() = default;
	virtual ~CAnimationObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetAnimation(CAnimation* _pAnimation);
	CAnimation* GetAnimation() { return m_pAnimation; }

private:
	void SetOffset(int32 _iOffset) { m_iOffset = _iOffset; }
	void SetDeltaSeconds(float _fSumDeltaSeoncds) { m_fSumDeltaSeconds = _fSumDeltaSeoncds; };

/***************
	데이터 멤버
***************/
protected:
	CAnimation* m_pAnimation = nullptr;

	float m_fSumDeltaSeconds = 0.0f;

	int32 m_iOffset = 0;
};

