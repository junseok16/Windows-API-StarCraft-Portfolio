#include "pch.h"
#include "Heuristic.h"

bool CHeuristic::BeginSearch(Vec2MapInfo& _tMapInfo)
{
	// 출발지와 도착지가 같은 경우
	if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, _tMapInfo.iStartX, _tMapInfo.iStartY)) { return true; }

	// 출발지나 도착지가 배열의 범위, 즉 맵의 범위를 벗어나는 경우
	if (!IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, _tMapInfo.iStartX, _tMapInfo.iStartY) ||
		!IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, _tMapInfo.iDestX, _tMapInfo.iDestY)) { return false; }

	// 출발지나 도착지가 절벽인 경우
	// || !IsPassableNode(mapInfo.map, mapInfo.start_x, mapInfo.start_y)
	if (!IsUnitNPassableNode(_tMapInfo.tMap, _tMapInfo.iDestX, _tMapInfo.iDestY)) { return false; }

	// 출발지를 불러옵니다.
	int32 iStartX = _tMapInfo.iStartX;
	int32 iStartY = _tMapInfo.iStartY;

	// 모든 노드의 비용을 무한으로 초기화하고 부모를 -1로 초기화합니다.
	std::vector<std::vector<CellDetails>> vecCells(_tMapInfo.iMapRow, std::vector<CellDetails>(_tMapInfo.iMapCol));
	for (int32 iY = 0; iY < _tMapInfo.iMapRow; ++iY)
	{
		for (int32 iX = 0; iX< _tMapInfo.iMapCol; ++iX)
		{
			vecCells[iY][iX].f = vecCells[iY][iX].g = vecCells[iY][iX].h = INF;
			vecCells[iY][iX].iParentX = vecCells[iY][iX].iParentY = -1;
		}
	}

	// 출발지 노드의 비용을 0으로 초기화하고 부모를 자기 자신으로 초기화합니다.
	vecCells[iStartY][iStartX].f = vecCells[iStartY][iStartX].g = vecCells[iStartY][iStartX].h = 0;
	vecCells[iStartY][iStartX].iParentX = iStartX;
	vecCells[iStartY][iStartX].iParentY = iStartY;

	// 닫힌 목록을 만듭니다.
	std::vector<std::vector<bool>> vecClosedList(_tMapInfo.iMapRow, std::vector<bool>(_tMapInfo.iMapCol));

	CostCoord tVertex;
	tVertex.iCost = 0;
	tVertex.iX = iStartX;
	tVertex.iY = iStartY;

	// 열린 목록을 만듭니다. greater 함수 객체로 비용 순으로 정렬합니다.
	std::priority_queue<CostCoord, std::vector<CostCoord>, greater> pqOpenList;
	pqOpenList.push(tVertex);

	while (!pqOpenList.empty())
	{
		// 열린 목록에서 비용이 가장 작은 노드를 구하고, 열린 목록에서 없앱니다.
		CostCoord tCurCoord = pqOpenList.top();
		pqOpenList.pop();

		int32 iCurX = tCurCoord.iX;
		int32 iCurY = tCurCoord.iY;

		// 비용이 가장 작은 노드를 닫힌 목록에 삽입합니다.
		vecClosedList[iCurY][iCurX] = true;

		int32 nf, ng, nh;

		// 상하좌우를 탐색합니다.
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			// 다음 노드의 좌표를 구합니다.
			int32 iPostX = iCurX + m_dx1[iIndex];
			int32 iPostY = iCurY + m_dy1[iIndex];

			// 다음 노드가 배열의 범위 안에 있는 경우,
			if (IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, iPostX, iPostY))
			{
				// 다음 노드가 도착지인 경우
				if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, iPostX, iPostY))
				{
					vecCells[iPostY][iPostX].iParentX = iCurX;
					vecCells[iPostY][iPostX].iParentY = iCurY;

					// 최적의 경로를 복원합니다.
					TraceMinimumPath(vecCells, { _tMapInfo.iDestX, _tMapInfo.iDestY });
					return true;
				}

				// 다음 노드가 닫힌 목록에 없고 벽이 아닌 경우, 즉 방문한 적이 없고 갈 수 있는 곳인 경우
				else if (!vecClosedList[iPostY][iPostX] && IsPassableNode(_tMapInfo.tMap, iPostX, iPostY))
				{
					// 비용을 구합니다.
					ng = vecCells[iCurY][iCurX].g + 10;

					// 다음 노드에서 도착지까지의 비용입니다.
					nh = 10 * (std::abs(iPostX - _tMapInfo.iDestX) + std::abs(iPostY - _tMapInfo.iDestY));
					nf = ng + nh;

					// 이전에 F가 업데이트되지 않았던 노드거나, 업데이트될 노드보다 F가 더 작은 경우
					if (vecCells[iPostY][iPostX].f == INF || vecCells[iPostY][iPostX].f > nf)
					{
						vecCells[iPostY][iPostX].g = ng;
						vecCells[iPostY][iPostX].h = nh;
						vecCells[iPostY][iPostX].f = nf;

						vecCells[iPostY][iPostX].iParentX = iCurX;
						vecCells[iPostY][iPostX].iParentY = iCurY;

						CostCoord tVertex;
						tVertex.iCost = nf;
						tVertex.iX = iPostX;
						tVertex.iY = iPostY;

						// 열린 목록에 삽입합니다.
						pqOpenList.push(tVertex);
					}
				}
			}
		}


		// 대각선을 탐색합니다.
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			// 다음 노드의 좌표를 구합니다.
			int32 iPostX = iCurX + m_dx2[iIndex];
			int32 iPostY = iCurY + m_dy2[iIndex];

			// 다음 노드가 배열의 범위 안에 있는 경우,
			if (IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, iPostX, iPostY))
			{
				if (IsCrossDiagonal(_tMapInfo.tMap, iCurX, iCurY, iPostX, iPostY)) { continue; }

				if (IsCrossCorner(_tMapInfo.tMap, iCurX, iCurY, iPostX, iPostY)) { continue; }
				
				// 다음 노드가 도착지인 경우
				if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, iPostX, iPostY))
				{
					vecCells[iPostY][iPostX].iParentX = iCurX;
					vecCells[iPostY][iPostX].iParentY = iCurY;

					// 최적의 경로를 복원합니다.
					TraceMinimumPath(vecCells, { _tMapInfo.iDestX, _tMapInfo.iDestY });
					return true;
				}

				// 다음 노드가 닫힌 목록에 없고 벽이 아닌 경우, 즉 방문한 적이 없고 갈 수 있는 곳인 경우
				else if (!vecClosedList[iPostY][iPostX] && IsPassableNode(_tMapInfo.tMap, iPostX, iPostY))
				{
					// 비용을 구합니다.
					ng = vecCells[iCurY][iCurX].g + 14;
					nh = 10 * (std::abs(iPostX - _tMapInfo.iDestX) + std::abs(iPostY - _tMapInfo.iDestY));
					nf = ng + nh;

					// 이전에 F가 업데이트되지 않았던 노드거나, 업데이트될 노드보다 F가 더 작은 경우
					if (vecCells[iPostY][iPostX].f == INF || vecCells[iPostY][iPostX].f > nf)
					{
						vecCells[iPostY][iPostX].g = ng;
						vecCells[iPostY][iPostX].h = nh;
						vecCells[iPostY][iPostX].f = nf;

						vecCells[iPostY][iPostX].iParentX = iCurX;
						vecCells[iPostY][iPostX].iParentY = iCurY;

						CostCoord bVertex;
						bVertex.iCost = nf;
						bVertex.iX = iPostX;
						bVertex.iY = iPostY;

						// 열린 목록에 삽입합니다.
						pqOpenList.push(bVertex);
					}
				}
			}
		}
	}

	return false;
}

void CHeuristic::TraceMinimumPath(std::vector<std::vector<CellDetails>> _vecCells, Coord _tDest)
{
	std::stack<Vector2Int> stkTracking;
	std::queue<Vector2Int> queTracking;
	std::vector<Vector2Int> vecTracking;
	
	int32 iCurX = _tDest.iX;
	int32 iCurY = _tDest.iY;
	stkTracking.push({ iCurX, iCurY });

	// 도착지부터 출발지까지 부모 노드를 복원합니다.
	while (!(_vecCells[iCurY][iCurX].iParentX == iCurX && _vecCells[iCurY][iCurX].iParentY == iCurY))
	{
		int32 iTempX = _vecCells[iCurY][iCurX].iParentX;
		int32 iTempY = _vecCells[iCurY][iCurX].iParentY;

		iCurX = iTempX;
		iCurY = iTempY;

		stkTracking.push({ iCurX, iCurY });
	}

	// 출발지부터 도착지까지 큐에 저장합니다.
	while (!stkTracking.empty())
	{
		queTracking.push(stkTracking.top());
		vecTracking.push_back(stkTracking.top());
		stkTracking.pop();
	}

	m_queOptimalPath = queTracking;
	m_vecOptimalPath = vecTracking;
	return;
}

bool CHeuristic::IsCrossDiagonal(Vec2Map& _tMap, int32 _iCurX, int32 _iCurY, int32 _iPostX, int32 _iPostY)
{
	return ((_tMap[_iPostY][_iCurX].m_eTileType == ETileType::IMPASSABLE) && (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::IMPASSABLE))
		|| ((_tMap[_iPostY][_iCurX].m_eTileType == ETileType::BUILDING) && (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::BUILDING))
		|| ((_tMap[_iPostY][_iCurX].m_eTileType == ETileType::UNIT) && (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::UNIT));
}

bool CHeuristic::IsCrossCorner(Vec2Map& _tMap, int32 _iCurX, int32 _iCurY, int32 _iPostX, int32 _iPostY)
{
	return (_tMap[_iPostY][_iCurX].m_eTileType == ETileType::UNIT) || (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::UNIT)
		|| (_tMap[_iPostY][_iCurX].m_eTileType == ETileType::BUILDING) || (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::BUILDING)
		|| (_tMap[_iPostY][_iCurX].m_eTileType == ETileType::IMPASSABLE) || (_tMap[_iCurY][_iPostX].m_eTileType == ETileType::IMPASSABLE);
}

std::queue<Vector2Int> CHeuristic::GetQueOptimalPath()
{
	return m_queOptimalPath;
}

std::vector<Vector2Int> CHeuristic::GetVecOptimalPath()
{
	return m_vecOptimalPath;
}

bool CHeuristic::IsUnitNPassableNode(Vec2Map& _tMap, int32 _iCurX, int32 _iCurY)
{
	return (_tMap[_iCurY][_iCurX].m_eTileType == ETileType::PASSABLE)
		|| (_tMap[_iCurY][_iCurX].m_eTileType == ETileType::UNIT)
		|| (_tMap[_iCurY][_iCurX].m_eTileType == ETileType::BUILDING)
		|| (_tMap[_iCurY][_iCurX].m_eTileType == ETileType::MINERAL);
}

bool CHeuristic::IsPassableNode(Vec2Map& _tMap, int32 iCurX, int32 iCurY)
{
	return (_tMap[iCurY][iCurX].m_eTileType == ETileType::PASSABLE);
}

bool CHeuristic::IsDestinationNode(int32 _iDestX, int32 _iDestY, int32 _iCurX, int32 _iCurY)
{
	return ((_iDestX == _iCurX) && (_iDestY == _iCurY));
}

bool CHeuristic::IsInGround(int32 _iMapCol, int32 _iMapRow, int32 _iCurX, int32 _iCurY)
{
	return (((0 <= _iCurX) && (_iCurX < _iMapCol)) && ((0 <= _iCurY) && (_iCurY < _iMapRow)));
}