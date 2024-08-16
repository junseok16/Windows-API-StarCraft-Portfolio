#include "pch.h"
#include "SpriteObject.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Scene.h"

void CSpriteObject::Initialize()
{
	CObject::Initialize();
}

void CSpriteObject::Update()
{
	CObject::Update();
}

void CSpriteObject::LateUpdate()
{
	CObject::LateUpdate();
}

void CSpriteObject::Render(HDC _hDC) {
	CObject::Render(_hDC);

	// ��������Ʈ�� �����մϴ�.
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

void CSpriteObject::Release()
{
	CObject::Release();
}
