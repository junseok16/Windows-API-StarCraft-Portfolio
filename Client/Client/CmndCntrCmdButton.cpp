#include "pch.h"
#include "CmndCntrCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "SCV.h"
using namespace std;

void CCmndCntrCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CCmndCntrCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::C))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		// 자원이 부족한 경우
		CBuildingProperty* pProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::COMMAND_CENTER);
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

		//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
		//dynamic_cast<CSCV*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_D);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_COMMAND_CENTER);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CCmndCntrCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CCmndCntrCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CCmndCntrCmdButton::Release()
{
	CCmdButton::Release();
}

void CCmndCntrCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();
	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CSCV*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_D);
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_COMMAND_CENTER);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}
