#include "pch.h"
#include "CvrtOpsCmdButton.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "BuildingProperty.h"
#include "Scene.h"
#include "Cursor.h"
#include "TerranObject.h"

void CCvrtOpsCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 655.0f, 570.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CCvrtOpsCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::C))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);

		// 미네랄이 부족한 경우
		CBuildingProperty* pProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::COVERT_OPS);
		if (CGameManager::GetManager()->GetProducedMineral() < pProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}
		// 가스가 부족한 경우
		if (CGameManager::GetManager()->GetProducedGas() < pProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_COVERT_OPS);
		CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
	}
}

void CCvrtOpsCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CCvrtOpsCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CCvrtOpsCmdButton::Release()
{
	CCmdButton::Release();
}

void CCvrtOpsCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();

	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	CScene::s_pCursor->SetWatingCmdType(ECommandType::BUILD_COVERT_OPS);
	CScene::s_pCursor->SetCursorCmdMode(ECursorCommandMode::KEYBOARD_MODE);
}
