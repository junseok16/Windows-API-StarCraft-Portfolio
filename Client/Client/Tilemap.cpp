#include "pch.h"
#include "Tilemap.h"
using namespace std;

void CTilemap::LoadFile(const std::wstring& _strPath)
{
	FILE* pFile = nullptr;
	::_wfopen_s(&pFile, _strPath.c_str(), L"rb");
	assert(pFile);

	// ������ �࿭ ũ�⸦ �����մϴ�.
	::fread(&m_tMapSize.m_iX, sizeof(m_tMapSize.m_iX), 1, pFile);
	::fread(&m_tMapSize.m_iY, sizeof(m_tMapSize.m_iY), 1, pFile);

	// �࿭ ũ�⸦ �������� ���Ϳ��� Ÿ�� Ÿ���� �ҷ��� ���Ͽ� �����մϴ�.
	for (int32 y = 0; y < m_tMapSize.m_iY; y++)
	{
		for (int32 x = 0; x < m_tMapSize.m_iX; x++)
		{
			ETileType eTileType = ETileType::ENUM_END;
			::fread(&eTileType, sizeof(eTileType), 1, pFile);
			m_vecTiles[y][x].m_eTileType = eTileType;
		}
	}

	::fclose(pFile);
	return;
}

void CTilemap::SaveFile(const std::wstring& _strPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strPath.c_str(), L"wb");
	assert(pFile != nullptr);

	// ������ �࿭ ũ�⸦ �ҷ��ɴϴ�.
	::fwrite(&m_tMapSize.m_iX, sizeof(m_tMapSize.m_iX), 1, pFile);
	::fwrite(&m_tMapSize.m_iY, sizeof(m_tMapSize.m_iY), 1, pFile);

	// �࿭ ũ�⸦ �������� ���Ͽ��� Ÿ�� Ÿ���� �ҷ��� ���Ϳ� �����մϴ�.
	for (int32 y = 0; y < m_tMapSize.m_iY; y++)
	{
		for (int32 x = 0; x < m_tMapSize.m_iX; x++)
		{
			ETileType eTileType = m_vecTiles[y][x].m_eTileType;
			::fwrite(&eTileType, sizeof(eTileType), 1, pFile);
		}
	}

	::fclose(pFile);
	return;
}

void CTilemap::SetMapSize(Vector2Int _tMapSize)
{
	m_tMapSize = _tMapSize;
	m_vecTiles = vector<vector<tagTileInfo>>(_tMapSize.m_iHeight, vector<tagTileInfo>(_tMapSize.m_iWidth, tagTileInfo{ ETileType::PASSABLE }));
}

void CTilemap::SetTileSize(Vector2Int _tTileSize)
{
	m_tTileSize = _tTileSize;
}

tagTileInfo CTilemap::GetTileAt(int32 _iX, int32 _iY)
{
	// Ÿ���� ������ ����� ���
	if (_iX < 0 || _iY < 0 || _iX >= m_tMapSize.m_iWidth || _iY >= m_tMapSize.m_iHeight)
	{
		return { ETileType::ENUM_END };
	}
	return m_vecTiles[_iY][_iX];
}

void CTilemap::SetTileAt(int32 _iX, int32 _iY, tagTileInfo _tTileInfo)
{
	// Ÿ���� ������ ����� ���
	if (_iX < 0 || _iY < 0 || _iX >= m_tMapSize.m_iWidth || _iY >= m_tMapSize.m_iHeight)
	{
		return;
	}
	m_vecTiles[_iY][_iX] = _tTileInfo;
}
