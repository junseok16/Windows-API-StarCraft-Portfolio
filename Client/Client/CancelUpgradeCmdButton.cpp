#include "pch.h"
#include "CancelUpgradeCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CCancelUpgradeCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CCancelUpgradeCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::ESC))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->SendCommand(ECommandType::CANCEL_UPGRADE);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
}

void CCancelUpgradeCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CCancelUpgradeCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CCancelUpgradeCmdButton::Release()
{
	CCmdButton::Release();
}

void CCancelUpgradeCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->SendCommand(ECommandType::CANCEL_UPGRADE);
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
}
