#pragma once
#include "ResourceEx.h"

class CTexture;

struct tagSpriteInfo final
{
	CTexture* m_pTexture = nullptr;	// 스프라이트를 생성할 텍스처의 포인터
	Vector2Int m_tPosition{ 0, 0 };	// 스프라이트의 위치
	Vector2Int m_tSize{ 0, 0 };		// 스프라이트의 가로, 세로 길이
};

class CSprite : public CResourceEx
{
/***************
	메서드
***************/
public:
	// CSprite(CTexture* _pTexture, int32 _iX, int32 _iY, int32 _iWidth, int32 _iHeight);
	CSprite() = default;
	virtual ~CSprite() = default;

public:
	HDC GetTextureDC() const;
	uint32 GetTextureAlpha() const;

public:
	tagSpriteInfo GetSpriteInfo() const { return m_tSpriteInfo; }
	void SetSpriteInfo(tagSpriteInfo _tSpriteInfo) { m_tSpriteInfo = _tSpriteInfo; }

	/*
	Vector2Int GetPosition() const { return m_tPosition; }
	void SetPosition(Vector2Int _tPosition) { m_tPosition = _tPosition; }

	Vector2Int GetSize() const { return m_tSize; }
	void SetSize(Vector2Int _tSize) { m_tSize = _tSize; }
	*/

/***************
	데이터 멤버
***************/
private:
	tagSpriteInfo m_tSpriteInfo;
};

