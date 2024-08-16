#include "pch.h"
#include "Animation.h"
#include "Texture.h"

HDC CAnimation::GetTextureDC() const
{
	return m_tAnimationInfo.m_pTexture->GetDC();
}

uint32 CAnimation::GetTextureAlpha() const
{
	return m_tAnimationInfo.m_pTexture->GetAlpha();
}
