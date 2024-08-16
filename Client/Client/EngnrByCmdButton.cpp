#include "pch.h"
#include "EngnrByCmdButton.h"

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

void CEngnrByCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 520.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CEngnrByCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }
	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::E))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		// 자원이 부족한 경우
		CBuildingProperty* pProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::ENGINEERING_BAY);
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
		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_ENGINEERING_BAY);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CEngnrByCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }

}

void CEngnrByCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }

}

void CEngnrByCmdButton::Release()
{
	CCmdButton::Release();

}

void CEngnrByCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();
	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CSCV*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_D);
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_E);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_ENGINEERING_BAY);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}

void CEngnrByCmdButton::VerifyTechTree()
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
