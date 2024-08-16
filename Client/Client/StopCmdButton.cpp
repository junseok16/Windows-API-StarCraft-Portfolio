#include "pch.h"
#include "StopCmdButton.h"

#include "GameManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"

void CStopCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CStopCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::S))
	{
		SetButtonState(EButtonState::CLICK);
		// CScene::s_pPlayer->SendCommand(ECommandType::STOP);
		CGameManager::GetManager()->SendCommand(ECommandType::STOP);
	}
}

void CStopCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CStopCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CStopCmdButton::Release()
{
	CCmdButton::Release();

}

void CStopCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	SetButtonState(EButtonState::CLICK);
	//CScene::s_pPlayer->SendCommand(ECommandType::STOP);
	CGameManager::GetManager()->SendCommand(ECommandType::STOP);
}
