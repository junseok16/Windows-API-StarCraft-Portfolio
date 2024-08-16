#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "MouseManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"

#include "ScrollComponent.h"
#include "TerranObject.h"
#include "Command.h"
using namespace std;

void CPlayer::Initialize()
{
	CObject::Initialize();
	
	// 부모 속성을 초기화합니다.
	SetPosition({ 400.0f, 300.0f });
	SetSize({ 10, 10 });
	SetObjectType(EObjectType::PLAYER);
	SetGdiRender(false);

	// 카메라 컴포넌트를 붙입니다.
	CScrollComponent* pScrollComponent = new CScrollComponent();
	pScrollComponent->SetComponentOwner(this);
	InsertComponent(pScrollComponent);
}

void CPlayer::Update()
{
	CObject::Update();
	UpdatePosition();
}

void CPlayer::LateUpdate()
{
	// 컴포넌트 업데이트
	CObject::LateUpdate();
	
	/*
	// 죽은 오브젝트를 선택한 오브젝트에서 없앱니다.
	for (auto iter = m_vecSelectedObjects.begin(); iter != m_vecSelectedObjects.end(); )
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(*iter);
		if (pTerranObject->GetDead())
		{
			// 이 오브젝트에 붙어있던 모든 컴포넌트를 삭제합니다.
			pTerranObject->Release();
			iter = m_vecSelectedObjects.erase(iter);
		}
		else
		{
			++iter;
		}
	}*/
}

void CPlayer::Render(HDC _hDC)
{
	CObject::Render(_hDC);

	// 플레이어 위치를 출력합니다.
	/*
	{
		std::wstring strDegree = std::format(L"Player ({0}, {1})", m_tPosition.m_fX, m_tPosition.m_fY);
		CGeometry::DrawString(_hDC, { 20, 100 }, strDegree, RGB(0, 255, 0));
	}
	*/
}

void CPlayer::Release()
{
	CObject::Release();
}

void CPlayer::UpdatePosition()
{
	// 마우스, 키보드를 입력하여 플레이어를 이동합니다.
	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	Vector2 tMousePosition = CMouseManager::GetManager()->GetMousePosition();

	// 왼쪽으로 이동합니다.
	if (CKeyManager::GetManager()->IsKeyPressed((uint8)EKeyType::CURSOR_LEFT)
		|| tMousePosition.m_fX <= 20.0f)
	{
		m_tPosition.m_fX -= SCROLL_SPEED * fDeltaSeconds;
	}

	// 오른쪽으로 이동합니다.
	if (CKeyManager::GetManager()->IsKeyPressed((uint8)EKeyType::CURSOR_RIGHT) ||
		tMousePosition.m_fX >= FWINCX - 20.0f)
	{
		m_tPosition.m_fX += SCROLL_SPEED * fDeltaSeconds;
	}

	// 위로 이동합니다.
	if (CKeyManager::GetManager()->IsKeyPressed((uint8)EKeyType::CURSOR_UP) ||
		tMousePosition.m_fY <= 20.0f)
	{
		m_tPosition.m_fY -= SCROLL_SPEED * fDeltaSeconds;
	}

	// 아래로 이동합니다.
	if (CKeyManager::GetManager()->IsKeyPressed((uint8)EKeyType::CURSOR_DOWN) ||
		tMousePosition.m_fY >= FWINCY - 20.0f)
	{
		m_tPosition.m_fY += SCROLL_SPEED * fDeltaSeconds;
	}

	// 플레이어 위치를 제한합니다.
	m_tPosition.m_fX = clamp(m_tPosition.m_fX, FWINCX * 0.5f, FWORLDCX - FWINCX * 0.5f);// 400 ~ 3696
	m_tPosition.m_fY = clamp(m_tPosition.m_fY, FWINCY * 0.5f, FWORLDCY - FWINCY * 0.5f);// 400 ~ 3696
}

/*
void CPlayer::SendCommand(ECommandType _eCommandType)
{
	for (const auto& pSelectedObject : m_vecSelectedObjects)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pSelectedObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		switch (_eCommandType)
		{
		case ECommandType::STOP:
		{
			CCommand* pCmd = new CStop(_eCommandType);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;

		case ECommandType::CANCEL:
		{
			CCommand* pCmd = new CCancel(_eCommandType);
			pTerranObject->PushCommandQueue(pCmd);
		}

		//case ECommandType::HOLD_POSITION:
		//	break;

		case ECommandType::USE_STIMPACK:
		{
			CCommand* pCmd = new CStimpack(_eCommandType);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;

		case ECommandType::SIEGE_MODE:
		{
			CCommand* pCmd = new CSiegeMode(_eCommandType);
			pTerranObject->PushCommandQueue(pCmd);
		}

		//// 고스트, 레이스
		//case ECommandType::CLOCK:
		//	break;

		//// 탱크
		//case ECommandType::SIEGE_MODE:
		//	break;

		//case ECommandType::TANK_MODE:
		//	break;

		//// 건물
		//case ECommandType::LIFT_OFF:
		//	break;

		case ECommandType::BUILD_SCV:
		case ECommandType::BUILD_MARINE:
		case ECommandType::BUILD_FIREBAT:
		case ECommandType::BUILD_MEDIC:
		case ECommandType::BUILD_GHOST:
		case ECommandType::BUILD_VULTURE:
		case ECommandType::BUILD_SIEGE_TANK:
		case ECommandType::BUILD_GOLIATH:
		{
			CCommand* pCmd = new CBuild(_eCommandType);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;

		default:
		break;
		}
	}
}

void CPlayer::SendCommand(ECommandType _eCommandType, CTerranObject* _pTargetObject)
{
	for (const auto& pSelectedObject : m_vecSelectedObjects)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pSelectedObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		switch (_eCommandType)
		{
		//case ECommandType::REPAIR:
		//	break;
		//case ECommandType::GATHER:
		//	break;
		default:
			break;
		}
	}
}

void CPlayer::SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition)
{
	for (const auto& pSelectedObject : m_vecSelectedObjects)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pSelectedObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }

		switch (_eCommandType)
		{
		// 공통
		case ECommandType::MOVE:
		{
			CCommand* pCmd = new CMove(_eCommandType, _tDstTile, _tDstPosition);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;

		//case ECommandType::PATROL:
		//	break;

		//	// 벌쳐
		//case ECommandType::SPIDER_MINE:
		//	break;

		//	// 건물
		//case ECommandType::RALLY_POINT:
		//	break;

		//case ECommandType::LAND:
		//	break;

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
		{
			CCommand* pCmd = new CConstruct(_eCommandType, _tDstTile, _tDstPosition);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;
		}
	}
}

void CPlayer::SendCommand(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTargetObject)
{
	for (const auto& pSelectedObject : m_vecSelectedObjects)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pSelectedObject);
		switch (_eCommandType)
		{
		case ECommandType::MOVE:
		{
			CCommand* pCmd = new CMove(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;

		case ECommandType::ATTACK:
		{
			CCommand* pCmd = new CAttack(_eCommandType, _tDstTile, _tDstPosition, _pTargetObject);
			pTerranObject->PushCommandQueue(pCmd);
		}
		break;
		
		case ECommandType::LOCK_DOWN:
		{
			
		}
		break;

		case ECommandType::NUCLEAR_STRIKE:
		{

		}
		break;
		
		}
	}
}

void CPlayer::SendCommand(ECommandType _eCommandType, ETerranUpgradeType _eUpgradeType)
{
	for (const auto& pSelectedObject : m_vecSelectedObjects)
	{
		CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pSelectedObject);
		if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { break; }
		
		switch (_eCommandType)
		{
		case ECommandType::UPGRADE:
			break;
		default:
			break;
		}
		
	}
}



void CPlayer::InsertSelectedObject(CObject* _pObject)
{
	VERIFY_NULLPTR(_pObject);
	m_vecSelectedObjects.push_back(_pObject);
}

void CPlayer::EraseSelectedObject(CObject* _pObject)
{
	VERIFY_NULLPTR(_pObject);
	m_vecSelectedObjects.erase(remove(m_vecSelectedObjects.begin(), m_vecSelectedObjects.end(), _pObject), m_vecSelectedObjects.end());
}

void CPlayer::ClearSelectedObject()
{
	m_vecSelectedObjects.clear();
}

int32 CPlayer::SizeSelectedObject()
{
	return m_vecSelectedObjects.size();
}
*/