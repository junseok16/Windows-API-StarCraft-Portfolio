#pragma once

class CTilemap;

class CTilemapManager final
{
/***************
	메서드
***************/
private:
	CTilemapManager() = default;

public:
	~CTilemapManager() = default;
	CTilemapManager(const CTilemapManager& rhs) = delete;
	CTilemapManager(CTilemapManager&& rhs) = delete;
	CTilemapManager& operator=(const CTilemapManager& rhs) = delete;
	CTilemapManager& operator=(CTilemapManager&& rhs) = delete;

public:
	static CTilemapManager* GetManager() {
		if (s_pTilemapManager == nullptr)
		{
			s_pTilemapManager = new CTilemapManager();
		}
		return s_pTilemapManager;
	}

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

public:
	CTilemap* GetTilemap(const std::wstring& _strKey) { return m_umapTilemaps[_strKey]; }
	CTilemap* CreateTilemap(const std::wstring& _strKey);

	void SaveTilemap(const std::wstring& _strKey, const std::wstring& _strPath);
	CTilemap* LoadTilemap(const std::wstring& _strKey, const std::wstring& _strPath);

/***************
	데이터 멤버
***************/
public:
	static CTilemapManager* s_pTilemapManager;

private:
	// 윈도우 핸들
	HWND m_hWnd{};

	// 타일맵 해시
	std::unordered_map<std::wstring, CTilemap*> m_umapTilemaps;
};
