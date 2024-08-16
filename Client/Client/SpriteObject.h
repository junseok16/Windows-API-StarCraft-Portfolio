#pragma once
#include "Object.h"

class CSprite;

class CSpriteObject : public CObject
{
/***************
	메서드
***************/
public:
	CSpriteObject() = default;
	virtual ~CSpriteObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetSprite(CSprite* _pSprite) { m_pSprite = _pSprite; }
	CSprite* GetSprite() { return m_pSprite; }


/***************
	데이터 멤버
***************/
protected:
	CSprite* m_pSprite = nullptr;
};

