#include "pch.h"
#include "ArmNukeCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "UpgradeProperty.h"
#include "TerranObject.h"

void CArmNukeCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pArmNukeProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::ARM_NUCLEAR_SILO);
}

void CArmNukeCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::N))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		if (CGameManager::GetManager()->GetProducedMineral() < pArmNukeProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pArmNukeProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		// 보급품이 부족한 경우
		if (CGameManager::GetManager()->GetConsumedSupply() + pArmNukeProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
		CGameManager::GetManager()->SendCommand(ECommandType::ARM_NUCLEAR_SILO);
	}
}

void CArmNukeCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CArmNukeCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CArmNukeCmdButton::Release()
{
	CCmdButton::Release();
}

void CArmNukeCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (CGameManager::GetManager()->GetProducedMineral() < pArmNukeProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pArmNukeProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	// 보급품이 부족한 경우
	if (CGameManager::GetManager()->GetConsumedSupply() + pArmNukeProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::ARM_NUCLEAR_SILO);
}

void CArmNukeCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::ARM_NUCLEAR_SILO) == true)
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
