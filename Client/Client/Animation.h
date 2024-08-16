#pragma once
#include "ResourceEx.h"

class CTexture;

struct tagAnimationInfo final
{
	CTexture* m_pTexture = nullptr;		// 애니메이션을 생성할 텍스처 포인터
	std::wstring m_strName = L"";		// 애니메이션 이름
	bool m_bVertical = false;			// 세로 애니메이션 여부
	std::pair<int32, int32> m_tXIndex;	// 애니메이션이 시작하고 끝나는 열
	std::pair<int32, int32> m_tYIndex;	// 애니메이션이 시작하고 끝나는 행
	Vec2Int m_tSize{ 0, 0 };			// 스프라이트의 크기
	float m_fDuration = 1.0f;			// 애니메이션 실행 시간
	bool m_bPlayOnce = false;			// 한 번만 플레이도 필요하다.
	bool m_bRepeat = true;				// 애니메이션 반복
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

