#pragma once
#include "ResourceEx.h"

class CTilemap : public CResourceEx
{
/***************
	�޼���
***************/
public:
	CTilemap() = default;
	virtual ~CTilemap() = default;

public:
	virtual void LoadFile(const std::wstring& _strPath) override;
	virtual void SaveFile(const std::wstring& _strPath) override;

public:
	Vector2Int GetMapSize() const { return m_tMapSize; }
	void SetMapSize(Vector2Int _tMapSize);

	Vector2Int GetTileSize() const { return m_tTileSize; }
	void SetTileSize(Vector2Int _tTileSize);

	tagTileInfo GetTileAt(int32 _iX, int32 _iY);
	void SetTileAt(int32 _iX, int32 _iY, tagTileInfo _tTileInfo);
	
	std::vector<std::vector<tagTileInfo>>& GetTiles() { return m_vecTiles; }


/***************
	������ ���
***************/
private:
	// ���� ũ��(128 * 128)
	Vector2Int m_tMapSize{ IWORLDCX / ITILECX, IWORLDCY / ITILECY };

	// Ÿ���� ũ��(32 x 32)
	Vector2Int m_tTileSize{ ITILECX, ITILECY };

	// 2���� Ÿ�� ����
	std::vector<std::vector<tagTileInfo>> m_vecTiles;
};

