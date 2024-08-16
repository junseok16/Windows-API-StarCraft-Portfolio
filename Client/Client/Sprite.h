#pragma once
#include "ResourceEx.h"

class CTexture;

struct tagSpriteInfo final
{
	CTexture* m_pTexture = nullptr;	// ��������Ʈ�� ������ �ؽ�ó�� ������
	Vector2Int m_tPosition{ 0, 0 };	// ��������Ʈ�� ��ġ
	Vector2Int m_tSize{ 0, 0 };		// ��������Ʈ�� ����, ���� ����
};

class CSprite : public CResourceEx
{
/***************
	�޼���
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
	������ ���
***************/
private:
	tagSpriteInfo m_tSpriteInfo;
};

