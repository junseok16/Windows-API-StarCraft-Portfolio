#include "pch.h"
#include "UpVhclWpnCmdButton.h"

#include "PropertyManager.h"
#include "GameManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "TerranObject.h"
#include "UpgradeProperty.h"

void CUpVhclWpnCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pVhclWpnProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_1);
	pVhclWpnProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_2);
	pVhclWpnProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_WEAPONS_3);
}

void CUpVhclWpnCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::W))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		if (!VerifyResource())
		{
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_VIHICLE_WEAPONS);
	}
}

void CUpVhclWpnCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpVhclWpnCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpVhclWpnCmdButton::Release()
{
	CCmdButton::Release();
}

void CUpVhclWpnCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();
	
	if (!VerifyResource())
	{
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_VIHICLE_WEAPONS);
}

void CUpVhclWpnCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_1) == false)
	{
		if (GetButtonState() != EButtonState::DISABLE)
		{
			return;
		}
		SetButtonState(EButtonState::RELEASE);
	}
	else
	{
		if (CGameManager::GetManager()->IsThereBuilding(ETerranBuildingType::SCIENCE_FACILITY) == false)
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
}

bool CUpVhclWpnCmdButton::VerifyResource()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_1) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclWpnProperty[0]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclWpnProperty[0]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_2) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclWpnProperty[1]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclWpnProperty[1]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_WEAPONS_3) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclWpnProperty[2]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclWpnProperty[2]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	return true;
}
