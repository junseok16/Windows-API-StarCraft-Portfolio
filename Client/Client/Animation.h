#pragma once
#include "ResourceEx.h"

class CTexture;

struct tagAnimationInfo final
{
	CTexture* m_pTexture = nullptr;		// �ִϸ��̼��� ������ �ؽ�ó ������
	std::wstring m_strName = L"";		// �ִϸ��̼� �̸�
	bool m_bVertical = false;			// ���� �ִϸ��̼� ����
	std::pair<int32, int32> m_tXIndex;	// �ִϸ��̼��� �����ϰ� ������ ��
	std::pair<int32, int32> m_tYIndex;	// �ִϸ��̼��� �����ϰ� ������ ��
	Vec2Int m_tSize{ 0, 0 };			// ��������Ʈ�� ũ��
	float m_fDuration = 1.0f;			// �ִϸ��̼� ���� �ð�
	bool m_bPlayOnce = false;			// �� ���� �÷��̵� �ʿ��ϴ�.
	bool m_bRepeat = true;				// �ִϸ��̼� �ݺ�
};

class CAnimation : public CResourceEx
{
public:
	CAnimation() = default;
	virtual ~CAnimation() = default;

public:
	HDC GetTextureDC() const;
	uint32 GetTextureAlpha() const;

public:
	tagAnimationInfo GetAnimationInfo() const { return m_tAnimationInfo; }
	void SetAnimationInfo(tagAnimationInfo _tAnimationInfo) { m_tAnimationInfo = _tAnimationInfo; }
	
private:
	tagAnimationInfo m_tAnimationInfo;
};

