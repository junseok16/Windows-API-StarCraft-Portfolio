#include "pch.h"
#include "AStarManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "TilemapObject.h"
#include "Tilemap.h"
#include "Heuristic.h"
using namespace std;

CAStarManager* CAStarManager::s_pAStarManager = nullptr;

void CAStarManager::Initialize()
{
	m_pHeuristic = new CHeuristic();
	VERIFY_NULLPTR(m_pHeuristic);
}

void CAStarManager::Release()
{
	SAFE_DELETE(m_pHeuristic);
	SAFE_DELETE(s_pAStarManager);
}

bool CAStarManager::FindOptimalPath(std::queue<Vector2Int>& _quePath, std::vector<Vector2Int>& _vecPath, Vector2Int tStart, Vector2Int tEnd)
{
	// ����, ���� Ÿ�ϸ��� �ҷ��ɴϴ�.
	CTilemapObject* pDyTilemapObject = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
	CTilemapObject* pStTilemapObject = CSceneManager::GetManager()->GetCurScene()->GetStaticTilemapObject();

	Vec2Map& vecDyTiles = pDyTilemapObject->GetTilemap()->GetTiles();
	Vec2Map& vecStTiles = pStTilemapObject->GetTilemap()->GetTiles();

	// �� �� ���� ������ �����մϴ�.
	Vec2Map vecComTiles = vector<vector<tagTileInfo>>(ITILEMAPCY, vector<tagTileInfo>(ITILEMAPCX, { ETileType::PASSABLE }));
	for (int32 y = 0; y < ITILEMAPCY; y++)
	{
		for (int32 x = 0; x < ITILEMAPCX; x++)
		{
			if (vecDyTiles[y][x].m_eTileType == ETileType::IMPASSABLE || vecStTiles[y][x].m_eTileType == ETileType::IMPASSABLE)
			{
				vecComTiles[y][x].m_eTileType = ETileType::IMPASSABLE;
			}
			else if (vecDyTiles[y][x].m_eTileType == ETileType::UNIT)
			{
				vecComTiles[y][x].m_eTileType = ETileType::UNIT;
			}
			else if (vecDyTiles[y][x].m_eTileType == ETileType::BUILDING)
			{
				vecComTiles[y][x].m_eTileType = ETileType::BUILDING;
			}
		}
	}

	// Vec2MapInfo mapInfo = m_file_class->GetVec2Map();
	Vec2MapInfo mapInfo{ vecComTiles, ITILEMAPCX, ITILEMAPCY, tStart.m_iX, tStart.m_iY, tEnd.m_iX, tEnd.m_iY };
	if (mapInfo.tMap.empty()) { return false; }

	
	// �� ������ �������� A* �˰����� �����Ѵ�.
	bool result = m_pHeuristic->BeginSearch(mapInfo);

	if (result)
	{
		_quePath = m_pHeuristic->GetQueOptimalPath();
		_vecPath = m_pHeuristic->GetVecOptimalPath();
		return true;
	}
	return false;
}
