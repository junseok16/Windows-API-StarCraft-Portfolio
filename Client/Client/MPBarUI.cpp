#include "pch.h"
#include "MPBarUI.h"

#include "PropertyManager.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "TerranObject.h"
#include "Unit.h"
#include "Building.h"

#include "SceneManager.h"
#include "Scene.h"

void CMPBarUI::Initialize()
{
	CSliderUI::Initialize();

	SetBackRectPosition({ m_pMPBarOwner->GetPosition().m_fX, m_pMPBarOwner->GetPosition().m_fY + m_fDistance });
	SetFillRectPosition({ m_pMPBarOwner->GetPosition().m_fX, m_pMPBarOwner->GetPosition().m_fY + m_fDistance });
	SetBackRectSize({ m_pMPBarOwner->GetSize().m_iX, 5 });
	SetFillRectSize({ m_pMPBarOwner->GetSize().m_iX, 5 });

	SetBackRectColor(RGB(128, 128, 128));
	SetBackRectBorderColor(RGB(0, 0, 0));
	SetFillRectColor(RGB(255, 0, 255));
	SetFillRectBorderColor(RGB(0, 0, 0));
}

void CMPBarUI::Update()
{
	CSliderUI::Update();
	UpdateUIPosition();
	UpdateFillAmount();
}

void CMPBarUI::LateUpdate()
{
	CSliderUI::LateUpdate();
}

void CMPBarUI::Render(HDC _hDC)
{
	VERIFY_NULLPTR(m_pMPBarOwner);
	if (m_pMPBarOwner->GetSelected())
	{
		// 스크롤된 위치를 구합니다.
		CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
		Vector2 tCameraPosition = pCurScene->GetCameraPosition();

		CGeometry::DrawRectangle(_hDC, { m_tBackRectPosition.m_fX - (tCameraPosition.m_fX - FWINCX * 0.5f), m_tBackRectPosition.m_fY - (tCameraPosition.m_fY - FWINCY * 0.5f) }, m_tBackRectSize, m_iBackColor);
		float fOffset = m_tFillRectSize.m_iX * m_fFillAmount;
		float fDelta = (m_tBackRectSize.m_iX - fOffset) * 0.5f;
		CGeometry::DrawRectangle(_hDC, { m_tFillRectPosition.m_fX - (int32)fDelta - (tCameraPosition.m_fX - FWINCX * 0.5f), m_tFillRectPosition.m_fY - (tCameraPosition.m_fY - FWINCY * 0.5f) }, { (int32)fOffset, m_tFillRectSize.m_iY }, m_iFillColor);
	}
}

void CMPBarUI::Release()
{
	CSliderUI::Release();
}

void CMPBarUI::UpdateUIPosition()
{
	VERIFY_NULLPTR(m_pMPBarOwner);
	SetBackRectPosition({ m_pMPBarOwner->GetPosition().m_fX, m_pMPBarOwner->GetPosition().m_fY + m_fDistance });
	SetFillRectPosition({ m_pMPBarOwner->GetPosition().m_fX, m_pMPBarOwner->GetPosition().m_fY + m_fDistance });
}

void CMPBarUI::UpdateFillAmount()
{
	VERIFY_NULLPTR(m_pMPBarOwner);
	ETerranObjectType eTerranObjectType = m_pMPBarOwner->GetTerranObjectType();

	float fRatio = 0.0f;

	switch (eTerranObjectType)
	{
	case ETerranObjectType::GROUND_UNIT:
	case ETerranObjectType::AIR_UNIT:
	{
		CUnit* pUnit = dynamic_cast<CUnit*>(m_pMPBarOwner);
		fRatio = (float)pUnit->GetCurMP() / (float)pUnit->GetUnitProperty().GetMaxMP();
		SetFillAmount(fRatio);
	}
	break;

	case ETerranObjectType::BUILDING:
	{
		CBuilding* pBuilding = dynamic_cast<CBuilding*>(m_pMPBarOwner);
		fRatio = (float)pBuilding->GetCurMP() / (float)pBuilding->GetBuildingProperty().GetMaxMP();
		SetFillAmount(fRatio);
	}
	break;

	default:
	break;
	}
}
