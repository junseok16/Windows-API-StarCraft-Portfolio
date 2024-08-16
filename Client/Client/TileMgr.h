#pragma once

class CTileManager final
{
private:
	CTileManager();
	~CTileManager();

public:
	void	Initialize();
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

	void	Picking(POINT pt, int _iDrawID, int _iOption);

	void	SaveTile();
	void	LoadTile();

public:
	static CTileManager*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileManager;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTileManager* m_pInstance;
	std::vector<CObject*> m_vecTile;
};

