#include "pch.h"
#include "UpIonThrstrCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "UpgradeProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CUpIonThrstrCmdButton::Initialize() {
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);

	pIonThrstrProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::ION_THRUSTERS);
}

void CUpIonThrstrCmdButton::Update() {
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::I))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		if (CGameManager::GetManager()->GetProducedMineral() < pIonThrstrProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pIonThrstrProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
		//dynamic_cast<CTerranObject*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		//CScene::s_pPlayer->SendCommand(ECommandType::UPGRADE_ION_THRUSTERS);


		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_ION_THRUSTERS);
	}
}

void CUpIonThrstrCmdButton::LateUpdate()
{
	if (!m_bUIActive) { return; }
	CCmdButton::LateUpdate();
}

void CUpIonThrstrCmdButton::Render(HDC _hDC)
{
	if (!m_bUIActive) { return; }
	CCmdButton::Render(_hDC);
}

void CUpIonThrstrCmdButton::Release()
{
	CCmdButton::Release();
}

void CUpIonThrstrCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	if (CGameManager::GetManager()->GetProducedMineral() < pIonThrstrProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pIonThrstrProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CTerranObject*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	//CScene::s_pPlayer->SendCommand(ECommandType::UPGRADE_ION_THRUSTERS);


	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	CGameManager::GetManager()->SendCommand(ECommandType::UPGRADE_ION_THRUSTERS);
}
