#include "pch.h"
#include "ResourceWidget.h"

#include "SpriteUI.h"
#include "TextUI.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"
using namespace std;

void CResourceWidget::Initialize()
{
	CWidget::Initialize();

	CSprite* pMineralSprite = CResourceManager::GetManager()->GetSprite(L"MineralUI");
	CSprite* pGasSprite = CResourceManager::GetManager()->GetSprite(L"GasUI");
	CSprite* pSupplySprite = CResourceManager::GetManager()->GetSprite(L"SplyUI");

	m_pMineralSpriteUI = new CSpriteUI();
	m_pMineralSpriteUI->SetPosition({ 570.0f, 20.0f });
	m_pMineralSpriteUI->SetSize({ 14, 14 });
	m_pMineralSpriteUI->SetGdiRender(false);
	m_pMineralSpriteUI->SetSprite(pMineralSprite);
	InsertUI(m_pMineralSpriteUI);

	m_pGasSpriteUI = new CSpriteUI();
	m_pGasSpriteUI->SetPosition({ 660.0f, 20.0f });
	m_pGasSpriteUI->SetSize({ 14, 14 });
	m_pGasSpriteUI->SetGdiRender(false);
	m_pGasSpriteUI->SetSprite(pGasSprite);
	InsertUI(m_pGasSpriteUI);

	m_pSupplySpriteUI = new CSpriteUI();
	m_pSupplySpriteUI->SetPosition({ 730.0f, 20.0f });
	m_pSupplySpriteUI->SetSize({ 20, 20 });
	m_pSupplySpriteUI->SetGdiRender(false);
	m_pSupplySpriteUI->SetSprite(pSupplySprite);
	InsertUI(m_pSupplySpriteUI);

	m_pMineralTextUI = new CTextUI();
	m_pMineralTextUI->SetFontHeight(20);
	m_pMineralTextUI->SetPosition({ 580.0f, 10.0f });
	m_pMineralTextUI->SetSize({ 10, 10 });
	m_pMineralTextUI->SetFontColor(RGB(0, 255, 0));
	m_pMineralTextUI->SetText(L"50");
	InsertUI(m_pMineralTextUI);

	m_pGasTextUI = new CTextUI();
	m_pGasTextUI->SetFontHeight(20);
	m_pGasTextUI->SetPosition({ 670.0f, 10.0f });
	m_pGasTextUI->SetSize({ 10, 10 });
	m_pGasTextUI->SetFontColor(RGB(0, 255, 0));
	m_pGasTextUI->SetText(L"0");
	InsertUI(m_pGasTextUI);

	m_pSupplyTextUI = new CTextUI();
	m_pSupplyTextUI->SetFontHeight(20);
	m_pSupplyTextUI->SetPosition({ 740.0f, 10.0f });
	m_pSupplyTextUI->SetSize({ 10, 10 });
	m_pSupplyTextUI->SetFontColor(RGB(0, 255, 0));
	m_pSupplyTextUI->SetText(L"0");
	InsertUI(m_pSupplyTextUI);
}

void CResourceWidget::Update()
{
	CWidget::Update();
	SetMineralText(to_wstring(CGameManager::GetManager()->GetProducedMineral()));
	SetGasText(to_wstring(CGameManager::GetManager()->GetProducedGas()));
	SetSupplyText(to_wstring(CGameManager::GetManager()->GetConsumedSupply()) + L" / " + to_wstring(CGameManager::GetManager()->GetProducedSupply()));
}

void CResourceWidget::LateUpdate()
{
	CWidget::LateUpdate();
}

void CResourceWidget::Render(HDC _hDC)
{
	CWidget::Render(_hDC);
}

void CResourceWidget::Release()
{
	CWidget::Release();
}

void CResourceWidget::SetMineralSprite(CSprite* _pMineralSprite)
{
	m_pMineralSpriteUI->SetSprite(_pMineralSprite);
}

void CResourceWidget::SetMineralText(std::wstring _strMineral)
{
	m_pMineralTextUI->SetText(_strMineral);
}

void CResourceWidget::SetGasSprite(CSprite* _pGasSprite)
{
	m_pGasSpriteUI->SetSprite(_pGasSprite);
}

void CResourceWidget::SetGasText(std::wstring _strGas)
{
	m_pGasTextUI->SetText(_strGas);
}

void CResourceWidget::SetSupplySprite(CSprite* _pSupplySprite)
{
	m_pSupplySpriteUI->SetSprite(_pSupplySprite);
}

void CResourceWidget::SetSupplyText(std::wstring _strSupply)
{
	m_pSupplyTextUI->SetText(_strSupply);
}
