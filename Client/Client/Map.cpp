#include "pch.h"
#include "Map.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Sprite.h"

void CMapUI::Initialize()
{
	CSpriteUI::Initialize();

	CSprite* pMapSprite = CResourceManager::GetManager()->GetSprite(L"FightingSpirit");

	// Object �Ӽ��� �ʱ�ȭ�մϴ�.
	SetUIType(EUIType::DYNAMIC_UI);
	SetPosition({ 2048.0f, 2048.0f });
	SetSize({ 4096, 4096 });
	SetGdiRender(false);

	// SpriteObject �Ӽ��� �ʱ�ȭ�մϴ�.
	SetSprite(pMapSprite);
}

void CMapUI::Update()
{
	CSpriteUI::Update();
}

void CMapUI::LateUpdate()
{
	CSpriteUI::LateUpdate();
}

void CMapUI::Render(HDC _hDC)
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

void CMapUI::Release()
{
	CSpriteUI::Release();
}
