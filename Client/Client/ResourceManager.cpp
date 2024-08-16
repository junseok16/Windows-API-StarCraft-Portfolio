#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Tilemap.h"
using namespace std;

CResourceManager* CResourceManager::s_pResourceManager = nullptr;

void CResourceManager::Initialize(HWND _hWnd, const std::wstring _strPath)
{
	m_hWnd = _hWnd;
	m_strPath = _strPath;
}

void CResourceManager::Release()
{
	for (auto& texture : m_umapTextures)
	{
		if (texture.second != nullptr)
		{
			SAFE_DELETE(texture.second);
		}
	}
	m_umapTextures.clear();

	for (auto& sprite : m_umapSprites)
	{
		if (sprite.second != nullptr)
		{
			SAFE_DELETE(sprite.second);
		}
	}
	m_umapSprites.clear();

	for (auto& animation : m_umapAnimations)
	{
		if (animation.second != nullptr)
		{
			SAFE_DELETE(animation.second);
		}
	}
	m_umapAnimations.clear();
	
	for (auto& tilemap : m_umapTilemaps)
	{
		if (tilemap.second != nullptr)
		{
			SAFE_DELETE(tilemap.second);
		}
	}
	m_umapTilemaps.clear();

	VERIFY_NULLPTR(s_pResourceManager);
	SAFE_DELETE(s_pResourceManager);
}

CTexture* CResourceManager::LoadTexture(const std::wstring& _strKey, const wstring& _strPath, uint32 _uiTransparency)
{
	const wstring strFullPath = m_strPath + _strPath;

	if (m_umapTextures.find(_strKey) != m_umapTextures.end())
	{
		return m_umapTextures[_strKey];
	}

	// 새로운 텍스처를 생성합니다.
	CTexture* pTexture = new CTexture();
	pTexture->LoadBMP(m_hWnd, strFullPath);
	pTexture->SetTransparency(_uiTransparency);

	m_umapTextures.insert({ _strKey, pTexture });
	return pTexture;
}

CSprite* CResourceManager::CreateSprite(const std::wstring& _strKey, CTexture* _pTexture, int32 _iX, int32 _iY, int32 _iWidth, int32 _iHeight)
{
	if (m_umapSprites.find(_strKey) != m_umapSprites.end())
	{
		return m_umapSprites[_strKey];
	}

	CSprite* pSprite = new CSprite();
	pSprite->SetSpriteInfo({ _pTexture, { _iX, _iY }, { _iWidth, _iHeight } });
	m_umapSprites.insert({ _strKey, pSprite });
	return pSprite;
}

CAnimation* CResourceManager::CreateAnimation(const std::wstring& _strKey, CTexture* _pTexture, std::wstring _strName, bool _bVertical, std::pair<int32, int32> _tXIndex, std::pair<int32, int32> _tYIndex, Vector2Int _tSize, float _fDuration, bool _bPlayOnce, bool _bRepeat)
{
	if (m_umapAnimations.find(_strKey) != m_umapAnimations.end())
	{
		return m_umapAnimations[_strKey];
	}

	CAnimation* pAnimation = new CAnimation();
	pAnimation->SetAnimationInfo({ _pTexture, _strName, _bVertical, _tXIndex, _tYIndex, _tSize, _fDuration, _bPlayOnce, _bRepeat });
	m_umapAnimations.insert({ _strKey, pAnimation });
	return pAnimation;
}


CTilemap* CResourceManager::CreateTilemap(const wstring& _strKey)
{
	if (m_umapTilemaps.find(_strKey) != m_umapTilemaps.end())
	{
		return m_umapTilemaps[_strKey];
	}
	
	CTilemap* pTilemap = new CTilemap();
	m_umapTilemaps.insert({ _strKey, pTilemap });
	return pTilemap;
}

void CResourceManager::SaveTilemap(const wstring& _strKey, const wstring& _strPath)
{
	CTilemap* pTilemap = GetTilemap(_strKey);

	const wstring strFullPath = m_strPath + _strPath;
	pTilemap->SaveFile(strFullPath);
}

CTilemap* CResourceManager::LoadTilemap(const wstring& _strKey, const wstring& _strPath)
{
	CTilemap* pTilemap = nullptr;

	// 타일맵 파일이 없는 경우
	if (m_umapTilemaps.find(_strKey) == m_umapTilemaps.end())
	{
		m_umapTilemaps.insert({ _strKey, new CTilemap() });
	}
	pTilemap = m_umapTilemaps[_strKey];

	const wstring strFullPath = m_strPath + _strPath;
	pTilemap->LoadFile(strFullPath);
	return pTilemap;
}
