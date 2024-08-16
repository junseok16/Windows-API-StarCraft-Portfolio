#include "pch.h"
#include "GoBackCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "SCV.h"

void CGoBackCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
} 

void CGoBackCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::ESC))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
}

void CGoBackCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CGoBackCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CGoBackCmdButton::Release()
{
	CCmdButton::Release();
}

void CGoBackCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
}
