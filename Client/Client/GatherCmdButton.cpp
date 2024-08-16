#include "pch.h"
#include "GatherCmdButton.h"

void CGatherCmdButton::Initialize()
{
	CCmdButton::Initialize();
	SetButtonState(EButtonState::RELEASE);
	SetCurSprite(GetSpriteAt(EButtonState::RELEASE));
	SetPosition({ 712.0f, 520.0f });
	SetSize({ 44, 44 });
	SetUIActive(false);
}

void CGatherCmdButton::Update()
{
	CCmdButton::Update();
	if (!m_bUIActive) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

}

void CGatherCmdButton::LateUpdate() {
	CCmdButton::LateUpdate();
	if (!m_bUIActive) { return; }
}

void CGatherCmdButton::Render(HDC _hDC) {
	CCmdButton::Render(_hDC);
	if (!m_bUIActive) { return; }
}

void CGatherCmdButton::Release() {
	CCmdButton::Release();
}

void CGatherCmdButton::OnButtonClick() 
{
	if (!m_bUIActive) { return; }

	CCmdButton::OnButtonClick();

}
