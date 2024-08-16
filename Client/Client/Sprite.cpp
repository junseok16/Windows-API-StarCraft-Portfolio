#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

HDC CSprite::GetTextureDC() const
{
	return m_tSpriteInfo.m_pTexture->GetDC();
}

uint32 CSprite::GetTextureAlpha() const
{
	return m_tSpriteInfo.m_pTexture->GetAlpha();
}
