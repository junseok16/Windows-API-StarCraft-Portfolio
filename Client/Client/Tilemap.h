#pragma once
#include "ResourceEx.h"

class CTilemap : public CResourceEx
{
/***************
	메서드
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
	데이터 멤버
***************/
private:
	// 맵의 크기(128 * 128)
	Vector2Int m_tMapSize{ IWORLDCX / ITILECX, IWORLDCY / ITILECY };

	// 타일의 크기(32 x 32)
	Vector2Int m_tTileSize{ ITILECX, ITILECY };

	// 2차원 타일 벡터
	std::vector<std::vector<tagTileInfo>> m_vecTiles;
};

