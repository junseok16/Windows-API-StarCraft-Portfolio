#include "pch.h"
#include "UseStmPackCmdButton.h"

#include "GameManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
using namespace std;

void CUseStmPackCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CUseStmPackCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::T))
	{
		CGameManager::GetManager()->SendCommand(ECommandType::USE_STIMPACK);
	}
}

void CUseStmPackCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CUseStmPackCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CUseStmPackCmdButton::Release()
{
	CCmdButton::Release();

}

void CUseStmPackCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CGameManager::GetManager()->SendCommand(ECommandType::USE_STIMPACK);
}

void CUseStmPackCmdButton::VerifyTechTree()
{
	std::array<bool, (int32)ETerranUpgradeType::ENUM_END>& arrUpgrades = CGameManager::GetManager()->GetUpgrades();

	if (arrUpgrades[(int32)ETerranUpgradeType::STIMPACK_TECH] == false)
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
