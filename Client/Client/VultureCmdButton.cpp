#include "pch.h"
#include "VultureCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "UnitProperty.h"
#include "Scene.h"
#include "Player.h"

#include "Factory.h"

void CVultureCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CVultureCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::V))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		// 자원이 부족한 경우
		CUnitProperty* pVultureProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
		if (CGameManager::GetManager()->GetProducedMineral() < pVultureProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pVultureProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		// 보급품이 부족한 경우
		if (CGameManager::GetManager()->GetConsumedSupply() + pVultureProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
		//dynamic_cast<CFactory*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		//CScene::s_pPlayer->SendCommand(ECommandType::BUILD_VULTURE);


		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		CGameManager::GetManager()->SendCommand(ECommandType::BUILD_VULTURE);
	}
}

void CVultureCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CVultureCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CVultureCmdButton::Release()
{
	CCmdButton::Release();
}

void CVultureCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	// 자원이 부족한 경우
	CUnitProperty* pVultureProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
	if (CGameManager::GetManager()->GetProducedMineral() < pVultureProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pVultureProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	// 보급품이 부족한 경우
	if (CGameManager::GetManager()->GetConsumedSupply() + pVultureProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CFactory*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	//CScene::s_pPlayer->SendCommand(ECommandType::BUILD_VULTURE);

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	CGameManager::GetManager()->SendCommand(ECommandType::BUILD_VULTURE);
}
