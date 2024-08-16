#include "pch.h"
#include "MiniMapWidget.h"

#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

#include "TilemapObject.h"
#include "Tilemap.h"
#include "SpriteUI.h"
#include "Scene.h"
using namespace std;

void CMiniMapWidget::Initialize()
{
	CWidget::Initialize();
	
	CSprite* pMiniMapSprite = CResourceManager::GetManager()->GetSprite(L"MiniMap00");

	m_pMiniMapSpriteUI = new CSpriteUI();
	m_pMiniMapSpriteUI->SetPosition({ 88.0f, 516.0f });
	m_pMiniMapSpriteUI->SetSize({ 160, 160 });
	m_pMiniMapSpriteUI->SetGdiRender(false);
	m_pMiniMapSpriteUI->SetSprite(pMiniMapSprite);
	InsertUI(m_pMiniMapSpriteUI);

	m_vecDynamicTiles = vector<vector<tagTileInfo>>(128, vector<tagTileInfo>(128, { ETileType::PASSABLE }));
}

void CMiniMapWidget::Update()
{
	CWidget::Update();
}

void CMiniMapWidget::LateUpdate()
{
	CWidget::LateUpdate();
}

void CMiniMapWidget::Render(HDC _hDC)
{
	CWidget::Render(_hDC);
	
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fSumRefreshDeltaSeconds += fDeltaSeconds;

	if (m_fSumRefreshDeltaSeconds >= 3.0f)
	{
		CTilemapObject* pDyTilemapObject = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		m_vecDynamicTiles = pDyTilemapObject->GetTilemap()->GetTiles();
		m_fSumRefreshDeltaSeconds = 0.0f;
	}

	
	Vector2 tMiniMapPosition = m_pMiniMapSpriteUI->GetPosition();
	// Vector2Int tMiniMapSize = m_pMiniMapSpriteUI->GetSize();

	for (uint32 y = 0; y < ITILEMAPCY; ++y)
	{
		for (uint32 x = 0; x < ITILEMAPCX; ++x)
		{
			float fX = tMiniMapPosition.m_fX - 76.0f + x * 1.25f;
			float fY = tMiniMapPosition.m_fY - 76.0f + y * 1.25f;

			if ((m_vecDynamicTiles[y][x].m_eTileType == ETileType::BUILDING)
				|| (m_vecDynamicTiles[y][x].m_eTileType == ETileType::UNIT))
			{
				if (m_vecDynamicTiles[y][x].m_eOwnerType == EOwnerType::PLAYER)
				{
					CGeometry::DrawRectangle(_hDC, { fX, fY }, { 4, 4 }, RGB(0, 255, 0));
				}
				else if (m_vecDynamicTiles[y][x].m_eOwnerType == EOwnerType::COMPUTER)
				{
					CGeometry::DrawRectangle(_hDC, { fX, fY }, { 4, 4 }, RGB(255, 0, 0));
				}
			}
		}
	}
}

void CMiniMapWidget::Release()
{
	CWidget::Release();
}
