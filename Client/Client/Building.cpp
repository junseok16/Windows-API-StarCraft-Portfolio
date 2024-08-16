#include "pch.h"
#include "Building.h"
#include "BuildingProperty.h"

CBuilding::CBuilding(CBuildingProperty& _buildingProperty) :
	m_buildingProperty(_buildingProperty) { }

void CBuilding::Initialize()
{
	CAnimationObject::Initialize();
}

void CBuilding::Update()
{
	CAnimationObject::Update();
	UpdateWireframe();
}

void CBuilding::LateUpdate()
{
	CAnimationObject::LateUpdate();
}

void CBuilding::Render(HDC _hDC)
{
	CAnimationObject::Render(_hDC);
}

void CBuilding::Release()
{
	CAnimationObject::Release();
}

void CBuilding::UpdateWireframe()
{
	// 체력 상태에 따라 와이어프레임을 업데이트합니다.
	int32 iMaxHP = GetBuildingProperty().GetMaxHP();
	int32 iCurHP = GetCurHP();

	int32 i56HP = iMaxHP * 5 / 6;
	int32 i46HP = iMaxHP * 4 / 6;
	int32 i36HP = iMaxHP * 3 / 6;
	int32 i26HP = iMaxHP * 2 / 6;
	int32 i16HP = iMaxHP * 1 / 6;

	if (i56HP < iCurHP && iCurHP <= iMaxHP)
	{
		m_pCurBigWireframe = m_pBigWireframe[0];
		m_iCurHPColor = RGB(0, 255, 0);
	}
	else if (i46HP < iCurHP && iCurHP <= i56HP)
	{
		m_pCurBigWireframe = m_pBigWireframe[1];
		m_iCurHPColor = RGB(0, 255, 0);
	}
	else if (i36HP < iCurHP && iCurHP <= i46HP)
	{
		m_pCurBigWireframe = m_pBigWireframe[2];
		m_iCurHPColor = RGB(255, 255, 0);
	}
	else if (i26HP < iCurHP && iCurHP <= i36HP)
	{
		m_pCurBigWireframe = m_pBigWireframe[3];
		m_iCurHPColor = RGB(255, 255, 0);
	}
	else if (i16HP < iCurHP && iCurHP <= i26HP)
	{
		m_pCurBigWireframe = m_pBigWireframe[4];
		m_iCurHPColor = RGB(255, 0, 0);
	}
	else if (0 < iCurHP && iCurHP <= i56HP)
	{
		m_pCurBigWireframe = m_pBigWireframe[5];
		m_iCurHPColor = RGB(255, 0, 0);
	}
}
