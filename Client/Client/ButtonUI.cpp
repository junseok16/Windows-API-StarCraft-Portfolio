#include "pch.h"
#include "ButtonUI.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "Sprite.h"

void CButtonUI::Initialize()
{
	CUI::Initialize();
}

void CButtonUI::Update()
{
	CUI::Update();
	if (!m_bUIActive) { return; }
	UpdateButtonState();
}

void CButtonUI::LateUpdate()
{
	CUI::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CButtonUI::Render(HDC _hDC)
{
	CUI::Render(_hDC);
	if (!m_bUIActive) { return; }

	if (m_pCurSprite != nullptr)
	{
		tagSpriteInfo tSpriteInfo = m_pCurSprite->GetSpriteInfo();

		Vector2Int tSize = tSpriteInfo.m_tSize;
		Vector2Int tPosition = tSpriteInfo.m_tPosition;
		uint32 uiAlpha = m_pCurSprite->GetTextureAlpha();

		if (m_bGdiRender == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurSprite->GetTextureDC(),
				tPosition.m_iX,
				tPosition.m_iY,
				SRCCOPY);
		}
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tPosition.m_fX - tSize.m_iX * 0.5f),
				(int32)(m_tPosition.m_fY - tSize.m_iY * 0.5f),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurSprite->GetTextureDC(),
				tPosition.m_iX,
				tPosition.m_iY,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
	else
	{
		CGeometry::DrawRectangle(_hDC, m_tPosition, m_tSize, RGB(0, 255, 0));
	}
}

void CButtonUI::Release()
{
	CUI::Release();
}

void CButtonUI::OnButtonClick() { }

void CButtonUI::SetButtonState(EButtonState _eButtonState)
{
	if (m_eButtonState == _eButtonState) { return; }

	m_eButtonState = _eButtonState;

	if (m_arrSprites[(int32)_eButtonState] != nullptr)
	{
		m_pCurSprite = m_arrSprites[(int32)_eButtonState];
	}
}

void CButtonUI::UpdateButtonState()
{
	if (m_eButtonState == EButtonState::DISABLE)
	{
		return;
	}

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();

	// 버튼 상태를 변경합니다.
	if (m_eButtonState == EButtonState::CLICK)
	{
		m_fSumDeltaSeconds += fDeltaSeconds;
		if (m_fSumDeltaSeconds >= 0.3f)
		{
			m_fSumDeltaSeconds = 0.0f;
			SetButtonState(EButtonState::RELEASE);
		}
		return;
	}

	if (IsCursorInRect() == true)
	{
		if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			SetButtonState(EButtonState::PRESS);
		}
		else
		{
			if (m_eButtonState == EButtonState::PRESS)
			{
				SetButtonState(EButtonState::CLICK);
				if (m_fpOnClick) { m_fpOnClick(); }
			}
			else
			{
				SetButtonState(EButtonState::HOVER);
			}
		}
	}
	else
	{
		SetButtonState(EButtonState::RELEASE);
	}
}
