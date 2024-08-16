#include "pch.h"
#include "HPBarUI.h"

#include "PropertyManager.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "TerranObject.h"
#include "Unit.h"
#include "Building.h"

#include "SceneManager.h"
#include "Scene.h"

void CHPBarUI::Initialize()
{
	CSliderUI::Initialize();

	SetBackRectPosition({ m_pHPBarOwner->GetPosition().m_fX, m_pHPBarOwner->GetPosition().m_fY + m_fDistance });
	SetFillRectPosition({ m_pHPBarOwner->GetPosition().m_fX, m_pHPBarOwner->GetPosition().m_fY + m_fDistance });
	SetBackRectSize({ m_pHPBarOwner->GetSize().m_iX, 5 });
	SetFillRectSize({ m_pHPBarOwner->GetSize().m_iX, 5 });

	SetBackRectColor(RGB(128, 128, 128));
	SetBackRectBorderColor(RGB(0, 0, 0));
	SetFillRectColor(RGB(0, 255, 0));
	SetFillRectBorderColor(RGB(0, 0, 0));
}

void CHPBarUI::Update()
{
	CSliderUI::Update();
	UpdateUIPosition();
	UpdateFillAmount();
}

void CHPBarUI::LateUpdate()
{
	CSliderUI::LateUpdate();
}

void CHPBarUI::Render(HDC _hDC)
{
	VERIFY_NULLPTR(m_pHPBarOwner);
	if (m_pHPBarOwner->GetSelected())
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

void CHPBarUI::Release()
{
	CSliderUI::Release();
}

void CHPBarUI::UpdateUIPosition()
{
	VERIFY_NULLPTR(m_pHPBarOwner);
	SetBackRectPosition({ m_pHPBarOwner->GetPosition().m_fX, m_pHPBarOwner->GetPosition().m_fY + m_fDistance });
	SetFillRectPosition({ m_pHPBarOwner->GetPosition().m_fX, m_pHPBarOwner->GetPosition().m_fY + m_fDistance });
}

void CHPBarUI::UpdateFillAmount()
{
	VERIFY_NULLPTR(m_pHPBarOwner);
	ETerranObjectType eTerranObjectType = m_pHPBarOwner->GetTerranObjectType();

	float fRatio = 0.0f;

	switch (eTerranObjectType)
	{
	case ETerranObjectType::GROUND_UNIT:
	case ETerranObjectType::AIR_UNIT:
	{
		CUnit* pUnit = dynamic_cast<CUnit*>(m_pHPBarOwner);
		fRatio = (float)pUnit->GetCurHP() / (float)pUnit->GetUnitProperty().GetMaxHP();
		SetFillAmount(fRatio);
	}
	break;

	case ETerranObjectType::BUILDING:
	{
		CBuilding* pBuilding = dynamic_cast<CBuilding*>(m_pHPBarOwner);
		fRatio = (float)pBuilding->GetCurHP() / (float)pBuilding->GetBuildingProperty().GetMaxHP();
		SetFillAmount(fRatio);
	}
	break;

	default:
	break;
	}

	if (0.0f <= fRatio && fRatio < 0.333f)
	{
		SetFillRectColor(RGB(255, 0, 0));
	}
	else if (0.333f <= fRatio && fRatio < 0.666f)
	{
		SetFillRectColor(RGB(255, 255, 0));
	}
	else if (0.666f < fRatio && fRatio <= 1.0f)
	{
		SetFillRectColor(RGB(0, 255, 0));
	}
}

