#include "pch.h"
#include "UpInfWpnCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CUpInfWpnCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pInfWpnProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_1);
	pInfWpnProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_2);
	pInfWpnProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_WEAPONS_3);
}

void CUpInfWpnCmdButton::Update()
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
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_INFANTRY_WEAPONS);
	}
}

void CUpInfWpnCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpInfWpnCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpInfWpnCmdButton::Release()
{
	CCmdButton::Release();
}

void CUpInfWpnCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (!VerifyResource())
	{
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_INFANTRY_WEAPONS);
}

void CUpInfWpnCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_1) == false)
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

bool CUpInfWpnCmdButton::VerifyResource()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_1) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfWpnProperty[0]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfWpnProperty[0]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_2) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfWpnProperty[1]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfWpnProperty[1]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_WEAPONS_3) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfWpnProperty[2]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfWpnProperty[2]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	return true;
}
