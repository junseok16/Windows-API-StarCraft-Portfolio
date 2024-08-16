#include "pch.h"
#include "SUnitProfileWidget.h"

#include "ButtonUI.h"
#include "SpriteUI.h"
#include "AnimationUI.h"
#include "TextUI.h"

#include "ResourceManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Object.h"
#include "TerranObject.h"
#include "Player.h"
#include "Unit.h"
#include "Building.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "CommandCenter.h"
#include "Barracks.h"
#include "Factory.h"
#include "Starport.h"

#include "EngineeringBay.h"
#include "Academy.h"
#include "Armory.h"
#include "MachineShop.h"
using namespace std;

void CSUnitProfileWidget::Initialize()
{
	CWidget::Initialize();
	{
		m_pBigWireUI = new CSpriteUI();
		m_pBigWireUI->SetPosition({ 250.0f, 530.0f });
		m_pBigWireUI->SetSize({ 70, 70 });
		m_pBigWireUI->SetGdiRender(false);
		m_pBigWireUI->SetSprite(nullptr);
		InsertUI(m_pBigWireUI);

		m_pHPUI = new CTextUI();
		m_pHPUI->SetFontHeight(17);
		m_pHPUI->SetPosition({ 238.0f, 560.0f });
		m_pHPUI->SetSize({ 10, 10 });
		m_pHPUI->SetFontColor(RGB(0, 255, 0));
		m_pHPUI->SetText(L"");
		InsertUI(m_pHPUI);

		m_pMPUI = new CTextUI();
		m_pMPUI->SetFontHeight(17);
		m_pMPUI->SetPosition({ 238.0f, 570.0f });
		m_pMPUI->SetSize({ 10, 10 });
		m_pMPUI->SetFontColor(RGB(200, 200, 200));
		m_pMPUI->SetText(L"");
		InsertUI(m_pMPUI);

		m_pNameUI = new CTextUI();
		m_pNameUI->SetFontHeight(17);
		m_pNameUI->SetPosition({ 350.0f, 495.0f });
		m_pNameUI->SetSize({ 10, 10 });
		m_pNameUI->SetFontColor(RGB(200, 200, 200));
		m_pNameUI->SetText(L"");
		InsertUI(m_pNameUI);

		m_pRankUI = new CTextUI();
		m_pRankUI->SetFontHeight(17);
		m_pRankUI->SetPosition({ 350.0f, 518.0f });
		m_pRankUI->SetSize({ 10, 10 });
		m_pRankUI->SetFontColor(RGB(200, 200, 200));
		m_pRankUI->SetText(L"");
		InsertUI(m_pRankUI);

		m_pPortraitUI = new CAnimationUI();
		m_pPortraitUI->SetPosition({ 555.0f, 550.0f });
		m_pPortraitUI->SetSize({ 60, 56 });
		m_pPortraitUI->SetAnimation(nullptr);
		InsertUI(m_pPortraitUI);
	}

	{
		m_pEmptyProgressBarUI = new CSpriteUI();
		m_pEmptyProgressBarUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"PrgrsBarEmpty"));
		m_pEmptyProgressBarUI->SetPosition({ 418.0f, 538.0f });
		m_pEmptyProgressBarUI->SetSize({ 44, 44 });
		m_pEmptyProgressBarUI->SetGdiRender(true);
		m_pEmptyProgressBarUI->SetUIActive(false);
		InsertUI(m_pEmptyProgressBarUI);

		m_pFullProgressBarUI = new CSpriteUI();
		m_pFullProgressBarUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"PrgrsBarFull"));
		m_pFullProgressBarUI->SetPosition({ 418.0f, 538.0f });
		m_pFullProgressBarUI->SetSize({ 44, 44 });
		m_pFullProgressBarUI->SetGdiRender(true);
		m_pFullProgressBarUI->SetUIActive(false);
		InsertUI(m_pFullProgressBarUI);
	}

	{
		m_pBuildingTextUI = new CTextUI();
		m_pBuildingTextUI->SetFontHeight(17);
		m_pBuildingTextUI->SetPosition({ 400.0f, 514.0f });
		m_pBuildingTextUI->SetSize({ 10, 10 });
		m_pBuildingTextUI->SetFontColor(RGB(200, 200, 200));
		m_pBuildingTextUI->SetText(L"");
		m_pBuildingTextUI->SetUIActive(false);
		InsertUI(m_pBuildingTextUI);

		m_pBuildingQueueUI = new CSpriteUI();
		m_pBuildingQueueUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"BuildQue"));
		m_pBuildingQueueUI->SetPosition({ 394.0f, 544.0f });
		m_pBuildingQueueUI->SetSize({ 70, 70 });
		m_pBuildingQueueUI->SetGdiRender(true);
		m_pBuildingQueueUI->SetUIActive(false);
		InsertUI(m_pBuildingQueueUI);

		m_pBuildingUnit[0] = new CSpriteUI();
		m_pBuildingUnit[0]->SetPosition({ 320.0f, 520.0f });
		m_pBuildingUnit[0]->SetSize({ 40, 40 });
		m_pBuildingUnit[0]->SetGdiRender(false);
		m_pBuildingUnit[0]->SetSprite(nullptr);
		m_pBuildingUnit[0]->SetUIActive(false);
		InsertUI(m_pBuildingUnit[0]);

		m_pBuildingUnit[1] = new CSpriteUI();
		m_pBuildingUnit[1]->SetPosition({ 320.0f, 568.0f });
		m_pBuildingUnit[1]->SetSize({ 40, 40 });
		m_pBuildingUnit[1]->SetGdiRender(false);
		m_pBuildingUnit[1]->SetSprite(nullptr);
		m_pBuildingUnit[1]->SetUIActive(false);
		InsertUI(m_pBuildingUnit[1]);

		m_pBuildingUnit[2] = new CSpriteUI();
		m_pBuildingUnit[2]->SetPosition({ 369.0f, 568.0f });
		m_pBuildingUnit[2]->SetSize({ 40, 40 });
		m_pBuildingUnit[2]->SetGdiRender(false);
		m_pBuildingUnit[2]->SetSprite(nullptr);
		m_pBuildingUnit[2]->SetUIActive(false);
		InsertUI(m_pBuildingUnit[2]);

		m_pBuildingUnit[3] = new CSpriteUI();
		m_pBuildingUnit[3]->SetPosition({ 418.0f, 568.0f });
		m_pBuildingUnit[3]->SetSize({ 40, 40 });
		m_pBuildingUnit[3]->SetGdiRender(false);
		m_pBuildingUnit[3]->SetSprite(nullptr);
		m_pBuildingUnit[3]->SetUIActive(false);
		InsertUI(m_pBuildingUnit[3]);

		m_pBuildingUnit[4] = new CSpriteUI();
		m_pBuildingUnit[4]->SetPosition({ 467.0f, 568.0f });
		m_pBuildingUnit[4]->SetSize({ 40, 40 });
		m_pBuildingUnit[4]->SetGdiRender(false);
		m_pBuildingUnit[4]->SetSprite(nullptr);
		m_pBuildingUnit[4]->SetUIActive(false);
		InsertUI(m_pBuildingUnit[4]);
	}

	{
		m_pUpgradeQueueUI = new CSpriteUI();
		m_pUpgradeQueueUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"UpgrdBx"));
		m_pUpgradeQueueUI->SetPosition({ 320.0f, 520.0f });
		m_pUpgradeQueueUI->SetSize({ 44, 44 });
		m_pUpgradeQueueUI->SetGdiRender(true);
		m_pUpgradeQueueUI->SetUIActive(false);
		InsertUI(m_pUpgradeQueueUI);

		m_pUpgradeUI = new CSpriteUI();
		m_pUpgradeUI->SetPosition({ 319.0f, 522.0f });
		m_pUpgradeUI->SetSize({ 44, 44 });
		m_pUpgradeUI->SetGdiRender(true);
		m_pUpgradeUI->SetSprite(nullptr);
		m_pUpgradeUI->SetUIActive(false);
		InsertUI(m_pUpgradeUI);
	}
}

void CSUnitProfileWidget::Update()
{
	CWidget::Update();

	vector<CTerranObject*> vecSelectedObjects = CGameManager::GetManager()->GetSelectedObjects();
	if (vecSelectedObjects.size() == 0 || 1 < vecSelectedObjects.size()) { SetWidgetActive(false); return; }

	CTerranObject* pTerranObject = vecSelectedObjects.front();
	if (pTerranObject->GetDead())
	{
		SetWidgetActive(false);
		return;
	}

	
	// 싱글 유닛 위젯을 켭니다.
	SetWidgetActive(true);
	
	switch (pTerranObject->GetTerranObjectType())
	{
	case ETerranObjectType::GROUND_UNIT:
	case ETerranObjectType::AIR_UNIT:
	{
		CUnit* pUnit = dynamic_cast<CUnit*>(pTerranObject);
		CUnitProperty& unitProperty = pUnit->GetUnitProperty();

		
		SetBigWireSprite(pUnit->GetCurBigWireframeSprite());
		SetHPText(to_wstring(pUnit->GetCurHP()) + L" / " + to_wstring(unitProperty.GetMaxHP()));

		if (unitProperty.GetMaxMP() == 0)
		{
			m_pMPUI->SetUIActive(false);
		}
		else
		{
			SetMPText(to_wstring(pUnit->GetCurMP()) + L" / " + to_wstring(unitProperty.GetMaxMP()));
		}

		m_pHPUI->SetPosition({ 230.0f, 560.0f });
		m_pMPUI->SetPosition({ 226.0f, 575.0f });

		SetHPTextColor(pUnit->GetCurHPColor());
		SetNameText(unitProperty.GetName());
		SetRankText(unitProperty.GetStrRank());
		SetPortraitAnim(pUnit->GetPortraitAnim());

		m_pBuildingTextUI->SetUIActive(false);
		m_pEmptyProgressBarUI->SetUIActive(false);
		m_pFullProgressBarUI->SetUIActive(false);
		m_pBuildingQueueUI->SetUIActive(false);
		for (int32 i = 0; i < 5; ++i) { m_pBuildingUnit[i]->SetUIActive(false); }
		m_pUpgradeQueueUI->SetUIActive(false);
		m_pUpgradeUI->SetUIActive(false);
	}
	break;

	case ETerranObjectType::BUILDING:
	{
		CBuilding* pBuilding = dynamic_cast<CBuilding*>(pTerranObject);
		CBuildingProperty& buildingProperty = pBuilding->GetBuildingProperty();

		SetBigWireSprite(pBuilding->GetCurBigWireframeSprite());
		SetHPText(to_wstring(pBuilding->GetCurHP()) + L" / " + to_wstring(buildingProperty.GetMaxHP()));
		
		m_pHPUI->SetPosition({ 215.0f, 565.0f });

		SetHPTextColor(pBuilding->GetCurHPColor());
		SetNameText(buildingProperty.GetName());
		SetRankText(L"");
		SetPortraitAnim(pBuilding->GetPortraitAnim());

		m_pMPUI->SetUIActive(false);
		m_pBuildingTextUI->SetUIActive(false);
		m_pEmptyProgressBarUI->SetUIActive(false);
		m_pFullProgressBarUI->SetUIActive(false);
		m_pBuildingQueueUI->SetUIActive(false);
		for (int32 i = 0; i < 5; ++i) { m_pBuildingUnit[i]->SetUIActive(false); }
		m_pUpgradeQueueUI->SetUIActive(false);
		m_pUpgradeUI->SetUIActive(false);

		// 업그레이드 중일 때
		VerifyUpgrade(pBuilding);

		// 생산 중일 때
		VerifyBuildingUnit(pBuilding);
	}
	break;
	}
}

void CSUnitProfileWidget::LateUpdate()
{
	CWidget::LateUpdate();
}

void CSUnitProfileWidget::Render(HDC _hDC)
{
	CWidget::Render(_hDC);
}

void CSUnitProfileWidget::Release()
{
	CWidget::Release();
}


void CSUnitProfileWidget::VerifyBuildingUnit(CBuilding* _pBuilding)
{
	std::deque<ETerranUnitType>& deqBuildingQueue = _pBuilding->GetBuildingUnitsQueue();

	if (deqBuildingQueue.empty())
	{
		return;
	}

	m_pBuildingTextUI->SetUIActive(true);
	m_pBuildingTextUI->SetText(L"Building");

	m_pEmptyProgressBarUI->SetUIActive(true);
	m_pFullProgressBarUI->SetUIActive(true);
	m_pBuildingQueueUI->SetUIActive(true);

	for (uint32 i = 0; i < deqBuildingQueue.size(); ++i)
	{
		m_pBuildingUnit[i]->SetUIActive(true);

		switch (deqBuildingQueue[i])
		{
		case ETerranUnitType::SCV:				m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdSCVBuild")); break;
		case ETerranUnitType::MARINE:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdMrnBuild")); break;
		case ETerranUnitType::FIREBAT:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdFrbtBuild")); break;
		case ETerranUnitType::MEDIC:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdMdcBuild")); break;
		case ETerranUnitType::GHOST:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdGhstBuild")); break;
		case ETerranUnitType::VULTURE:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdVltrBuild")); break;
		case ETerranUnitType::TANK:				m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdTnkBuild")); break;
		case ETerranUnitType::GOLIATH:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdGlthBuild")); break;
		// case ETerranUnitType::WRAITH:			m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"")); break;
		case ETerranUnitType::SCIENCE_VESSEL:	m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdScncVslBuild")); break;
		case ETerranUnitType::BATTLE_CRUISER:	m_pBuildingUnit[i]->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdBtlcrsrBuild")); break;
		default: break;
		}
	}

	for (int32 i = deqBuildingQueue.size(); i < 5; ++i)
	{
		m_pBuildingUnit[i]->SetUIActive(false);
		m_pBuildingUnit[i]->SetSprite(nullptr);
	}
}

void CSUnitProfileWidget::VerifyUpgrade(CBuilding* _pBuilding)
{
	if (_pBuilding->GetUpgradesQueue().empty()) { return; }
	std::deque<ETerranUpgradeType>& deqUpgradeQueue = _pBuilding->GetUpgradesQueue();

	if (deqUpgradeQueue.empty())
	{
		return;
	}

	m_pBuildingTextUI->SetUIActive(true);
	m_pBuildingTextUI->SetText(L"Upgrading");
	m_pEmptyProgressBarUI->SetUIActive(true);
	m_pFullProgressBarUI->SetUIActive(true);
	m_pUpgradeQueueUI->SetUIActive(true);
	m_pUpgradeUI->SetUIActive(true);

	ETerranUpgradeType eTerranUpgradeType = deqUpgradeQueue.front();
	switch (eTerranUpgradeType)
	{
	case ETerranUpgradeType::INFANTRY_WEAPONS_1:
	case ETerranUpgradeType::INFANTRY_WEAPONS_2:
	case ETerranUpgradeType::INFANTRY_WEAPONS_3:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdUpInftyWpnUpgrade"));
		break;

	case ETerranUpgradeType::INFANTRY_ARMOR_1:
	case ETerranUpgradeType::INFANTRY_ARMOR_2:
	case ETerranUpgradeType::INFANTRY_ARMOR_3:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdUpInftyArmrUpgrade"));
		break;

	case ETerranUpgradeType::U238_SHELLS:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdU238Upgrade"));
		break;

	case ETerranUpgradeType::STIMPACK_TECH:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdStmpckUpgrade"));
		break;

	case ETerranUpgradeType::RESTORATION:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::OPTICAL_FLARE:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::CADUCEUS_REACTOR:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::VIHICLE_WEAPONS_1:
	case ETerranUpgradeType::VIHICLE_WEAPONS_2:
	case ETerranUpgradeType::VIHICLE_WEAPONS_3:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdUpVhclWpnUpgrade"));
		break;

	case ETerranUpgradeType::VIHICLE_PLATING_1:
	case ETerranUpgradeType::VIHICLE_PLATING_2:
	case ETerranUpgradeType::VIHICLE_PLATING_3:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdUpVhclPltngUpgrade"));
		break;

	case ETerranUpgradeType::SHIP_WEAPONS:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::SHIP_PLATING:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::ION_THRUSTERS:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdUpIonKlstrUpgrade"));
		break;

	case ETerranUpgradeType::SPIDER_MINES:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::SIEGE_TECH:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkUpgrade"));
		break;

	case ETerranUpgradeType::CHARON_BOOSTERS:
		//m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite());
		break;

	case ETerranUpgradeType::IRRADIATE:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdIrdtUpgrade"));
		break;

	case ETerranUpgradeType::YAMATO_CANNON:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdYmtUpgrade"));
		break;

	case ETerranUpgradeType::ARM_NUCLEAR_SILO:
		m_pUpgradeUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"CmdArmNclrSloUpgrade"));
		break;

	default:
	break;
	}
}


void CSUnitProfileWidget::SetBigWireSprite(CSprite* _pBigWireSprite) { m_pBigWireUI->SetSprite(_pBigWireSprite); }

void CSUnitProfileWidget::SetHPText(std::wstring _strCurHP) { m_pHPUI->SetText(_strCurHP); }

void CSUnitProfileWidget::SetHPTextColor(int32 _iColor) { m_pHPUI->SetFontColor(_iColor); }

void CSUnitProfileWidget::SetMPText(std::wstring _strMP) { m_pMPUI->SetText(_strMP); }

void CSUnitProfileWidget::SetMPTextColor(int32 _iColor) { m_pMPUI->SetFontColor(_iColor); }

void CSUnitProfileWidget::SetNameText(std::wstring _strName) { m_pNameUI->SetText(_strName); }

void CSUnitProfileWidget::SetRankText(std::wstring _strRank) { m_pRankUI->SetText(_strRank); }

void CSUnitProfileWidget::SetBuildingText(std::wstring _pBuildingTextUI) { m_pBuildingTextUI->SetText(_pBuildingTextUI); }

void CSUnitProfileWidget::SetPortraitAnim(CAnimation* _pPortraitAnim) { m_pPortraitUI->SetAnimation(_pPortraitAnim); }