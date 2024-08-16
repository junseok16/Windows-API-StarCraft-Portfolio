#include "pch.h"
#include "UpU238CmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CUpU238CmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pU238ShllProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::U238_SHELLS);
}

void CUpU238CmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::U))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		if (CGameManager::GetManager()->GetProducedMineral() < pU238ShllProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pU238ShllProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_U238_SHELLS);
	}
}

void CUpU238CmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpU238CmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpU238CmdButton::Release()
{
	CCmdButton::Release();
}

void CUpU238CmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (CGameManager::GetManager()->GetProducedMineral() < pU238ShllProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pU238ShllProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_U238_SHELLS);
}
