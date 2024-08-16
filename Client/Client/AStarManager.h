#pragma once

class CHeuristic;

class CAStarManager final
{
private:
	CAStarManager() = default;

public:
	~CAStarManager() = default;
	CAStarManager(const CAStarManager& rhs) = delete;
	CAStarManager(CAStarManager&& rhs) = delete;
	CAStarManager& operator=(const CAStarManager& rhs) = delete;
	CAStarManager& operator=(CAStarManager&& rhs) = delete;

public:
	static CAStarManager* GetManager() {
		if (s_pAStarManager == nullptr)
		{
			s_pAStarManager = new CAStarManager();
		}
		return s_pAStarManager;
	}

public:
	void Initialize();
	void Release();

	bool FindOptimalPath(std::queue<Vector2Int>& _quePath, std::vector<Vector2Int>& _vecPath, Vector2Int tStart, Vector2Int tEnd);

/***************
	µ•¿Ã≈Õ ∏‚πˆ
***************/
public:
	static CAStarManager* s_pAStarManager;

private:
	CHeuristic* m_pHeuristic = nullptr;
	tagTileInfo m_tTileInfo;
};

