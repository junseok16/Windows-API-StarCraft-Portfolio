#include "pch.h"
#include "AnimationObject.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Animation.h"
using namespace std;

void CAnimationObject::Initialize()
{
	CObject::Initialize();
}

void CAnimationObject::Update()
{
	CObject::Update();

	// �ִϸ��̼��� ������Ʈ�մϴ�.
	VERIFY_NULLPTR(m_pAnimation);
	tagAnimationInfo tAnimationInfo = m_pAnimation->GetAnimationInfo();

	pair<int32, int32> tXIndex{ 0, 0 };
	pair<int32, int32> tYIndex{ 0, 0 };
	int32 iNumSprite = 0;
	float fDeltaDuration = 0.0f;

	// �ִϸ��̼��� �ε����� �����մϴ�.
	if (tAnimationInfo.m_bVertical == true)
	{
		// �ִϸ��̼��� ��� �� ������ �����Ǿ� �ִٰ� �����մϴ�.
		tYIndex = tAnimationInfo.m_tYIndex;
		iNumSprite = tYIndex.second - tYIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}
	else
	{
		// �ִϸ��̼��� ��� �� �࿡�� �����Ǿ� �ִٰ� �����մϴ�.
		tXIndex = tAnimationInfo.m_tXIndex;
		iNumSprite = tXIndex.second - tXIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}


	m_fSumDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

	// �� ���� �ִϸ��̼��� �����մϴ�.
	if (tAnimationInfo.m_bPlayOnce == true)
	{
		if (m_fSumDeltaSeconds >= fDeltaDuration)
		{
			m_fSumDeltaSeconds = 0.0f;
			m_iOffset = (m_iOffset + 1) % iNumSprite;

			if (m_iOffset == 0) { m_iOffset = iNumSprite - 1; }
		}
	}
	// �ݺ��ؼ� �ִϸ��̼��� �����մϴ�.
	else if (tAnimationInfo.m_bRepeat == true)
	{
		// ���� ��������Ʈ�� �����ϵ��� �������� ������ŵ�ϴ�.
		if (m_fSumDeltaSeconds >= fDeltaDuration)
		{
			m_fSumDeltaSeconds = 0.0f;
			m_iOffset = (m_iOffset + 1) % iNumSprite;
		}
	}
}

void CAnimationObject::LateUpdate()
{
	CObject::LateUpdate();
}

void CAnimationObject::Render(HDC _hDC)
{
	CObject::Render(_hDC);

	VERIFY_NULLPTR(m_pAnimation);
	tagAnimationInfo tAnimationInfo = m_pAnimation->GetAnimationInfo();

	bool bVertical = tAnimationInfo.m_bVertical;
	Vector2Int tSize = tAnimationInfo.m_tSize;
	pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
	pair<int32, int32> tYIndex = tAnimationInfo.m_tYIndex;
	uint32 uiAlpha = m_pAnimation->GetTextureAlpha();

	// ī�޶� ��ġ�� ���մϴ�.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				(tXIndex.first + m_iOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				SRCCOPY);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			::BitBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iOffset) * tSize.m_iHeight,
				SRCCOPY);
		}
	}
	else
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				(tXIndex.first + m_iOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iOffset) * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
}

void CAnimationObject::Release()
{
	CObject::Release();
}

void CAnimationObject::SetAnimation(CAnimation* _pAnimation)
{
	VERIFY_NULLPTR(_pAnimation);
	if (m_pAnimation == _pAnimation) { return; }
	m_pAnimation = _pAnimation;

	SetOffset(0);
	SetDeltaSeconds(0.0f);
}
