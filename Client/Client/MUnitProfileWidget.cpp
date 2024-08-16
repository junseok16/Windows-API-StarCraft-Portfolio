#include "pch.h"
#include "MUnitProfileWidget.h"

#include "ResourceManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"

#include "SpriteUI.h"
#include "AnimationUI.h"
#include "SmallProfileButton.h"

#include "UnitProperty.h"
#include "TerranObject.h"
#include "Unit.h"
using namespace std;

void CMUnitProfileWidget::Initialize()
{
	for (int32 iRow = 0; iRow < 2; ++iRow)
	{
		for (int32 iColumn = 0; iColumn < 6; ++iColumn)
		{
			m_pBlueButtonBox[iRow][iColumn] = new CSpriteUI();
			m_pBlueButtonBox[iRow][iColumn]->SetSprite(CResourceManager::GetManager()->GetSprite(L"SmlPrflBx"));
			m_pBlueButtonBox[iRow][iColumn]->SetPosition({ 230.0f + iColumn * 47.0f, 520.0f + iRow * 47.0f });
			m_pBlueButtonBox[iRow][iColumn]->SetSize({ 42, 42 });
			m_pBlueButtonBox[iRow][iColumn]->SetUIActive(false);
			InsertUI(m_pBlueButtonBox[iRow][iColumn]);

			m_pButton[iRow][iColumn] = new CSmallProfileButton();
			m_pButton[iRow][iColumn]->SetButtonState(EButtonState::RELEASE);
			m_pButton[iRow][iColumn]->SetPosition({ 230.0f + iColumn * 47.0f, 520.0f + iRow * 47.0f });
			m_pButton[iRow][iColumn]->SetSize({ 42, 42 });
			m_pButton[iRow][iColumn]->SetUIActive(false);
			InsertUI(m_pButton[iRow][iColumn]);
		}
	}

	m_pPortraitUI = new CAnimationUI();
	m_pPortraitUI->SetPosition({ 555.0f, 550.0f });
	m_pPortraitUI->SetSize({ 60, 56 });
	m_pPortraitUI->SetUIActive(false);
	m_pPortraitUI->SetAnimation(nullptr);
	InsertUI(m_pPortraitUI);

	CWidget::Initialize();
}

void CMUnitProfileWidget::Update()
{
	CWidget::Update();

	// 한 유닛일 때, 멀티 프로필을 끕니다.
	vector<CTerranObject*>& vecSelectedObjects = CGameManager::GetManager()->GetSelectedObjects();
	if (vecSelectedObjects.size() <= 1) { SetWidgetActive(false); return; }

	// 여러 유닛일 때, 멀티 프로필을 켭니다.
	SetWidgetActive(true);
	int32 iMaxRank = -1;
	CUnit* pHighRankUnit = nullptr;

	// 가장 높은 계급의 초상화를 켭니다.
	for (auto iter = vecSelectedObjects.begin(); iter != vecSelectedObjects.end();)
	{
		CUnit* pUnit = dynamic_cast<CUnit*>(*iter);
		int32 iCurRank = pUnit->GetUnitProperty().GetIntRank();

		if (iMaxRank == -1)
		{
			iMaxRank = iCurRank;
			pHighRankUnit = pUnit;
		}
		else if (iMaxRank < iCurRank)
		{
			iMaxRank = iCurRank;
			pHighRankUnit = pUnit;
		}
		iter++;
	}
	SetPortraitAnim(pHighRankUnit->GetPortraitAnim());

	// 선택된 유닛의 버튼을 켭니다.
	for (uint32 i = 0; i < 12; ++i)
	{
		int32 iRow = i % 2;
		int32 iColumn = i / 2;

		if (i < vecSelectedObjects.size())
		{
			m_pBlueButtonBox[iRow][iColumn]->SetUIActive(true);

			CUnit* pUnit = dynamic_cast<CUnit*>(vecSelectedObjects[i]);
			m_pButton[iRow][iColumn]->SetCurSprite(pUnit->GetCurSmallWireframeSprite());
			m_pButton[iRow][iColumn]->SetButtonOwner(pUnit);
			m_pButton[iRow][iColumn]->SetUIActive(true);
		}
		// 선택되지 않은 유닛의 버튼을 끕니다.
		else
		{
			m_pBlueButtonBox[iRow][iColumn]->SetUIActive(false);

			m_pButton[iRow][iColumn]->SetCurSprite(nullptr);
			m_pButton[iRow][iColumn]->SetButtonOwner(nullptr);
			m_pButton[iRow][iColumn]->SetUIActive(false);
		}
	}
}

void CMUnitProfileWidget::LateUpdate()
{
	CWidget::LateUpdate();
}

void CMUnitProfileWidget::Render(HDC _hDC)
{
	CWidget::Render(_hDC);
}

void CMUnitProfileWidget::Release()
{
	CWidget::Release();
}

void CMUnitProfileWidget::SetButtonSprite(int32 _iRow, int32 _iColumn, EButtonState _eButtonState, CSprite* _pButtonSprite)
{
	m_pButton[_iRow][_iColumn]->SetSpriteAt(_eButtonState, _pButtonSprite);
}

void CMUnitProfileWidget::SetPortraitAnim(CAnimation* _pPortraitAnim)
{
	m_pPortraitUI->SetAnimation(_pPortraitAnim);
}

