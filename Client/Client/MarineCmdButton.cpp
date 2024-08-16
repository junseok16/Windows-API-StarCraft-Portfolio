#include "pch.h"
#include "MarineCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"

#include "UnitProperty.h"
#include "TerranObject.h"

void CMarineCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CMarineCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::M))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		
		// 자원이 부족한 경우
		CUnitProperty* pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
		if (CGameManager::GetManager()->GetProducedMineral() < pMarineProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pMarineProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		// 보급품이 부족한 경우
		if (CGameManager::GetManager()->GetConsumedSupply() + pMarineProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		CGameManager::GetManager()->SendCommand(ECommandType::BUILD_MARINE);
	}
}

void CMarineCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CMarineCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CMarineCmdButton::Release()
{
	CCmdButton::Release();
}

void CMarineCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	// 자원이 부족한 경우
	CUnitProperty* pMarineProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::MARINE);
	if (CGameManager::GetManager()->GetProducedMineral() < pMarineProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pMarineProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	// 보급품이 부족한 경우
	if (CGameManager::GetManager()->GetConsumedSupply() + pMarineProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CTerranObject*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	//CScene::s_pPlayer->SendCommand(ECommandType::BUILD_MARINE);

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	CGameManager::GetManager()->SendCommand(ECommandType::BUILD_MARINE);
}
