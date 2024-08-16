#include "pch.h"
#include "SpriteUI.h"
#include "Sprite.h"

void CSpriteUI::Initialize()
{
	CUI::Initialize();
}

void CSpriteUI::Update()
{
	CUI::Update();
	if (!m_bUIActive) { return; }
}

void CSpriteUI::LateUpdate()
{
	CUI::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CSpriteUI::Render(HDC _hDC)
{
	CUI::Render(_hDC);
	if (!m_bUIActive) { return; }

	if (m_pSprite != nullptr)
	{
		tagSpriteInfo tSpriteInfo = m_pSprite->GetSpriteInfo();

		Vector2Int tSize = tSpriteInfo.m_tSize;
		Vector2Int tPosition = tSpriteInfo.m_tPosition;
		uint32 uiAlpha = m_pSprite->GetTextureAlpha();

		if (m_bGdiRender == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pSprite->GetTextureDC(),
				tPosition.m_iX,
				tPosition.m_iY,
				SRCCOPY);
		}
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pSprite->GetTextureDC(),
				tPosition.m_iX,
				tPosition.m_iY,
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

void CSpriteUI::Release()
{
	CUI::Release();
}
