#include "pch.h"
#include "SplyDptCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "PropertyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "SCV.h"

#include "BuildingProperty.h"
#include "Sprite.h"

using namespace std;

void CSplyDptCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CSplyDptCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::S))
	{
		CBuildingProperty* pProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::SUPPLY_DEPOT);
		
		// 자원이 부족한 경우
		if (CGameManager::GetManager()->GetProducedMineral() < pProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_SUPPLY_DEPOT);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CSplyDptCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CSplyDptCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CSplyDptCmdButton::Release()
{
	CCmdButton::Release();

}

void CSplyDptCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_SUPPLY_DEPOT);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}
