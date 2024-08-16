#pragma once

class CTexture;
class CSprite;
class CAnimation;
class CTilemap;

class CResourceManager final
{
/***************
	메서드
***************/
private:
	CResourceManager() = default;

public:
	~CResourceManager() = default;
	CResourceManager(const CResourceManager& rhs) = delete;
	CResourceManager(CResourceManager&& rhs) = delete;
	CResourceManager& operator=(const CResourceManager& rhs) = delete;
	CResourceManager& operator=(CResourceManager&& rhs) = delete;

public:
	static CResourceManager* GetManager() {
		if (s_pResourceManager == nullptr)
		{
			s_pResourceManager = new CResourceManager();
		}
		return s_pResourceManager;
	}

public:
	void Initialize(HWND _hWnd, const std::wstring _strPath);
	void Release();

public:
	// 텍스처
	CTexture* GetTexture(const std::wstring& _strKey) { return m_umapTextures[_strKey]; }
	CTexture* LoadTexture(const std::wstring& _strKey, const std::wstring& _strPath, uint32 _uiTransparency = RGB(255, 0, 255));

	// 스프라이트
	CSprite* GetSprite(const std::wstring& _strKey) { return m_umapSprites[_strKey]; }
	CSprite* CreateSprite(const std::wstring& _strKey, CTexture* _pTexture, int32 _iX, int32 _iY, int32 _iWidth, int32 _iHeight);

	// 애니메이션
	CAnimation* GetAnimation(const std::wstring& _strKey) { return m_umapAnimations[_strKey]; }
	CAnimation* CreateAnimation(const std::wstring& _strKey, CTexture* _pTexture, std::wstring _strName, bool _bVertical, std::pair<int32, int32> _tXIndex, std::pair<int32, int32> _tYIndex, Vector2Int _tSize, float _fDuration, bool _bPlayOnce, bool _bRepeat);

	CTilemap* GetTilemap(const std::wstring& _strKey) { return m_umapTilemaps[_strKey]; }
	CTilemap* CreateTilemap(const std::wstring& _strKey);

	void SaveTilemap(const std::wstring& _strKey, const std::wstring& _strPath);
	CTilemap* LoadTilemap(const std::wstring& _strKey, const std::wstring& _strPath);

/***************
	데이터 멤버
***************/
public:
	static CResourceManager* s_pResourceManager;

private:
	// 윈도우 핸들
	HWND m_hWnd{};

	// 리소스 폴더 절대 경로
	std::wstring m_strPath = L"";

	// 텍스처 해시
	std::unordered_map<std::wstring, CTexture*> m_umapTextures;

	// 스프라이트 해시
	std::unordered_map<std::wstring, CSprite*> m_umapSprites;
	
	// 애니메이션 해시
	std::unordered_map<std::wstring, CAnimation*> m_umapAnimations;

	// 타일맵 해시
	std::unordered_map<std::wstring, CTilemap*> m_umapTilemaps;

	// TODO: 사운드 해시
};
