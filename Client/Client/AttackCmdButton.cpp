#include "pch.h"
#include "AttackCmdButton.h"

#include "GameManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Cursor.h"
#include "TerranObject.h"

void CAttackCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CAttackCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }


	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::A))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::ATTACK);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CAttackCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CAttackCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CAttackCmdButton::Release()
{
	CCmdButton::Release();
}

void CAttackCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::ATTACK);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}
