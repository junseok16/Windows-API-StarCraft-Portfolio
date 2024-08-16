#include "pch.h"
#include "GoliathCmdButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "PropertyManager.h"
#include "UnitProperty.h"
#include "Scene.h"
#include "Player.h"
#include "TerranObject.h"

void CGoliathCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 769.0f, 470.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CGoliathCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	VerifyTechTree();// 테크 트리를 확인합니다.

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::G))
	{
		CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
		CUnitProperty* pGoliathProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GOLIATH);
		// 자원이 부족한 경우
		if (CGameManager::GetManager()->GetProducedMineral() < pGoliathProperty->GetMineral())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		if (CGameManager::GetManager()->GetProducedGas() < pGoliathProperty->GetGas())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		// 보급품이 부족한 경우
		if (CGameManager::GetManager()->GetConsumedSupply() + pGoliathProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
		{
			CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
			return;
		}

		//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
		//dynamic_cast<CTerranObject*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		//CScene::s_pPlayer->SendCommand(ECommandType::BUILD_GOLIATH);
		CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
		CGameManager::GetManager()->SendCommand(ECommandType::BUILD_GOLIATH);
	}
}

void CGoliathCmdButton::LateUpdate()
{
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CGoliathCmdButton::Render(HDC _hDC)
{
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CGoliathCmdButton::Release()
{
	CCmdButton::Release();
}

void CGoliathCmdButton::OnButtonClick()
{
	if (!m_bUIActive) { return; }
	CCmdButton::OnButtonClick();

	CUnitProperty* pGoliathProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GOLIATH);
	// 자원이 부족한 경우
	if (CGameManager::GetManager()->GetProducedMineral() < pGoliathProperty->GetMineral())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr00.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	if (CGameManager::GetManager()->GetProducedGas() < pGoliathProperty->GetGas())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr01.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	// 보급품이 부족한 경우
	if (CGameManager::GetManager()->GetConsumedSupply() + pGoliathProperty->GetConsumeSupply() > CGameManager::GetManager()->GetProducedSupply())
	{
		CSoundManager::GetManager()->PlaySoundEx(L"taderr02.wav", ESoundChannel::ADVISOR, 1.0f);
		return;
	}

	//CObject* pObject = CScene::s_pPlayer->GetSelectedObjects().front();
	//dynamic_cast<CTerranObject*>(pObject)->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	//CScene::s_pPlayer->SendCommand(ECommandType::BUILD_GOLIATH);
	CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_B);
	CGameManager::GetManager()->SendCommand(ECommandType::BUILD_GOLIATH);
}

void CGoliathCmdButton::VerifyTechTree()
{
	std::array<int32, (int32)ETerranBuildingType::ENUM_END>& arrNumBuildings = CGameManager::GetManager()->GetNumBuildings();

	if (arrNumBuildings[(int32)ETerranBuildingType::ARMORY] <= 0)// ||
		// arrNumBuildings[(int32)ETerranBuildingType::SCIENCE_FACILITY] <= 0)
	{
		SetButtonState(EButtonState::DISABLE);
	}
	else if (arrNumBuildings[(int32)ETerranBuildingType::ARMORY] >= 1)
	{
		if (GetButtonState() != EButtonState::DISABLE)
		{
			return;
		}
		SetButtonState(EButtonState::RELEASE);
	}
}
