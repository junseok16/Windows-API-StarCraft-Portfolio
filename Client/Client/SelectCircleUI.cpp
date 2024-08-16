#include "pch.h"
#include "SelectCircleUI.h"

#include "SceneManager.h"

#include "TerranObject.h"
#include "Sprite.h"
#include "Scene.h"

void CSelectCircleUI::Initialize()
{
	CSpriteUI::Initialize();
	SetPosition({ m_pCircleOwner->GetPosition().m_fX, m_pCircleOwner->GetPosition().m_fY + 8.0f });
}

void CSelectCircleUI::Update()
{
	CSpriteUI::Update();
	UpdateUIPosition();
}

void CSelectCircleUI::LateUpdate()
{
	CSpriteUI::LateUpdate();
}

void CSelectCircleUI::Render(HDC _hDC)
{
	VERIFY_NULLPTR(m_pCircleOwner);
	if (m_pCircleOwner->GetSelected())
	{
		VERIFY_NULLPTR(m_pSprite);
		tagSpriteInfo tSpriteInfo = m_pSprite->GetSpriteInfo();

		Vector2Int tSize = tSpriteInfo.m_tSize;
		Vector2Int tPosition = tSpriteInfo.m_tPosition;
		uint32 uiAlpha = m_pSprite->GetTextureAlpha();

		// ��ũ�ѵ� ��ġ�� ���մϴ�.
		CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
		Vector2 tCameraPosition = pCurScene->GetCameraPosition();

		if (m_bGdiRender == false)
		{
			::BitBlt(_hDC,																				// �纻 �̹����� DC
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),	// �纻 �̹������� ���� �̹����� ������ �»�� ��ġ
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,																			// ���� �̹����� �غ�
				tSize.m_iHeight,																		// ���� �̹����� ����
				m_pSprite->GetTextureDC(),																// ���� �̹����� DC
				tPosition.m_iX,																			// ���� �̹����� �»�� ��ġ
				tPosition.m_iY,
				SRCCOPY);
		}
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
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
}

void CSelectCircleUI::Release()
{
	CSpriteUI::Release();
}

void CSelectCircleUI::UpdateUIPosition()
{
	VERIFY_NULLPTR(m_pCircleOwner);
	SetPosition({ m_pCircleOwner->GetPosition().m_fX, m_pCircleOwner->GetPosition().m_fY + 8.0f });
}
