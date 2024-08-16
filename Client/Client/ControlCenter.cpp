#include "pch.h"
#include "ControlCenter.h"

#include "ResourceManager.h"
using namespace std;

void CControlCenter::Initialize()
{
	CSpriteUI::Initialize();

	CSprite* pCtrlCenterSprite = CResourceManager::GetManager()->GetSprite(L"CtrlCenterUI");

	// CUI �Ӽ��� �ʱ�ȭ�մϴ�.
	SetPosition({ 400.0f, 300.0f });
	SetSize({ 800, 600 });
	SetUIType(EUIType::ENUM_END);// TODO: ui Ÿ������ �� �� �� ������...
	SetGdiRender(true);
	SetUIActive(true);

	// CSpriteUI �Ӽ��� �ʱ�ȭ�մϴ�.
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
