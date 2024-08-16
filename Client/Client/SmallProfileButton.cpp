#include "pch.h"
#include "SmallProfileButton.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Player.h"

using namespace std;

void CSmallProfileButton::Initialize()
{
	CButtonUI::Initialize();
	InsertOnClickDelegate(this, &CSmallProfileButton::OnButtonClick);
}

void CSmallProfileButton::Update()
{
	CButtonUI::Update();
}

void CSmallProfileButton::LateUpdate()
{
	CButtonUI::LateUpdate();
}

void CSmallProfileButton::Render(HDC _hDC)
{
	CButtonUI::Render(_hDC);
}

void CSmallProfileButton::Release()
{
	CButtonUI::Release();
}

void CSmallProfileButton::OnButtonClick()
{
	VERIFY_NULLPTR(m_pButtonOwner);
	CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
	
	CGameManager::GetManager()->ClearSelectedObject();
	CGameManager::GetManager()->InsertSelectedObject(m_pButtonOwner);
}
