#include "pch.h"
#include "RlyPntCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "TerranObject.h"
using namespace std;

void CRlyPntCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 520.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CRlyPntCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::R))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::SET_RALLY_POINT);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CRlyPntCmdButton::LateUpdate() {
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CRlyPntCmdButton::Render(HDC _hDC) {
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CRlyPntCmdButton::Release() {
	CCmdButton::Release();

}

void CRlyPntCmdButton::OnButtonClick() {
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::SET_RALLY_POINT);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

