#include "pch.h"
#include "TilemapObject.h"
#include "Tilemap.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "Sprite.h"
#include "Scene.h"
#include "Tilemap.h"
using namespace std;

void CTilemapObject::Initialize()
{
	CObject::Initialize();
}

void CTilemapObject::Update()
{
	CObject::Update();

	// 타일을 선택합니다.
	// PickTile();
}

void CTilemapObject::LateUpdate()
{
	CObject::LateUpdate();
}

void CTilemapObject::Render(HDC _hDC)
{
	CObject::Render(_hDC);

	VERIFY_NULLPTR(m_pTilemap);
	if (m_bDebug == false) { return; }

	const Vector2Int tMapSize = m_pTilemap->GetMapSize();
	vector<vector<tagTileInfo>>& vecTiles = m_pTilemap->GetTiles();

	// 타일을 불러옵니다.
	CSprite* pPassable = CResourceManager::GetManager()->GetSprite(L"PassableTile");
	CSprite* pImpassable = CResourceManager::GetManager()->GetSprite(L"ImpassableTile");
	Vector2Int tSize = pPassable->GetSpriteInfo().m_tSize;

	// 스크롤된 위치를 불러옵니다.
	CScene* pScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pScene->GetCameraPosition();

	// 스크롤된 위치의 상하좌우를 구합니다.
	float fMinX =tCameraPosition.m_fX - FWINCX * 0.5f;
	float fMaxX =tCameraPosition.m_fX + FWINCX * 0.5f;
	float fMinY =tCameraPosition.m_fY - FWINCY * 0.5f;
	float fMaxY =tCameraPosition.m_fY + FWINCY * 0.5f;

	// 상하좌우의 최소 인덱스와 최대 인덱스를 구합니다.
	int32 iCullMinX = (int32)(fMinX - m_tPosition.m_fX) / ITILECX;
	int32 iCullMaxX = (int32)(fMaxX - m_tPosition.m_fX) / ITILECX;
	int32 iCullMinY = (int32)(fMinY - m_tPosition.m_fY) / ITILECY;
	int32 iCullMaxY = (int32)(fMaxY - m_tPosition.m_fY) / ITILECY;

	for (int32 iY = iCullMinY; iY <= iCullMaxY; ++iY)
	{
		for (int32 iX = iCullMinX; iX <= iCullMaxX; ++iX)
		{
			if (iX < 0 || iX >= tMapSize.m_iX) { continue; }
			if (iY < 0 || iY >= tMapSize.m_iY) { continue; }

			switch (vecTiles[iY][iX].m_eTileType)
			{
				// 갈 수 있는 타일을 렌더합니다.
			case ETileType::PASSABLE:
				::GdiTransparentBlt(_hDC,
					(int32)m_tPosition.m_fX + iX * ITILECX - (int32)(tCameraPosition.m_fX - FWINCX * 0.5f),
					(int32)m_tPosition.m_fY + iY * ITILECY - (int32)(tCameraPosition.m_fY - FWINCY * 0.5f),
					ITILECX,
					ITILECY,
					pPassable->GetTextureDC(),
					pPassable->GetSpriteInfo().m_tPosition.m_iX,
					pPassable->GetSpriteInfo().m_tPosition.m_iY,
					ITILECX,
					ITILECY,
					pPassable->GetTextureAlpha());
				break;

				// 갈 수 없는 타일을 렌더합니다.
			case ETileType::IMPASSABLE:
			// case ETileType::UNIT:
			case ETileType::BUILDING:
				::GdiTransparentBlt(_hDC,
					(int32)m_tPosition.m_fX + iX * ITILECX - (int32)(tCameraPosition.m_fX - FWINCX * 0.5f),
					(int32)m_tPosition.m_fY + iY * ITILECY - (int32)(tCameraPosition.m_fY - FWINCY * 0.5f),
					ITILECX,
					ITILECY,
					pImpassable->GetTextureDC(),
					pImpassable->GetSpriteInfo().m_tPosition.m_iX,
					pImpassable->GetSpriteInfo().m_tPosition.m_iY,
					ITILECX,
					ITILECY,
					pImpassable->GetTextureAlpha());
				break;
			}
		}
	}
}

void CTilemapObject::Release()
{
	CObject::Release();
}

void CTilemapObject::PickTile()
{
	Vector2 tScrollPosition = CSceneManager::GetManager()->GetCurScene()->GetCameraPosition();
	Vector2 tMousePosition = CMouseManager::GetManager()->GetMousePosition();

	int32 iScrollX = (int32)(tScrollPosition.m_fX - FWINCX * 0.5f);
	int32 iScrollY = (int32)(tScrollPosition.m_fY - FWINCY * 0.5f);

	int32 iWorldPositionX = (int32)tMousePosition.m_fX + iScrollX;
	int32 iWorldPositionY = (int32)tMousePosition.m_fY + iScrollY;

	int32 iTileX = iWorldPositionX / ITILECX;
	int32 iTileY = iWorldPositionY / ITILECY;

	if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::ONE))
	{
		m_pTilemap->SetTileAt(iTileX, iTileY, { ETileType::IMPASSABLE });
	}

	if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::ZERO))
	{
		m_pTilemap->SetTileAt(iTileX, iTileY, { ETileType::PASSABLE });
	}
}
