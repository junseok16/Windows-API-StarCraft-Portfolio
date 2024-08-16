#include "pch.h"
#include "CmdButton.h"

#include "SoundManager.h"

void CCmdButton::Initialize()
{
	CButtonUI::Initialize();
	InsertOnClickDelegate(this, &CCmdButton::OnButtonClick);
}

void CCmdButton::Update()
{
	CButtonUI::Update();
}

void CCmdButton::LateUpdate()
{
	CButtonUI::LateUpdate();
}

void CCmdButton::Render(HDC _hDC)
{
	CButtonUI::Render(_hDC);
}

void CCmdButton::Release()
{
	CButtonUI::Release();
}

void CCmdButton::OnButtonClick()
{
	CSoundManager::GetManager()->PlaySoundEx(L"button.wav", ESoundChannel::CONTROL_CENTER, 1.0f);
}
