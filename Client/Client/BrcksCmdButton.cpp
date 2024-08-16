#include "pch.h"
#include "BrcksCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "BuildingProperty.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "SCV.h"
using namespace std;

void CBrcksCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 520.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CBrcksCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }
	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::B))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		
		// 자원이 부족한 경우
		CBuildingProperty* pProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::BARRACKS);
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
		
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_BARRACKS);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CBrcksCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CBrcksCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CBrcksCmdButton::Release()
{
	CCmdButton::Release();

}

void CBrcksCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_BARRACKS);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

void CBrcksCmdButton::VerifyTechTree()
{
	std::array<int32, (int32)ETerranBuildingType::ENUM_END>& arrNumBuildings = CGameManager::GetManager()->GetNumBuildings();

	if (arrNumBuildings[(int32)ETerranBuildingType::COMMAND_CENTER] <= 0)
	{
		SetButtonState(EButtonState::DISABLE);
	}
	else if (arrNumBuildings[(int32)ETerranBuildingType::COMMAND_CENTER] >= 1)
	{
		if (GetButtonState() != EButtonState::DISABLE)
		{
			return;
		}
		SetButtonState(EButtonState::RELEASE);
	}
}
