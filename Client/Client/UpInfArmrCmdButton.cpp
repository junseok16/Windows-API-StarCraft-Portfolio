#include "pch.h"
#include "UpInfArmrCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"

#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CUpInfArmrCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pInfArmrProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_1);
	pInfArmrProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_2);
	pInfArmrProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::INFANTRY_ARMOR_3);
}

void CUpInfArmrCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::A))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		
		if (!VerifyResource())
		{
			return;
		}
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_INFANTRY_ARMOR);
	}
}

void CUpInfArmrCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpInfArmrCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpInfArmrCmdButton::Release()
{
	CCmdButton::Release();
}

void CUpInfArmrCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (!VerifyResource())
	{
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_INFANTRY_ARMOR);
}

void CUpInfArmrCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_1) == false)
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

bool CUpInfArmrCmdButton::VerifyResource()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_1) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfArmrProperty[0]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfArmrProperty[0]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_2) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfArmrProperty[1]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfArmrProperty[1]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::INFANTRY_ARMOR_3) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pInfArmrProperty[2]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pInfArmrProperty[2]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	return true;
}
