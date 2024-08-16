#include "pch.h"
#include "ControlCenter.h"

#include "ResourceManager.h"
using namespace std;

void CControlCenter::Initialize()
{
	CSpriteUI::Initialize();

	CSprite* pCtrlCenterSprite = CResourceManager::GetManager()->GetSprite(L"CtrlCenterUI");

	// CUI 속성을 초기화합니다.
	SetPosition({ 400.0f, 300.0f });
	SetSize({ 800, 600 });
	SetUIType(EUIType::ENUM_END);// TODO: ui 타입으로 뭘 할 수 있을까...
	SetGdiRender(true);
	SetUIActive(true);

	// CSpriteUI 속성을 초기화합니다.
	SetSprite(pCtrlCenterSprite);
}

void CControlCenter::Update()
{
	CSpriteUI::Update();
}

void CControlCenter::LateUpdate()
{
	CSpriteUI::LateUpdate();
}

void CControlCenter::Render(HDC _hDC)
{
	CSpriteUI::Render(_hDC);
}

void CControlCenter::Release()
{
	CSpriteUI::Release();
}
