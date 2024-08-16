#include "pch.h"
#include "TnkMdCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"
using namespace std;

void CTnkMdCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CTnkMdCmdButton::Update() {
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	// VerifyTechTree();// 테크 트리를 확인합니다.
	
	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::O))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		CGameManager::GetManager()->SendCommand(ECommandType::TANK_MODE);
	}
}

void CTnkMdCmdButton::LateUpdate() {
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CTnkMdCmdButton::Render(HDC _hDC) {
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CTnkMdCmdButton::Release() {
	CCmdButton::Release();

}

void CTnkMdCmdButton::OnButtonClick() {
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	CGameManager::GetManager()->SendCommand(ECommandType::TANK_MODE);
}

void CTnkMdCmdButton::VerifyTechTree() {
	std::array<bool, (int32)ETerranUpgradeType::ENUM_END>& arrUpgrades = CGameManager::GetManager()->GetUpgrades();

	if (arrUpgrades[(int32)ETerranUpgradeType::SIEGE_TECH] == false)
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
