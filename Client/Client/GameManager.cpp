#include "pch.h"
#include "GameManager.h"

#include "TerranObject.h"
#include "Unit.h"
#include "Command.h"
using namespace std;

CGameManager* CGameManager::s_pGameManager = nullptr;

void CGameManager::Initialize()
{

}

void CGameManager::Update()
{
	for (auto iter = m_vecSelectedObjects.begin(); iter != m_vecSelectedObjects.end();)
	{
		if ((*iter)->GetDead())
		{
			// (*iter)->Release(); 여기서 오브젝트에 붙은 컴포넌트를 해제해야 할까?
			(*iter)->SetSelected(false);
			iter = m_vecSelectedObjects.erase(iter);
		}
		else
		{
			(*iter)->SetSelected(true);
			++iter;
		}
	}
}

void CGameManager::LateUpdate()
{

}

void CGameManager::Release()
{
	VERIFY_NULLPTR(s_pGameManager);
	SAFE_DELETE(s_pGameManager);
}

void CGameManager::ClearSelectedObject()
{
	for (const auto& pTerranObject : m_vecSelectedObjects)
	{
		pTerranObject->SetSelected(false);
	}
	m_vecSelectedObjects.clear();
}

void CGameManager::SendCommand(ECommandType _eCommandType)
{
	for (const auto& pTerranObject : m_vecSelectedObjects)
	{
		VERIFY_NULLPTR(pTerranObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }
		
		CCommand* pCmd = nullptr;
		switch (_eCommandType)
		{
		case ECommandType::STOP:			pCmd = new CStop(_eCommandType);			break;
		case ECommandType::GO_BACK:			pCmd = new CGoBack(_eCommandType);			break;
		case ECommandType::CANCEL:			pCmd = new CCancel(_eCommandType);			break;
		case ECommandType::CANCEL_LAST:		pCmd = new CCancelLast(_eCommandType);		break;
		case ECommandType::CANCEL_UPGRADE:	pCmd = new CCancelUpgrade(_eCommandType);	break;
		//case ECommandType::HOLD_POSITION:	pCmd = new CHoldPosition(_eCommandType);	break;
		case ECommandType::USE_STIMPACK:	pCmd = new CUseStimpack(_eCommandType);		break;
		case ECommandType::SIEGE_MODE:		pCmd = new CSiegeMode(_eCommandType);		break;
		case ECommandType::TANK_MODE:		pCmd = new CTankMode(_eCommandType);		break;
		
		case ECommandType::UPGRADE_INFANTRY_WEAPONS:
		case ECommandType::UPGRADE_INFANTRY_ARMOR:

		case ECommandType::UPGRADE_U238_SHELLS:
		case ECommandType::UPGRADE_STIMPACK_TECH:

		case ECommandType::UPGRADE_ION_THRUSTERS:
		case ECommandType::UPGRADE_SIEGE_TECH:

		case ECommandType::UPGRADE_VIHICLE_WEAPONS:
		case ECommandType::UPGRADE_VIHICLE_PLATING:

		case ECommandType::UPGRADE_IRRADIATE:
		case ECommandType::UPGRADE_YAMATO_CANNON:
		case ECommandType::ARM_NUCLEAR_SILO:	pCmd = new CUpgrade(_eCommandType);	break;
		
		case ECommandType::BUILD_SCV:
		case ECommandType::BUILD_MARINE:
		case ECommandType::BUILD_FIREBAT:
		case ECommandType::BUILD_MEDIC:
		case ECommandType::BUILD_GHOST:
		case ECommandType::BUILD_VULTURE:
		case ECommandType::BUILD_SIEGE_TANK:
		case ECommandType::BUILD_GOLIATH:
		case ECommandType::BUILD_SCIENCE_VESSEL:
		case ECommandType::BUILD_BATTLECRUISER:		pCmd = new CBuild(_eCommandType);	break;
		default: break;
		}

		pTerranObject->PushCommandQueue(pCmd);
	}
}

void CGameManager::SendCommand(ECommandType _eCommandType, CTerranObject* _pTargetObject)
{
	for (const auto& pTerranObject : m_vecSelectedObjects)
	{
		VERIFY_NULLPTR(pTerranObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		CCommand* pCmd = nullptr;
		switch (_eCommandType)
		{
		case ECommandType::USE_DEFENSIVE_MATRIX:
		case ECommandType::USE_IRRADIATE:
		case ECommandType::USE_YAMATO_CANNON:
		{
			pCmd = new CSkill(_eCommandType, _pTargetObject);
		}
		break;

		default:
		break;
		}
		pTerranObject->PushCommandQueue(pCmd);
	}
}

void CGameManager::SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition)
{
	for (const auto& pTerranObject : m_vecSelectedObjects)
	{
		VERIFY_NULLPTR(pTerranObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		CCommand* pCmd = nullptr;
		switch (_eCommandType)
		{
		case ECommandType::MOVE:					pCmd = new CMove(_eCommandType, _tDstTile, _tDstPosition);		break;
		// case ECommandType::PATROL: break;
		// case ECommandType::SPIDER_MINE: break;
		case ECommandType::SET_RALLY_POINT:			pCmd = new CRallyPoint(_eCommandType, _tDstTile, _tDstPosition);break;
		// case ECommandType::LAND: break;
		case ECommandType::BUILD_COMMAND_CENTER:
		case ECommandType::BUILD_SUPPLY_DEPOT:
		case ECommandType::BUILD_REFINERY:
		case ECommandType::BUILD_ENGINEERING_BAY:
		case ECommandType::BUILD_BARRACKS:
		case ECommandType::BUILD_ACADEMY:
		case ECommandType::BUILD_FACTORY:
		case ECommandType::BUILD_ARMORY:
		case ECommandType::BUILD_STARPORT:
		case ECommandType::BUILD_SCIENCE_FACILITY:
		case ECommandType::BUILD_MACHINE_SHOP:
		case ECommandType::BUILD_CONTROL_TOWER:
		case ECommandType::BUILD_PHYSICS_LAB:
		case ECommandType::BUILD_COVERT_OPS:
		case ECommandType::BUILD_NUCLEAR_SILO:		pCmd = new CConstruct(_eCommandType, _tDstTile, _tDstPosition);	break;
		default: break;
		}
		pTerranObject->PushCommandQueue(pCmd);
	}
}

void CGameManager::SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTargetObject)
{
	for (const auto& pTerranObject : m_vecSelectedObjects)
	{
		VERIFY_NULLPTR(pTerranObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		CCommand* pCmd = nullptr;
		switch (_eCommandType)
		{
		case ECommandType::MOVE:	pCmd = new CMove(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);		break;
		case ECommandType::ATTACK:	pCmd = new CAttack(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);	break;
		case ECommandType::GATHER:	pCmd = new CGather(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);	break;
		case ECommandType::USE_NUCLEAR_STRIKE:	pCmd = new CSkill(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);	break;
		default: break;
		}
		pTerranObject->PushCommandQueue(pCmd);
	}
}
