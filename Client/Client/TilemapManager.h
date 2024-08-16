#pragma once

class CTilemap;

class CTilemapManager final
{
/***************
	�޼���
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
	������ ���
***************/
public:
	static CTilemapManager* s_pTilemapManager;

private:
	// ������ �ڵ�
	HWND m_hWnd{};

	// Ÿ�ϸ� �ؽ�
	std::unordered_map<std::wstring, CTilemap*> m_umapTilemaps;
};
