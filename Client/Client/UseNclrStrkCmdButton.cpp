#include "pch.h"
#include "UseNclrStrkCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "TerranObject.h"
#include "Scene.h"
#include "Cursor.h"

void CUseNclrStrkCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CUseNclrStrkCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::N))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::USE_NUCLEAR_STRIKE);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CUseNclrStrkCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CUseNclrStrkCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CUseNclrStrkCmdButton::Release()
{
	CCmdButton::Release();
}

void CUseNclrStrkCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::USE_NUCLEAR_STRIKE);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

void CUseNclrStrkCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::ARM_NUCLEAR_SILO) == false)
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
