#include "pch.h"
#include "UpVhclPltngCmdButton.h"

#include "PropertyManager.h"
#include "GameManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "TerranObject.h"
#include "UpgradeProperty.h"

void CUpVhclPltngCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 520.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pVhclPltngProperty[0] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_1);
	pVhclPltngProperty[1] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_2);
	pVhclPltngProperty[2] = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::VIHICLE_PLATING_3);
}

void CUpVhclPltngCmdButton::Update()
{

	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::P))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		if (!VerifyResource())
		{
			return;
		}
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_VIHICLE_PLATING);
	}
}

void CUpVhclPltngCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpVhclPltngCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpVhclPltngCmdButton::Release()
{
	CCmdButton::Release();
}

void CUpVhclPltngCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (!VerifyResource())
	{
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_G);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_VIHICLE_PLATING);
}

void CUpVhclPltngCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_1) == false)
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

bool CUpVhclPltngCmdButton::VerifyResource()
{

	if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_1) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclPltngProperty[0]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclPltngProperty[0]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_2) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclPltngProperty[1]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclPltngProperty[1]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	else if (CGameManager::GetManager()->IsThereUpgrade(ETerranUpgradeType::VIHICLE_PLATING_3) == false)
	{
		if (CGameManager::GetManager()->GetProducedMineral() < pVhclPltngProperty[2]->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVhclPltngProperty[2]->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return false;
		}
	}
	return true;
}
