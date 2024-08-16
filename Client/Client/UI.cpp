#include "pch.h"
#include "UI.h"
#include "MouseManager.h"

void CUI::Initialize()
{

}

void CUI::Update()
{

}

void CUI::LateUpdate()
{

}

void CUI::Render(HDC _hDC)
{

}

void CUI::Release()
{

}

bool CUI::IsCursorInRect()
{
	RECT tUIRect = CGeometry::GetRect(m_tPosition, m_tSize);
	POINT tMousePosition = Vector2::Vector2ToPoint(CMouseManager::GetManager()->GetMousePosition());

	return ::PtInRect(&tUIRect, tMousePosition);
}
