#include "pch.h"
#include "Heuristic.h"

bool CHeuristic::BeginSearch(Vec2MapInfo& _tMapInfo)
{
	// ������� �������� ���� ���
	if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, _tMapInfo.iStartX, _tMapInfo.iStartY)) { return true; }

	// ������� �������� �迭�� ����, �� ���� ������ ����� ���
	if (!IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, _tMapInfo.iStartX, _tMapInfo.iStartY) ||
		!IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, _tMapInfo.iDestX, _tMapInfo.iDestY)) { return false; }

	// ������� �������� ������ ���
	// || !IsPassableNode(mapInfo.map, mapInfo.start_x, mapInfo.start_y)
	if (!IsUnitNPassableNode(_tMapInfo.tMap, _tMapInfo.iDestX, _tMapInfo.iDestY)) { return false; }

	// ������� �ҷ��ɴϴ�.
	int32 iStartX = _tMapInfo.iStartX;
	int32 iStartY = _tMapInfo.iStartY;

	// ��� ����� ����� �������� �ʱ�ȭ�ϰ� �θ� -1�� �ʱ�ȭ�մϴ�.
	std::vector<std::vector<CellDetails>> vecCells(_tMapInfo.iMapRow, std::vector<CellDetails>(_tMapInfo.iMapCol));
	for (int32 iY = 0; iY < _tMapInfo.iMapRow; ++iY)
	{
		for (int32 iX = 0; iX< _tMapInfo.iMapCol; ++iX)
		{
			vecCells[iY][iX].f = vecCells[iY][iX].g = vecCells[iY][iX].h = INF;
			vecCells[iY][iX].iParentX = vecCells[iY][iX].iParentY = -1;
		}
	}

	// ����� ����� ����� 0���� �ʱ�ȭ�ϰ� �θ� �ڱ� �ڽ����� �ʱ�ȭ�մϴ�.
	vecCells[iStartY][iStartX].f = vecCells[iStartY][iStartX].g = vecCells[iStartY][iStartX].h = 0;
	vecCells[iStartY][iStartX].iParentX = iStartX;
	vecCells[iStartY][iStartX].iParentY = iStartY;

	// ���� ����� ����ϴ�.
	std::vector<std::vector<bool>> vecClosedList(_tMapInfo.iMapRow, std::vector<bool>(_tMapInfo.iMapCol));

	CostCoord tVertex;
	tVertex.iCost = 0;
	tVertex.iX = iStartX;
	tVertex.iY = iStartY;

	// ���� ����� ����ϴ�. greater �Լ� ��ü�� ��� ������ �����մϴ�.
	std::priority_queue<CostCoord, std::vector<CostCoord>, greater> pqOpenList;
	pqOpenList.push(tVertex);

	while (!pqOpenList.empty())
	{
		// ���� ��Ͽ��� ����� ���� ���� ��带 ���ϰ�, ���� ��Ͽ��� ���۴ϴ�.
		CostCoord tCurCoord = pqOpenList.top();
		pqOpenList.pop();

		int32 iCurX = tCurCoord.iX;
		int32 iCurY = tCurCoord.iY;

		// ����� ���� ���� ��带 ���� ��Ͽ� �����մϴ�.
		vecClosedList[iCurY][iCurX] = true;

		int32 nf, ng, nh;

		// �����¿츦 Ž���մϴ�.
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			// ���� ����� ��ǥ�� ���մϴ�.
			int32 iPostX = iCurX + m_dx1[iIndex];
			int32 iPostY = iCurY + m_dy1[iIndex];

			// ���� ��尡 �迭�� ���� �ȿ� �ִ� ���,
			if (IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, iPostX, iPostY))
			{
				// ���� ��尡 �������� ���
				if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, iPostX, iPostY))
				{
					vecCells[iPostY][iPostX].iParentX = iCurX;
					vecCells[iPostY][iPostX].iParentY = iCurY;

					// ������ ��θ� �����մϴ�.
					TraceMinimumPath(vecCells, { _tMapInfo.iDestX, _tMapInfo.iDestY });
					return true;
				}

				// ���� ��尡 ���� ��Ͽ� ���� ���� �ƴ� ���, �� �湮�� ���� ���� �� �� �ִ� ���� ���
				else if (!vecClosedList[iPostY][iPostX] && IsPassableNode(_tMapInfo.tMap, iPostX, iPostY))
				{
					// ����� ���մϴ�.
					ng = vecCells[iCurY][iCurX].g + 10;

					// ���� ��忡�� ������������ ����Դϴ�.
					nh = 10 * (std::abs(iPostX - _tMapInfo.iDestX) + std::abs(iPostY - _tMapInfo.iDestY));
					nf = ng + nh;

					// ������ F�� ������Ʈ���� �ʾҴ� ���ų�, ������Ʈ�� ��庸�� F�� �� ���� ���
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

						// ���� ��Ͽ� �����մϴ�.
						pqOpenList.push(tVertex);
					}
				}
			}
		}


		// �밢���� Ž���մϴ�.
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			// ���� ����� ��ǥ�� ���մϴ�.
			int32 iPostX = iCurX + m_dx2[iIndex];
			int32 iPostY = iCurY + m_dy2[iIndex];

			// ���� ��尡 �迭�� ���� �ȿ� �ִ� ���,
			if (IsInGround(_tMapInfo.iMapCol, _tMapInfo.iMapRow, iPostX, iPostY))
			{
				if (IsCrossDiagonal(_tMapInfo.tMap, iCurX, iCurY, iPostX, iPostY)) { continue; }

				if (IsCrossCorner(_tMapInfo.tMap, iCurX, iCurY, iPostX, iPostY)) { continue; }
				
				// ���� ��尡 �������� ���
				if (IsDestinationNode(_tMapInfo.iDestX, _tMapInfo.iDestY, iPostX, iPostY))
				{
					vecCells[iPostY][iPostX].iParentX = iCurX;
					vecCells[iPostY][iPostX].iParentY = iCurY;

					// ������ ��θ� �����մϴ�.
					TraceMinimumPath(vecCells, { _tMapInfo.iDestX, _tMapInfo.iDestY });
					return true;
				}

				// ���� ��尡 ���� ��Ͽ� ���� ���� �ƴ� ���, �� �湮�� ���� ���� �� �� �ִ� ���� ���
				else if (!vecClosedList[iPostY][iPostX] && IsPassableNode(_tMapInfo.tMap, iPostX, iPostY))
				{
					// ����� ���մϴ�.
					ng = vecCells[iCurY][iCurX].g + 14;
					nh = 10 * (std::abs(iPostX - _tMapInfo.iDestX) + std::abs(iPostY - _tMapInfo.iDestY));
					nf = ng + nh;

					// ������ F�� ������Ʈ���� �ʾҴ� ���ų�, ������Ʈ�� ��庸�� F�� �� ���� ���
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

						// ���� ��Ͽ� �����մϴ�.
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

	// ���������� ��������� �θ� ��带 �����մϴ�.
	while (!(_vecCells[iCurY][iCurX].iParentX == iCurX && _vecCells[iCurY][iCurX].iParentY == iCurY))
	{
		int32 iTempX = _vecCells[iCurY][iCurX].iParentX;
		int32 iTempY = _vecCells[iCurY][iCurX].iParentY;

		iCurX = iTempX;
		iCurY = iTempY;

		stkTracking.push({ iCurX, iCurY });
	}

	// ��������� ���������� ť�� �����մϴ�.
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