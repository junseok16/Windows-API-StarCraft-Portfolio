#include "pch.h"
#include "UseIrdtCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "TerranObject.h"
#include "Scene.h"
#include "Cursor.h"

void CUseIrdtCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CUseIrdtCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::I))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::USE_IRRADIATE);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CUseIrdtCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CUseIrdtCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CUseIrdtCmdButton::Release()
{
	CCmdButton::Release();
}

void CUseIrdtCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::USE_IRRADIATE);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

void CUseIrdtCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::IRRADIATE) == false)
	{
		SetButtonState(EButtonState::DISABLE);
	}
	else
	{
		if (GetButtonState() != EButtonState::DISABLE)
		{
			return;
		}
		SetButtonState(EButtonState::RELEASE);
	}
}
