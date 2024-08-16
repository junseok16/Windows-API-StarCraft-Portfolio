#pragma once

class CHeuristic
{
private:
	// ����� ���� �� ����� �Լ� ��ü
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

	// *** �߰� ���� ***
	bool IsCrossDiagonal(Vec2Map&, int32, int32, int32, int32);
	bool IsCrossCorner(Vec2Map&, int32, int32, int32, int32);

private:
	// �����¿�
	const int32 m_dx1[4] = { 0, 0, 1, -1 };
	const int32 m_dy1[4] = { -1, 1, 0, 0 };

	// �밢��
	const int32 m_dx2[4] = { 1, -1, -1, 1 };
	const int32 m_dy2[4] = { -1, 1, -1, 1 };

	// ������ ���
	std::queue<Vector2Int> m_queOptimalPath;
	std::vector<Vector2Int> m_vecOptimalPath;
};

