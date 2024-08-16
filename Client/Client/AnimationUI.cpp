#include "pch.h"
#include "AnimationUI.h"
#include "TimeManager.h"
#include "Animation.h"
using namespace std;

void CAnimationUI::Initialize()
{
	CUI::Initialize();
}

void CAnimationUI::Update()
{
	CUI::Update();

	if (!m_bUIActive) { return; }

	// �ִϸ��̼��� ������Ʈ�մϴ�.
	VERIFY_NULLPTR(m_pAnimation);
	tagAnimationInfo tAnimationInfo = m_pAnimation->GetAnimationInfo();

	if (tAnimationInfo.m_bRepeat == false) { return; }
	m_fSumDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

	// �ִϸ��̼��� ��� �� �࿡�� �����Ǿ� �ִٰ� �����մϴ�.
	pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
	int32 iNumSprite = tXIndex.second - tXIndex.first + 1;
	float fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;

	// ���� ��������Ʈ�� �����ϵ��� �������� ������ŵ�ϴ�.
	if (m_fSumDeltaSeconds >= fDeltaDuration)
	{
		m_fSumDeltaSeconds = 0.0f;
		m_iOffset = (m_iOffset + 1) % iNumSprite;
	}
}

void CAnimationUI::LateUpdate()
{
	CUI::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CAnimationUI::Render(HDC _hDC)
{
	CUI::Render(_hDC);
	if (!m_bUIActive) { return; }

	if (m_pAnimation != nullptr)
	{
		tagAnimationInfo tAnimationInfo = m_pAnimation->GetAnimationInfo();

		Vector2Int tSize = tAnimationInfo.m_tSize;
		pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
		pair<int32, int32> tYIndex = tAnimationInfo.m_tYIndex;
		uint32 uiAlpha = m_pAnimation->GetTextureAlpha();

		if (m_bGdiRender == false)
		{
			// TODO: ������ �߸� �־��� ���� �����ϱ� Ȯ���ؾ� �մϴ�.
			::BitBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				(tXIndex.first + m_iOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				SRCCOPY);
		}
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pAnimation->GetTextureDC(),
				(tXIndex.first + m_iOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
	else
	{
		CGeometry::DrawRectangle(_hDC, m_tPosition, m_tSize, RGB(0, 255, 0));
	}
}

void CAnimationUI::Release()
{
	CUI::Release();
}
