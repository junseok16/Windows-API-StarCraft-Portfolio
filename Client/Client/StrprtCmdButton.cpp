#include "pch.h"
#include "StrprtCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "SCV.h"
using namespace std;

void CStrprtCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CStrprtCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::S))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);

		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_STARPORT);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CStrprtCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CStrprtCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CStrprtCmdButton::Release()
{
	CCmdButton::Release();
}

void CStrprtCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_STARPORT);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

void CStrprtCmdButton::VerifyTechTree()
{
	std::array<int32, (int32)ETerranBuildingType::ENUM_END>& arrNumBuildings = CGameManager::GetManager()->GetNumBuildings();

	if (arrNumBuildings[(int32)ETerranBuildingType::FACTORY] <= 0)
	{
		SetButtonState(EButtonState::DISABLE);
	}
	else if (arrNumBuildings[(int32)ETerranBuildingType::FACTORY] >= 1)
	{
		if (GetButtonState() != EButtonState::DISABLE)
		{
			return;
		}
		SetButtonState(EButtonState::RELEASE);
	}
}
