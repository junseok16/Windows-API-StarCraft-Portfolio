#include "pch.h"
#include "TilemapManager.h"
#include "Tilemap.h"

CTilemapManager* CTilemapManager::s_pTilemapManager = nullptr;

void CTilemapManager::Initialize()
{

}

void CTilemapManager::Update()
{

}

void CTilemapManager::LateUpdate()
{

}

void CTilemapManager::Render(HDC _hDC)
{

}

void CTilemapManager::Release()
{
	for (auto& tilemap : m_umapTilemaps)
	{
		if (tilemap.second != nullptr)
		{
			SAFE_DELETE(tilemap.second);
		}
	}
	m_umapTilemaps.clear();

	VERIFY_NULLPTR(s_pTilemapManager);
	SAFE_DELETE(s_pTilemapManager);
}

CTilemap* CTilemapManager::CreateTilemap(const std::wstring& _strKey)
{
	if (m_umapTilemaps.find(_strKey) != m_umapTilemaps.end())
	{
		return m_umapTilemaps[_strKey];
	}

	CTilemap* pTilemap = new CTilemap();
	m_umapTilemaps.insert({ _strKey, pTilemap });
	return pTilemap;
}

void CTilemapManager::SaveTilemap(const std::wstring& _strKey, const std::wstring& _strPath)
{

}

CTilemap* CTilemapManager::LoadTilemap(const std::wstring& _strKey, const std::wstring& _strPath)
{
	return nullptr;
}
