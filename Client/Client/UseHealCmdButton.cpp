#include "pch.h"
#include "UseHealCmdButton.h"

#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
using namespace std;

void CUseHealCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CUseHealCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::H))
	{
		//CScene::s_pPlayer->SendCommand(ECommandType::HEAL);
	}
}

void CUseHealCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CUseHealCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CUseHealCmdButton::Release()
{
	CCmdButton::Release();
}

void CUseHealCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	//CScene::s_pPlayer->SendCommand(ECommandType::HEAL);
}
