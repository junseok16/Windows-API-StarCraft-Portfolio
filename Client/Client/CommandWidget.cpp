#include "pch.h"
#include "CommandWidget.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"
#include "Cursor.h"
#include "TerranObject.h"
#include "Unit.h"
#include "Building.h"

#include "ButtonUI.h"
#include "UnitProperty.h"

#include "MoveCmdButton.h"
#include "StopCmdButton.h"
#include "AttackCmdButton.h"
#include "RlyPntCmdButton.h"
#include "GatherCmdButton.h"

#include "BscStrctrCmdButton.h"
#include "AdvStrctrCmdButton.h"
#include "GoBackCmdButton.h"

#include "CancelCmdButton.h"
#include "CancelLastCmdButton.h"
#include "CancelUpgradeCmdButton.h"

#include "SCVCmdButton.h"
#include "MarineCmdButton.h"
#include "FirebatCmdButton.h"
#include "MedicCmdButton.h"
#include "GhostCmdButton.h"

#include "VultureCmdButton.h"
#include "SiegeTankCmdButton.h"
#include "GoliathCmdButton.h"

#include "ScncVslCmdButton.h"
#include "BtlcrsrCmdButton.h"

#include "CmndCntrCmdButton.h"
#include "SplyDptCmdButton.h"
#include "RfnryCmdButton.h"
#include "BrcksCmdButton.h"
#include "EngnrByCmdButton.h"
#include "AcdmyCmdButton.h"

#include "FctryCmdButton.h"
#include "StrprtCmdButton.h"
#include "ScncFcltyCmdButton.h"
#include "ArmryCmdButton.h"

#include "CmstStnCmdButton.h"
#include "NclrSloCmdButton.h"
#include "MchnShpCmdButton.h"
#include "CntrlTwrCmdButton.h"
#include "CvrtOpsCmdButton.h"
#include "PhyscLbCmdButton.h"

#include "UseStmPackCmdButton.h"
#include "UseHealCmdButton.h"
#include "UseDfnsvMtrxCmdButton.h"
#include "UseIrdtCmdButton.h"
#include "UseYamatoCmdButton.h"

#include "UseDfnsvMtrxCmdButton.h"
#include "UseIrdtCmdButton.h"
#include "UseYamatoCmdButton.h"
#include "UseNclrStrkCmdButton.h"

#include "SgMdCmdButton.h"
#include "TnkMdCmdButton.h"

#include "UpInfWpnCmdButton.h"
#include "UpInfArmrCmdButton.h"

#include "UpVhclWpnCmdButton.h"
#include "UpVhclPltngCmdButton.h"

#include "UpU238CmdButton.h"
#include "UpStmpckCmdButton.h"
#include "UpIonThrstrCmdButton.h"
#include "UpSgMdCmdButton.h"

#include "UpYamatoCmdButton.h"
#include "UpIrdtCmdButton.h"

#include "ArmNukeCmdButton.h"
using namespace std;

void CCommandWidget::Initialize()
{
	// 이동 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::MOVE] = new CMoveCmdButton();
		m_pCmdButtons[(int32)ECommandType::MOVE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdMoveRelease"));
		m_pCmdButtons[(int32)ECommandType::MOVE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdMovePress"));
		m_pCmdButtons[(int32)ECommandType::MOVE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdMoveDisable"));
		m_pCmdButtons[(int32)ECommandType::MOVE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::MOVE]);
	}

	// 정지 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::STOP] = new CStopCmdButton();
		m_pCmdButtons[(int32)ECommandType::STOP]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdStopRelease"));
		m_pCmdButtons[(int32)ECommandType::STOP]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdStopPress"));
		m_pCmdButtons[(int32)ECommandType::STOP]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdStopDisable"));
		m_pCmdButtons[(int32)ECommandType::STOP]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::STOP]);
	}

	// 공격 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::ATTACK] = new CAttackCmdButton();
		m_pCmdButtons[(int32)ECommandType::ATTACK]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdAtckRelease"));
		m_pCmdButtons[(int32)ECommandType::ATTACK]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdAtckPress"));
		m_pCmdButtons[(int32)ECommandType::ATTACK]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdAtckDisable"));
		m_pCmdButtons[(int32)ECommandType::ATTACK]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::ATTACK]);
	}
	
	// 기본 건물 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE] = new CBscStrctrCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdBscStrctrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdBscStrctrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdBscStrctrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_BASIC_STRUCTURE]);
	}

	// 응용 건물 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE] = new CAdvStrctrCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdAdvcdStrctrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdAdvcdStrctrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdAdvcdStrctrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_ADVANCED_STRUCTURE]);
	}

	// 채집 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::GATHER] = new CGatherCmdButton();
		m_pCmdButtons[(int32)ECommandType::GATHER]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdGthrRelease"));
		m_pCmdButtons[(int32)ECommandType::GATHER]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdGthrPress"));
		m_pCmdButtons[(int32)ECommandType::GATHER]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdGthrDisable"));
		m_pCmdButtons[(int32)ECommandType::GATHER]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::GATHER]);
	}

	// 랠리 포인트 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT] = new CRlyPntCmdButton();
		m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdRllyPntRelease"));
		m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdRllyPntPress"));
		m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdRllyPntDisable"));
		m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::SET_RALLY_POINT]);
	}

	// SCV 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_SCV] = new CSCVCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_SCV]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite (L"CmdSCVRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCV]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite	(L"CmdSCVPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCV]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdSCVDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCV]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_SCV]);
	}

	// 마린 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_MARINE] = new CMarineCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_MARINE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdMrnRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MARINE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdMrnPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MARINE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdMrnDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MARINE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_MARINE]);
	}
	
	// 파이어뱃 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT] = new CFirebatCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdFrbtRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdFrbtPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdFrbtDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_FIREBAT]);
	}

	// 메딕 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC] = new CMedicCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdMdcRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdMdcPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdMdcDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_MEDIC]);
	}

	// 고스트 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_GHOST] = new CGhostCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_GHOST]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdGhstRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GHOST]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdGhstPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GHOST]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdGhstDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GHOST]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_GHOST]);
	}
	
	/*******************************************************************************************************************************/

	// 벌쳐 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE] = new CVultureCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdVltrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdVltrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdVltrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_VULTURE]);
	}

	// 탱크 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK] = new CSiegeTankCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdTnkRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdTnkPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdTnkDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_SIEGE_TANK]);
	}

	// 골리앗 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH] = new CGoliathCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdGlthRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdGlthPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdGlthDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_GOLIATH]);
	}

	/*******************************************************************************************************************************/

	// 사이언스 배슬 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL] = new CScncVslCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdScncVslRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdScncVslPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdScncVslDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_VESSEL]);
	}

	// 배틀쿠르저 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER] = new CBtlcrsrCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdBtlcrsrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdBtlcrsrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdBtlcrsrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_BATTLECRUISER]);
	}

	/*******************************************************************************************************************************/

	// cancel
	// cancel last
	// cancel upgrade
	// cancel construction
	// halt construction
	
	// 뒤로가기 아이콘(go back)
	{
		m_pCmdButtons[(int32)ECommandType::GO_BACK] = new CGoBackCmdButton();
		m_pCmdButtons[(int32)ECommandType::GO_BACK]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCnclRelease"));
		m_pCmdButtons[(int32)ECommandType::GO_BACK]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCnclPress"));
		m_pCmdButtons[(int32)ECommandType::GO_BACK]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCnclDisable"));
		m_pCmdButtons[(int32)ECommandType::GO_BACK]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::GO_BACK]);
	}

	// 스킬 취소 아이콘(cancel)
	{
		m_pCmdButtons[(int32)ECommandType::CANCEL] = new CCancelCmdButton();
		m_pCmdButtons[(int32)ECommandType::CANCEL]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCnclRelease"));
		m_pCmdButtons[(int32)ECommandType::CANCEL]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCnclPress"));
		m_pCmdButtons[(int32)ECommandType::CANCEL]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCnclDisable"));
		m_pCmdButtons[(int32)ECommandType::CANCEL]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::CANCEL]);
	}

	// 생산 취소 아이콘(cancel last)
	{
		m_pCmdButtons[(int32)ECommandType::CANCEL_LAST] = new CCancelLastCmdButton();
		m_pCmdButtons[(int32)ECommandType::CANCEL_LAST]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCnclRelease"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_LAST]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCnclPress"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_LAST]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCnclDisable"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_LAST]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::CANCEL_LAST]);
	}

	// 업그레이드 취소 아이콘(cancel upgrade)
	{
		m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE] = new CCancelUpgradeCmdButton();
		m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCnclRelease"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCnclPress"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCnclDisable"));
		m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::CANCEL_UPGRADE]);
	}

	// 커맨드 센터 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER] = new CCmndCntrCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite	(L"CmdCmndCntrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite	(L"CmdCmndCntrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite	(L"CmdCmndCntrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_COMMAND_CENTER]);
	}

	// 서플라이 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT] = new CSplyDptCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdSplyDptRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite	(L"CmdSplyDptPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdSplyDptDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_SUPPLY_DEPOT]);
	}

	// 리파이너리 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY] = new CRfnryCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdRfnryRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdRfnryPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdRfnryDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_REFINERY]);
	}

	// 배럭 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS] = new CBrcksCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdBrcksRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdBrcksPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdBrcksDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_BARRACKS]);
	}

	// 엔지니어링 베이 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY] = new CEngnrByCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdEngnrByRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdEngnrByPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdEngnrByDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_ENGINEERING_BAY]);
	}

	// 아카데미 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY] = new CAcdmyCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdAcdmyRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdAcdmyPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdAcdmyDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_ACADEMY]);
	}
	
	/*******************************************************************************************************************************/

	// 팩토리 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY] = new CFctryCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdFctryRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdFctryPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdFctryDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_FACTORY]);
	}

	// 스타포트 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT] = new CStrprtCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdStrprtRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdStrprtPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdStrprtDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_STARPORT]);
	}

	// 사이언스 퍼실리티 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY] = new CScncFcltyCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdScencFcltyRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdScencFcltyPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdScencFcltyDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_SCIENCE_FACILITY]);
	}

	// 아머리 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY] = new CArmryCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdArmryRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdArmryPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdArmryDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_ARMORY]);
	}

	/*********************************************************************************************************/
	
	// 콤셋 스테이션 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION] = new CCmstStnCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCmstStnRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCmstStnPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCmstStnDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_COMSAT_STATION]);
	}

	// 뉴클리어 사일로 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO] = new CNclrSloCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdNclrSloRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdNclrSloPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdNclrSloDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_NUCLEAR_SILO]);
	}

	// 머신샵 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP] = new CMchnShpCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdMchnShpRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdMchnShpPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdMchnShpDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_MACHINE_SHOP]);
	}

	// 컨트롤 타워 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER] = new CCntrlTwrCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCntrlTwrRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCntrlTwrPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCntrlTwrDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_CONTROL_TOWER]);
	}

	// 코버트 옵스 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS] = new CCvrtOpsCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdCvrtOpsRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdCvrtOpsPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdCvrtOpsDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_COVERT_OPS]);
	}

	// 피직스 랩 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB] = new CPhyscLbCmdButton();
		m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdPhyscLbRelease"));
		m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdPhyscLbPress"));
		m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdPhyscLbDisable"));
		m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::BUILD_PHYSICS_LAB]);
	}

	/*********************************************************************************************************/

	// 스팀팩 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::USE_STIMPACK] = new CUseStmPackCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_STIMPACK]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdStmpckRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_STIMPACK]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdStmpckPress"));
		m_pCmdButtons[(int32)ECommandType::USE_STIMPACK]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdStmpckDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_STIMPACK]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_STIMPACK]);
	}

	// 힐 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::USE_HEAL] = new CUseHealCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_HEAL]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdHealRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_HEAL]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdHealPress"));
		m_pCmdButtons[(int32)ECommandType::USE_HEAL]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdHealDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_HEAL]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_HEAL]);
	}

	// 시즈 모드 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::SIEGE_MODE] = new CSgMdCmdButton();
		m_pCmdButtons[(int32)ECommandType::SIEGE_MODE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkRelease"));
		m_pCmdButtons[(int32)ECommandType::SIEGE_MODE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkPress"));
		m_pCmdButtons[(int32)ECommandType::SIEGE_MODE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkDisable"));
		m_pCmdButtons[(int32)ECommandType::SIEGE_MODE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::SIEGE_MODE]);
	}

	// 탱크 모드 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::TANK_MODE] = new CTnkMdCmdButton();
		m_pCmdButtons[(int32)ECommandType::TANK_MODE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdTnkRelease"));
		m_pCmdButtons[(int32)ECommandType::TANK_MODE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdTnkPress"));
		m_pCmdButtons[(int32)ECommandType::TANK_MODE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdTnkDisable"));
		m_pCmdButtons[(int32)ECommandType::TANK_MODE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::TANK_MODE]);
	}

	// 디펜시브 매트릭스 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX] = new CUseDfnsvMtrxCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdDfnsvMtrxRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdDfnsvMtrxPress"));
		m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdDfnsvMtrxDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_DEFENSIVE_MATRIX]);
	}

	// 이레디에이트 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE] = new CUseIrdtCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdIrdtRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdIrdtPress"));
		m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdIrdtDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_IRRADIATE]);
	}

	// 야마토포 사용 아이콘
	{
		m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON] = new CUseYamatoCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdYmtRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdYmtPress"));
		m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdYmtDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_YAMATO_CANNON]);
	}

	/*********************************************************************************************************/

	// 보병 공격력 업그레이드
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS] = new CUpInfWpnCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyWpnRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyWpnPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyWpnDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_WEAPONS]);
	}

	// 보병 방어력 업그레이드
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR] = new CUpInfArmrCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyArmrRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyArmrPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdUpInftyArmrDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_INFANTRY_ARMOR]);
	}

	// U-238 탄환 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS] = new CUpU238CmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdU238Release"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdU238Press"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdU238Disable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_U238_SHELLS]);
	}

	// 스팀팩 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH] = new CUpStmpckCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdStmpckRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdStmpckPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdStmpckDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_STIMPACK_TECH]);
	}

	// 이온 클러스터 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS] = new CUpIonThrstrCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdUpIonKlstrRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdUpIonKlstrPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdUpIonKlstrDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_ION_THRUSTERS]);
	}

	// 시즈 모드 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH] = new CUpSgMdCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdSiegeTnkDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_SIEGE_TECH]);
	}

	// 차량 공격력 업그레이드
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS] = new CUpVhclWpnCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclWpnRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclWpnPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclWpnDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_WEAPONS]);
	}

	// 차량 방어력 업그레이드
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING] = new CUpVhclPltngCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclPltngRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclPltngPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdUpVhclPltngDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_VIHICLE_PLATING]);
	}

	// 이레디에이트 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE] = new CUpIrdtCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdIrdtRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdIrdtPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdIrdtDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_IRRADIATE]);
	}

	// 야마토포 연구
	{
		m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON] = new CUpYamatoCmdButton();
		m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdYmtRelease"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON]->SetSpriteAt(EButtonState::PRESS, CResourceManager::GetManager()->GetSprite(L"CmdYmtPress"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdYmtDisable"));
		m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::UPGRADE_YAMATO_CANNON]);
	}

	// 뉴클리어 사일로 무장
	{
		m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO] = new CArmNukeCmdButton();
		m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdArmNclrSloRelease"));
		m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdArmNclrSloPress"));
		m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdArmNclrSloDisable"));
		m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::ARM_NUCLEAR_SILO]);
	}

	// 핵 공격
	{
		m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE] = new CUseNclrStrkCmdButton();
		m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE]->SetSpriteAt(EButtonState::RELEASE, CResourceManager::GetManager()->GetSprite(L"CmdNclrStrkRelease"));
		m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE]->SetSpriteAt(EButtonState::PRESS,   CResourceManager::GetManager()->GetSprite(L"CmdNclrStrkPress"));
		m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE]->SetSpriteAt(EButtonState::DISABLE, CResourceManager::GetManager()->GetSprite(L"CmdNclrStrkDisable"));
		m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE]->SetUIActive(false);
		InsertUI(m_pCmdButtons[(int32)ECommandType::USE_NUCLEAR_STRIKE]);
	}

	/*
	pButton00->SetPosition({ 655.0f, 470.0f });
	pButton01->SetPosition({ 712.0f, 470.0f });
	pButton02->SetPosition({ 769.0f, 470.0f });

	pButton10->SetPosition({ 655.0f, 520.0f });
	pButton11->SetPosition({ 712.0f, 520.0f });
	pButton12->SetPosition({ 769.0f, 520.0f });

	pButton20->SetPosition({ 655.0f, 570.0f });
	pButton21->SetPosition({ 712.0f, 570.0f });
	pButton22->SetPosition({ 769.0f, 570.0f });
	*/
	CWidget::Initialize();
}

void CCommandWidget::Update()
{
	CWidget::Update();

	vector<CTerranObject*>& vecSelectedObjects = CGameManager::GetManager()->GetSelectedObjects();

	// 명령 위젯을 끕니다.
	if (vecSelectedObjects.size() == 0)
	{
		SetWidgetActive(false);
		return;
	}

	// 명령 위젯을 켭니다.
	SetWidgetActive(true);

	// 한 오브젝트가 선택된 경우
	if (vecSelectedObjects.size() == 1)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(vecSelectedObjects.front());

		// 적 오브젝트인 경우, 위젯을 끕니다.
		if (pTerranObject->GetOwnerType() == EOwnerType::COMPUTER)
		{
			SetWidgetActive(false);
			return;
		}

		switch (pTerranObject->GetTerranObjectType())
		{
		case ETerranObjectType::GROUND_UNIT:
		case ETerranObjectType::AIR_UNIT:
		case ETerranObjectType::BUILDING:
		{
			// 모든 버튼을 비활성화합니다.
			for (uint32 i = 0; i < (int32)ECommandType::ENUM_END; ++i)
			{
				m_pCmdButtons[i]->SetUIActive(false);
			}

			vector<ECommandType>& vecCommandTypes = pTerranObject->GetCurCommandTypes();
			for (uint32 i = 0; i < vecCommandTypes.size(); ++i)
			{
				m_pCmdButtons[(int32)vecCommandTypes[i]]->SetUIActive(true);
			}
		}
		break;
		}
	}

	// 여러 오브젝트가 선택된 경우
	else if (1 < vecSelectedObjects.size())
	{
		// 모든 버튼을 비활성화합니다.
		for (uint32 i = 0; i < (int32)ECommandType::ENUM_END; ++i)
		{
			m_pCmdButtons[i]->SetUIActive(false);
		}

		int32 iMaxRank = -1;
		bool bIdentical = true;

		for (auto iter = vecSelectedObjects.begin(); iter != vecSelectedObjects.end(); iter++)
		{
			int32 iCurRank = dynamic_cast<CUnit*>(*iter)->GetUnitProperty().GetIntRank();

			if (iMaxRank == -1)
			{
				iMaxRank = iCurRank;
			}
			else if (iMaxRank < iCurRank)
			{
				iMaxRank = iCurRank;
				bIdentical = false;
				break;
			}
		}

		if (bIdentical)
		{
			CUnit* pUnit = dynamic_cast<CUnit*>(vecSelectedObjects.front());
			if (pUnit->GetTerranUnitType() == ETerranUnitType::SCV)
			{
				m_pCmdButtons[(int32)ECommandType::MOVE]->SetUIActive(true);
				m_pCmdButtons[(int32)ECommandType::STOP]->SetUIActive(true);
				m_pCmdButtons[(int32)ECommandType::ATTACK]->SetUIActive(true);
			}
			else
			{
				vector<ECommandType>& vecCommandTypes = pUnit->GetCurCommandTypes();
				for (uint32 i = 0; i < vecCommandTypes.size(); ++i)
				{
					m_pCmdButtons[(int32)vecCommandTypes[i]]->SetUIActive(true);
				}
			}
		}
		else
		{
			m_pCmdButtons[(int32)ECommandType::MOVE]->SetUIActive(true);
			m_pCmdButtons[(int32)ECommandType::STOP]->SetUIActive(true);
			m_pCmdButtons[(int32)ECommandType::ATTACK]->SetUIActive(true);
		}
	}
}

void CCommandWidget::LateUpdate()
{
	CWidget::LateUpdate();
}

void CCommandWidget::Render(HDC _hDC)
{
	CWidget::Render(_hDC);
}

void CCommandWidget::Release()
{
	CWidget::Release();
}
