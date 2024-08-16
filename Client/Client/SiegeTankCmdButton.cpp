#include "pch.h"
#include "SiegeTankCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "UnitProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CSiegeTankCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CSiegeTankCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }
	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::T))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		// 자원이 부족한 경우
		CUnitProperty* pTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
		if (CGameManager::GetManager()->GetProducedMineral() < pTankProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pTankProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		// 보급품이 부족한 경우
		if (CGameManager::GetManager()->GetConsumedSupply() + pTankProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		CGameManager::GetManager()->SendCommand(ECommandType::BUILD_SIEGE_TANK);
	}
}

void CSiegeTankCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CSiegeTankCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CSiegeTankCmdButton::Release()
{
	CCmdButton::Release();
}

void CSiegeTankCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	// 자원이 부족한 경우
	CUnitProperty* pTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
	if (CGameManager::GetManager()->GetProducedMineral() < pTankProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pTankProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	// 보급품이 부족한 경우
	if (CGameManager::GetManager()->GetConsumedSupply() + pTankProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	CGameManager::GetManager()->SendCommand(ECommandType::BUILD_SIEGE_TANK);
}

void CSiegeTankCmdButton::VerifyTechTree()
{
	if (CGameManager::GetManager()->IsThereBuilding(ETerranBuildingType::MACHINE_SHOP) == false)
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
