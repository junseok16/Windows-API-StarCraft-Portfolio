#pragma once

class CHeuristic
{
private:
	// 비용을 비교할 때 사용할 함수 객체
	struct greater
	{
		constexpr bool operator()(const CostCoord& _Left, const CostCoord& _Right) const
		{
			return _Left.iCost > _Right.iCost;
		}
	};

public:
	CHeuristic() = default;
	CHeuristic(const CHeuristic&) = default;
	~CHeuristic() = default;

	bool BeginSearch(Vec2MapInfo&);
	std::queue<Vector2Int> GetQueOptimalPath();
	std::vector<Vector2Int> GetVecOptimalPath();

private:
	bool IsUnitNPassableNode(Vec2Map&, int32, int32);
	bool IsPassableNode(Vec2Map&, int32, int32);
	bool IsDestinationNode(int32, int32, int32, int32);
	bool IsInGround(int32, int32, int32, int32);
	void TraceMinimumPath(std::vector<std::vector<CellDetails>>, Coord);

	// *** 추가 사항 ***
	bool IsCrossDiagonal(Vec2Map&, int32, int32, int32, int32);
	bool IsCrossCorner(Vec2Map&, int32, int32, int32, int32);

private:
	// 상하좌우
	const int32 m_dx1[4] = { 0, 0, 1, -1 };
	const int32 m_dy1[4] = { -1, 1, 0, 0 };

	// 대각선
	const int32 m_dx2[4] = { 1, -1, -1, 1 };
	const int32 m_dy2[4] = { -1, 1, -1, 1 };

	// 최적의 경로
	std::queue<Vector2Int> m_queOptimalPath;
	std::vector<Vector2Int> m_vecOptimalPath;
};

