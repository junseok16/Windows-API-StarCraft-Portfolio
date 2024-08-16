#include "pch.h"
#include "Widget.h"
using namespace std;

void CWidget::Initialize()
{
	CUI::Initialize();

	for (auto pUI : m_pUIs)
	{
		pUI->Initialize();
	}
}

void CWidget::Update()
{
	CUI::Update();

	if (m_bWidgetActive == true)
	{
		for (auto pUI : m_pUIs)
		{
			pUI->Update();
		}
	}
}

void CWidget::LateUpdate()
{
	CUI::LateUpdate();

	if (m_bWidgetActive == true)
	{
		for (auto pUI : m_pUIs)
		{
			pUI->LateUpdate();
		}
	}
}

void CWidget::Render(HDC _hDC)
{
	CUI::Render(_hDC);

	if (m_bWidgetActive == true)
	{
		for (auto pUI : m_pUIs)
		{
			pUI->Render(_hDC);
		}
	}
}

void CWidget::Release()
{
	CUI::Release();

	for (auto pUI : m_pUIs)
	{
		pUI->Release();
		SAFE_DELETE(pUI);
	}
	m_pUIs.clear();
}

void CWidget::SetWidgetActive(bool _bWidgetActive)
{
	m_bWidgetActive = _bWidgetActive;

	for (const auto& pUI : m_pUIs)
	{
		pUI->SetUIActive(_bWidgetActive);
	}
}

bool CWidget::GetWidgetActive() const
{
	return m_bWidgetActive;
}

void CWidget::InsertUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_pUIs.push_back(_pUI);
}

void CWidget::EraseUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_pUIs.erase(remove(m_pUIs.begin(), m_pUIs.end(), _pUI), m_pUIs.end());

	// TODO: 여기서 삭제해도 될까?
	SAFE_DELETE(_pUI);
}
