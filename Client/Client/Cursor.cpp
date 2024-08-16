#include "pch.h"
#include "Cursor.h"

#include "GameManager.h"
#include "PropertyManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

#include "DynamicTilemapObject.h"
#include "StaticTilemapObject.h"
#include "RectangleColliderComponent.h"
#include "Scene.h"
#include "Animation.h"
#include "Command.h"
#include "Player.h"
#include "TerranObject.h"
#include "Building.h"
#include "Unit.h"
#include "UnitProperty.h"
#include "BuildingProperty.h"

#include "Sprite.h"
using namespace std;

void CCursor::Initialize()
{
	CAnimationObject::Initialize();
	::ShowCursor(false);

	/********************
		Object 클래스
	********************/
	SetGdiRender(true);
	SetObjectType(EObjectType::CURSOR);
	SetPosition({ 400.0f, 300.0f });
	SetSize({ 10, 10 });

	// 커서에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderSize({ 10, 10 });
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);

	pRectCollider->SetCollisionType(ECollisionType::CURSOR);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::AIR_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	pRectCollider->SetDebug(false);
	pRectCollider->SetScroll(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);
	

	/********************
		AnimationObject 클래스
	********************/
	{
		m_pCrsrReleaseAnim = CResourceManager::GetManager()->GetAnimation(L"CrsrRls");
		m_pCrsrDragAnim = CResourceManager::GetManager()->GetAnimation(L"CrsrDrg");

		m_pCrsrScrollAnim[(int32)EDirectionState::EAST] = CResourceManager::GetManager()->GetAnimation(L"CrsrE");
		m_pCrsrScrollAnim[(int32)EDirectionState::NORTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"CrsrNE");
		m_pCrsrScrollAnim[(int32)EDirectionState::NORTH] = CResourceManager::GetManager()->GetAnimation(L"CrsrN");
		m_pCrsrScrollAnim[(int32)EDirectionState::NORTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"CrsrNW");
		m_pCrsrScrollAnim[(int32)EDirectionState::WEST] = CResourceManager::GetManager()->GetAnimation(L"CrsrW");
		m_pCrsrScrollAnim[(int32)EDirectionState::SOUTH_WEST] = CResourceManager::GetManager()->GetAnimation(L"CrsrSW");
		m_pCrsrScrollAnim[(int32)EDirectionState::SOUTH] = CResourceManager::GetManager()->GetAnimation(L"CrsrS");
		m_pCrsrScrollAnim[(int32)EDirectionState::SOUTH_EAST] = CResourceManager::GetManager()->GetAnimation(L"CrsrSE");

		m_pCrsrRotateAnim[(int32)EOwnerType::PLAYER] = CResourceManager::GetManager()->GetAnimation(L"CrsrRttPlyr");
		m_pCrsrRotateAnim[(int32)EOwnerType::NEUTRAL] = CResourceManager::GetManager()->GetAnimation(L"CrsrRttNtrl");
		m_pCrsrRotateAnim[(int32)EOwnerType::COMPUTER] = CResourceManager::GetManager()->GetAnimation(L"CrsrRttCmptr");

		m_pCrsrCircleOrderAnim = CResourceManager::GetManager()->GetAnimation(L"CrsrCrclPlyr");
		
		m_pCrsrCrossOrderAnim[(int32)EOwnerType::PLAYER] = CResourceManager::GetManager()->GetAnimation(L"CrsrCrssPlyr");
		m_pCrsrCrossOrderAnim[(int32)EOwnerType::NEUTRAL] = CResourceManager::GetManager()->GetAnimation(L"CrsrCrssNtrl");
		m_pCrsrCrossOrderAnim[(int32)EOwnerType::COMPUTER] = CResourceManager::GetManager()->GetAnimation(L"CrsrCrssCmptr");
		SetAnimation(m_pCrsrReleaseAnim);
	}


	/********************
		Cursor 클래스
	********************/
	SetCursorAnimState(ECursorAnimState::RELEASE);
	SetCursorCmdMode(ECursorCommandMode::MOUSE_MODE);
}


void CCursor::Update()
{
	CAnimationObject::Update();
	UpdatePosition();
	UpdateDirection();

	SelectObject();
	CommandSelectObject();
	UpdateAnim();
}

void CCursor::LateUpdate()
{
	CAnimationObject::LateUpdate();
}

void CCursor::Render(HDC _hDC)
{
	RenderDragBox(_hDC);
	CAnimationObject::Render(_hDC);
	RenderCnstrctnBP(_hDC);
}

void CCursor::Release()
{
	CAnimationObject::Release();
	::ShowCursor(true);
}


void CCursor::UpdatePosition()
{
	// 커서를 이동합니다.
	Vector2 tCursorPosition = CMouseManager::GetManager()->GetCursorPostion();
	SetPosition(tCursorPosition);

	// 청사진 위치를 이동합니다.
	Vector2Int tCrsrTilePosition = CGeometry::ToTilePosition(tCursorPosition);
	m_pCnstrctBPPosition = { tCrsrTilePosition.m_iX * FTILECX + FTILECX * 0.5f, tCrsrTilePosition.m_iY * FTILECY + FTILECY * 0.5f };
}

void CCursor::UpdateDirection()
{
	Vector2 tMousePosition = CMouseManager::GetManager()->GetMousePosition();
	if (tMousePosition.m_fX <= 20.0f)
	{
		SetCursorAnimState(ECursorAnimState::SCROLL);

		// 커서가 좌상단에 있는 경우
		if (tMousePosition.m_fY <= 20.0f)
		{
			SetDirState(EDirectionState::NORTH_WEST);
		}
		// 커서가 좌하단에 있는 경우
		else if (tMousePosition.m_fY >= FWINCY - 20.0f)
		{
			SetDirState(EDirectionState::SOUTH_WEST);
		}
		// 커서가 좌측에 있는 경우
		else
		{
			SetDirState(EDirectionState::WEST);
		}
	}
	else if (tMousePosition.m_fX >= FWINCX - 20.0f)
	{
		SetCursorAnimState(ECursorAnimState::SCROLL);

		// 커서가 우상단에 있는 경우
		if (tMousePosition.m_fY <= 20.0f)
		{
			SetDirState(EDirectionState::NORTH_EAST);
		}
		// 커서가 우하단에 있는 경우
		else if (tMousePosition.m_fY >= FWINCY - 20.0f)
		{
			SetDirState(EDirectionState::SOUTH_EAST);
		}
		// 커서가 우측에 있는 경우
		else
		{
			SetDirState(EDirectionState::EAST);
		}
	}
	// 커서가 상단에 있는 경우
	else if (tMousePosition.m_fY <= 20.0f)
	{
		SetCursorAnimState(ECursorAnimState::SCROLL);
		SetDirState(EDirectionState::NORTH);
	}
	// 커서가 하단에 있는 경우
	else if (tMousePosition.m_fY >= FWINCY - 20.0f)
	{
		SetCursorAnimState(ECursorAnimState::SCROLL);
		SetDirState(EDirectionState::SOUTH);
	}
	// 커서가 중앙에 있는 경우
	else
	{
		if (GetCursorAnimState() == ECursorAnimState::ROTATE) { return; }
		if (GetCursorAnimState() == ECursorAnimState::CIRCLE_ORDER) { return; }
		SetCursorAnimState(ECursorAnimState::RELEASE);
		SetDirState(EDirectionState::ENUM_END);
	}
}

void CCursor::SelectObject()
{
	if (m_eWatingCommandType != ECommandType::ENUM_END)
	{
		return;
	}

	switch (m_eCursorCommandMode)
	{
	/*****************
		키보드 입력 후 마우스 명령 모드
	*****************/
	case ECursorCommandMode::KEYBOARD_MODE:
	{
		// 마우스로 명령을 내리는 키보드 모드에서는 아무것도 하지 않습니다.
	}
	break;

	/*****************
		마우스 명령 모드
	*****************/
	case ECursorCommandMode::MOUSE_MODE:
	{
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			m_tDragBeginPosition = m_tPosition;
			m_tDragEndPosition = m_tPosition;
		}

		// 마우스를 유닛 밖에 놓고 드래그한 경우
		if (CKeyManager::GetManager()->IsKeyPressed((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			if (m_bWasKeyMode)
			{
				m_tDragBeginPosition = m_tPosition;
				m_bWasKeyMode = false;
				return;
			}

			m_tDragEndPosition = m_tPosition;
			if (m_tDragBeginPosition.m_fX != m_tDragEndPosition.m_fX || m_tDragBeginPosition.m_fY != m_tDragEndPosition.m_fY)
			{
				SetCursorAnimState(ECursorAnimState::DRAG);
				return;
			}
		}

		// 마우스를 뗐을 때 유닛이나 건물이 있는 경우, 선택된 오브젝트를 갱신합니다.
		if (CKeyManager::GetManager()->IsKeyUp((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			m_tDragEndPosition = m_tPosition;

			RECT tDragRect{ 0, 0, 0, 0 };

			// 한 유닛 혹은 여러 유닛을 선택했는지 여부를 저장합니다.
			bool bClick = false;

			// 클릭으로 처리합니다.
			if ((m_tDragBeginPosition.m_fX == m_tDragEndPosition.m_fX) && (m_tDragBeginPosition.m_fY == m_tDragEndPosition.m_fY))
			{
				bClick = true;
				tDragRect =
				{
					(int32)(m_tDragBeginPosition.m_fX - 0.5f),
					(int32)(m_tDragBeginPosition.m_fY - 0.5f),
					(int32)(m_tDragBeginPosition.m_fX + 0.5f),
					(int32)(m_tDragBeginPosition.m_fY + 0.5f)
				};
			}
			// 드래그로 처리합니다.
			else
			{
				bClick = false;
				int32 minX = (int32)min(m_tDragBeginPosition.m_fX, m_tDragEndPosition.m_fX);
				int32 maxX = (int32)max(m_tDragBeginPosition.m_fX, m_tDragEndPosition.m_fX);
				int32 minY = (int32)min(m_tDragBeginPosition.m_fY, m_tDragEndPosition.m_fY);
				int32 maxY = (int32)max(m_tDragBeginPosition.m_fY, m_tDragEndPosition.m_fY);
				tDragRect = { minX, minY, maxX, maxY };
			}

			// 모든 오브젝트를 순회합니다.
			CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
			VERIFY_NULLPTR(pCurScene);

			vector<CTerranObject*> vecSelectedUnits;
			list<CObject*>& lstUnits = pCurScene->GetUnits();
			bool bUnit = IsThereObject(lstUnits, vecSelectedUnits, tDragRect, bClick);

			vector<CTerranObject*> vecSelectedBuildings;
			bool bBuilding = false;
			if (bUnit == false)
			{
				list<CObject*>& lstBuildings = pCurScene->GetBuildings();
				bBuilding = IsThereObject(lstBuildings, vecSelectedBuildings, tDragRect, bClick);
			}

			// 클릭 혹은 드래그한 곳에 유닛이 있는 경우
			if (bUnit == true)
			{
				CGameManager::GetManager()->ClearSelectedObject();
				CGameManager::GetManager()->SetSelectedObjects(vecSelectedUnits);

				sort(vecSelectedUnits.begin(), vecSelectedUnits.end(), [](CTerranObject* pFirst, CTerranObject* pSecond) {
					CUnit* pFirstUnit = dynamic_cast<CUnit*>(pFirst);
					CUnit* pSecondUnit = dynamic_cast<CUnit*>(pSecond);
					return pFirstUnit->GetUnitProperty().GetIntRank() > pSecondUnit->GetUnitProperty().GetIntRank();
				});
				PlayUnitSound(vecSelectedUnits.front());
			}

			// 클릭 혹은 드래그한 곳에 건물만 있는 경우
			else if (bUnit == false && bBuilding == true)
			{
				CGameManager::GetManager()->ClearSelectedObject();
				CGameManager::GetManager()->InsertSelectedObject(vecSelectedBuildings.front());
				PlayStructureSound(vecSelectedBuildings.front());
			}

			// 적군을 드래그한 경우BUILD
			else
			{
				
			}

			m_tDragBeginPosition = { 0.0f, 0.0f };
			m_tDragEndPosition = { 0.0f, 0.0f };
		}
	}
	break;
	}
}

void CCursor::CommandSelectObject()
{
	switch (m_eCursorCommandMode)
	{
	/*****************
		키보드 모드
	*****************/
	case ECursorCommandMode::KEYBOARD_MODE:
	{
		// 건물 건설인 경우, 스프라이트를 업데이트합니다.
		UpdateBlueprintSprite();

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CTilemapObject* pStaitcTilemap = CSceneManager::GetManager()->GetCurScene()->GetStaticTilemapObject();

		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		CStaticTilemapObject* pStaticTilemapObject = dynamic_cast<CStaticTilemapObject*>(pStaitcTilemap);

		Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);

		// 명령을 실행합니다.
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			switch (m_eWatingCommandType)
			{
			case ECommandType::MOVE:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition, nullptr);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
				CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			break;

			case ECommandType::ATTACK:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition, nullptr);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
				CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			break;

			case ECommandType::SET_RALLY_POINT:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
				CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			break;

			/*
			case ECommandType::PATROL:
				break;
			case ECommandType::HOLD_POSITION:
				break;
			case ECommandType::REPAIR:
				break;
			case ECommandType::GATHER:
				break;
			*/

			case ECommandType::BUILD_COMMAND_CENTER:
			case ECommandType::BUILD_BARRACKS:
			case ECommandType::BUILD_ENGINEERING_BAY:
			case ECommandType::BUILD_FACTORY:
			case ECommandType::BUILD_STARPORT:
			case ECommandType::BUILD_SCIENCE_FACILITY:
			{
				if (pDynamicTilemapObject->IsImpassableDynamicTiles(tTilePosition, { 4, 3 }) || pStaticTilemapObject->IsImpassableStaticTiles(tTilePosition, { 4, 3 }))
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;
				}
			}
			break;

			case ECommandType::BUILD_REFINERY:
			{
				// TODO: 리파이너리 위치 알아내기
			}
			break;

			case ECommandType::BUILD_SUPPLY_DEPOT:
			case ECommandType::BUILD_ACADEMY:
			case ECommandType::BUILD_ARMORY:
			{
				if (pDynamicTilemapObject->IsImpassableDynamicTiles(tTilePosition, { 3, 2 }) || pStaticTilemapObject->IsImpassableStaticTiles(tTilePosition, { 3, 2 }))
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;
				}
			}
			break;

			case ECommandType::BUILD_MACHINE_SHOP:
			{
				bool bPossible = false;
				vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(ETerranAddOnType::MACHINE_SHOP);

				Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
				for (const auto& TilePosition : vecMachineShopTilePosition)
				{
					if (TilePosition == tTilePosition)
					{
						bPossible = true;
						break;
					}
				}

				if (!bPossible)
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;


					m_tDragBeginPosition = { 0.0f, 0.0f };
					m_tDragEndPosition = { 0.0f, 0.0f };
				}
			}
			break;

			case ECommandType::BUILD_CONTROL_TOWER:
			{
				bool bPossible = false;
				vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(ETerranAddOnType::CONTROL_TOWER);

				Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
				for (const auto& TilePosition : vecMachineShopTilePosition)
				{
					if (TilePosition == tTilePosition)
					{
						bPossible = true;
						break;
					}
				}

				if (!bPossible)
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;

					m_tDragBeginPosition = { 0.0f, 0.0f };
					m_tDragEndPosition = { 0.0f, 0.0f };
				}
			}
			break;

			case ECommandType::BUILD_COVERT_OPS:
			{
				bool bPossible = false;
				vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(ETerranAddOnType::COVERT_OPS);

				Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
				for (const auto& TilePosition : vecMachineShopTilePosition)
				{
					if (TilePosition == tTilePosition)
					{
						bPossible = true;
						break;
					}
				}

				if (!bPossible)
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;

					m_tDragBeginPosition = { 0.0f, 0.0f };
					m_tDragEndPosition = { 0.0f, 0.0f };
				}
			}
			break;

			case ECommandType::BUILD_PHYSICS_LAB:
			{
				bool bPossible = false;
				vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(ETerranAddOnType::PHYSICS_LAB);

				Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
				for (const auto& TilePosition : vecMachineShopTilePosition)
				{
					if (TilePosition == tTilePosition)
					{
						bPossible = true;
						break;
					}
				}

				if (!bPossible)
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;

					m_tDragBeginPosition = { 0.0f, 0.0f };
					m_tDragEndPosition = { 0.0f, 0.0f };
				}
			}
			break;

			case ECommandType::BUILD_NUCLEAR_SILO:
			{
				bool bPossible = false;
				vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(ETerranAddOnType::NUCLEAR_SILO);

				Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
				for (const auto& TilePosition : vecMachineShopTilePosition)
				{
					if (TilePosition == tTilePosition)
					{
						bPossible = true;
						break;
					}
				}

				if (!bPossible)
				{
					CSoundManager::GetManager()->RandomPlaySound(2, ESoundChannel::UNIT, L"tscerr0", L".wav");
				}
				else
				{
					CSoundManager::GetManager()->PlaySoundEx(L"pbldgplc.wav", ESoundChannel::ADVISOR, 1.0f);
					CGameManager::GetManager()->SendCommand(m_eWatingCommandType, CGeometry::ToTilePosition(m_tPosition), m_tPosition);
					m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
					m_pCnstrctBPSprite = nullptr;
					m_eWatingCommandType = ECommandType::ENUM_END;


					m_tDragBeginPosition = { 0.0f, 0.0f };
					m_tDragEndPosition = { 0.0f, 0.0f };
				}
			}
			break;
			}

			m_bWasKeyMode = true;
		}

		// 명령을 취소합니다.
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::RIGHT_MOUSE_BUTTON))
		{
			CGameManager::GetManager()->SendCommand(ECommandType::CANCEL);
			m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
			m_eWatingCommandType = ECommandType::ENUM_END;
			m_pCnstrctBPSprite = nullptr;

			m_bWasKeyMode = true;
		}
	}
	break;

	/*****************
		마우스 모드
	*****************/
	case ECursorCommandMode::MOUSE_MODE:
	{
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::RIGHT_MOUSE_BUTTON) && !m_bCollided)
		{
			Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
			CGameManager::GetManager()->SendCommand(ECommandType::MOVE, tTilePosition, m_tPosition);
		}
	}
	break;
	}
}

bool CCursor::IsThereObject(std::list<CObject*>& _lstObjects, std::vector<CTerranObject*>& _vecSelectedObjects, RECT& _tDragRect, bool _bClick)
{
	bool bIsThereUnit = false;

	for (const auto& pObject : _lstObjects)
	{
		// 유닛의 사각형을 구합니다.
		Vector2 tObjectPosition = pObject->GetPosition();
		Vector2Int tObjectSize = pObject->GetSize();
		RECT tObjectRect = CGeometry::GetRect(tObjectPosition, tObjectSize);

		// 충돌한 사각형을 선언합니다.
		RECT tIntersectRect{};

		// 클릭이고 충돌한 오브젝트가 있는 경우
		if (_bClick && ::IntersectRect(&tIntersectRect, &_tDragRect, &tObjectRect))
		{
			CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pObject);
			_vecSelectedObjects.push_back(pTerranObject);
			return true;
		}

		// 드래그고 충돌한 오브젝트가 있는 경우
		else if (!_bClick && ::IntersectRect(&tIntersectRect, &_tDragRect, &tObjectRect))
		{
			CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pObject);

			// 적군은 제외합니다.
			if (pTerranObject->GetOwnerType() != EOwnerType::PLAYER) { continue; }
			bIsThereUnit = true;
			_vecSelectedObjects.push_back(pTerranObject);
		}

		if (_vecSelectedObjects.size() >= 12) { break; }
	}

	return bIsThereUnit;
}

void CCursor::UpdateAnim()
{
	// 커서의 애니메이션을 변경합니다.
	switch (m_eCursorAnimState)
	{
	case ECursorAnimState::RELEASE:
		SetAnimation(m_pCrsrReleaseAnim);
		break;

	case ECursorAnimState::DRAG:
		SetAnimation(m_pCrsrDragAnim);
		break;

	case ECursorAnimState::SCROLL:
		SetAnimation(m_pCrsrScrollAnim[(int32)m_eDirectionState]);
		break;

	case ECursorAnimState::ROTATE:
		SetAnimation(m_pCrsrRotateAnim[(int32)m_eCollidedOwnerType]);
		break;

	case ECursorAnimState::CIRCLE_ORDER:
		SetAnimation(m_pCrsrCircleOrderAnim);
		break;

	case ECursorAnimState::CROSS_ORDER:
		SetAnimation(m_pCrsrCrossOrderAnim[(int32)m_eCollidedOwnerType]);
		break;
	}
}

void CCursor::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	m_bCollided = true;
	SetCursorAnimState(ECursorAnimState::ROTATE);
}

void CCursor::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CObject* pDstObject = _pDstCollider->GetComponentOwner();
	SetCollidedOwnerType(dynamic_cast<CTerranObject*>(pDstObject)->GetOwnerType());

	switch (m_eCursorCommandMode)
	{
	/*****************
		키보드 모드
	*****************/
	case ECursorCommandMode::KEYBOARD_MODE:
	{
		// 명령을 실행합니다.
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::LEFT_MOUSE_BUTTON))
		{
			Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
			CTerranObject* pTarget = dynamic_cast<CTerranObject*>(_pDstCollider->GetComponentOwner());

			switch (m_eWatingCommandType)
			{
			case ECommandType::ATTACK:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition, pTarget);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
				CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			break;

			case ECommandType::MOVE:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition, pTarget);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
				CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
			break;

			case ECommandType::USE_NUCLEAR_STRIKE:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, tTilePosition, m_tPosition, pTarget);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
			}
			break;

			case ECommandType::USE_DEFENSIVE_MATRIX:
			case ECommandType::USE_IRRADIATE:
			case ECommandType::USE_YAMATO_CANNON:
			{
				CGameManager::GetManager()->SendCommand(m_eWatingCommandType, pTarget);
				m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
				m_eWatingCommandType = ECommandType::ENUM_END;
			}
			break;
			}
		}

		// 명령을 취소합니다.
		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::RIGHT_MOUSE_BUTTON))
		{
			CGameManager::GetManager()->SendCommand(ECommandType::CANCEL);
			m_eCursorCommandMode = ECursorCommandMode::MOUSE_MODE;
			m_eWatingCommandType = ECommandType::ENUM_END;
			m_pCnstrctBPSprite = nullptr;
			CGameManager::GetManager()->FrontSelectedObject()->SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
		}
	}
	break;

	/*****************
		마우스 모드
	*****************/
	case ECursorCommandMode::MOUSE_MODE:
	{
		SetCursorAnimState(ECursorAnimState::ROTATE);

		CObject* pDstObject = _pDstCollider->GetComponentOwner();
		SetCollidedOwnerType(dynamic_cast<CTerranObject*>(pDstObject)->GetOwnerType());

		if (CKeyManager::GetManager()->IsKeyDown((int32)EKeyType::RIGHT_MOUSE_BUTTON))
		{
			Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
			CTerranObject* pTerranObject = dynamic_cast<CTerranObject*>(pDstObject);

			// 충돌한 유닛이 적군 유닛인 경우, 공격 명령을 내립니다.
			if (pTerranObject->GetOwnerType() == EOwnerType::COMPUTER)
			{
				CGameManager::GetManager()->SendCommand(ECommandType::ATTACK, tTilePosition, m_tPosition, pTerranObject);
			}
			// 충돌한 유닛이 아군 유닛인 경우, 이동 명령을 내립니다.
			else if (pTerranObject->GetOwnerType() == EOwnerType::PLAYER)
			{
				CGameManager::GetManager()->SendCommand(ECommandType::MOVE, tTilePosition, m_tPosition, pTerranObject);
			}
			else if (pTerranObject->GetOwnerType() == EOwnerType::NEUTRAL && pTerranObject->GetTerranObjectType() == ETerranObjectType::MINERAL)
			{
				CGameManager::GetManager()->SendCommand(ECommandType::GATHER, tTilePosition, m_tPosition, pTerranObject);
			}
		}
	}
	break;
	}
}

void CCursor::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	m_bCollided = false;
	SetCursorAnimState(ECursorAnimState::RELEASE);
	SetCollidedOwnerType(EOwnerType::NEUTRAL);
}

void CCursor::UpdateBlueprintSprite()
{
	switch (m_eWatingCommandType)
	{
	case ECommandType::BUILD_COMMAND_CENTER:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"CmdCntrO", L"CmdCntrX");
	}
	break;

	case ECommandType::BUILD_SUPPLY_DEPOT:
	{
		m_pCnstrctOffset = { 32.0f, 16.0f };
		SetBlueprintSprite(3, 2, L"SplyO", L"SplyX");
	}
	break;


	case ECommandType::BUILD_REFINERY:
	{
		m_pCnstrctOffset = { 48.0f, 16.0f };
		SetRefineryBPSprite(4, 2, L"RfnryO", L"RfnryX");
	}
	break;

	case ECommandType::BUILD_ENGINEERING_BAY:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"EngnrByO", L"EngnrByX");
	}
	break;

	case ECommandType::BUILD_BARRACKS:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"BrrcksO", L"BrrcksX");
	}
	break;

	case ECommandType::BUILD_ACADEMY:
	{

		m_pCnstrctOffset = { 32.0f, 16.0f };
		SetBlueprintSprite(3, 2, L"AcdmyO", L"AcdmyX");
	}
	break;

	case ECommandType::BUILD_FACTORY:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"FctryO", L"FctryX");
	}
	break;

	case ECommandType::BUILD_STARPORT:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"StrprtO", L"StrprtX");
	}
	break;

	case ECommandType::BUILD_SCIENCE_FACILITY:
	{
		m_pCnstrctOffset = { 48.0f, 32.0f };
		SetBlueprintSprite(4, 3, L"ScncFcltyO", L"ScncFcltyX");
	}
	break;

	case ECommandType::BUILD_ARMORY:
	{
		m_pCnstrctOffset = { 32.0f, 16.0f };
		SetBlueprintSprite(3, 2, L"ArmryO", L"ArmryX");
	}
	break;

	case ECommandType::BUILD_COMSAT_STATION:
	{

	}
	break;

	case ECommandType::BUILD_NUCLEAR_SILO:
	{
		m_pCnstrctOffset = { 16.0f, 16.0f };
		SetAddOnBlueprintSprite(ETerranAddOnType::NUCLEAR_SILO, 2, 2, L"NclrSloO", L"NclrSloX");
	}
	break;

	case ECommandType::BUILD_MACHINE_SHOP:
	{
		m_pCnstrctOffset = { 16.0f, 16.0f };
		SetAddOnBlueprintSprite(ETerranAddOnType::MACHINE_SHOP, 2, 2, L"MchnShopO", L"MchnShopX");
	}
	break;

	case ECommandType::BUILD_CONTROL_TOWER:
	{
		m_pCnstrctOffset = { 16.0f, 16.0f };
		SetAddOnBlueprintSprite(ETerranAddOnType::CONTROL_TOWER, 2, 2, L"CntrlTwrO", L"CntrlTwrX");
	}
	break;

	case ECommandType::BUILD_PHYSICS_LAB:
	{
		m_pCnstrctOffset = { 16.0f, 16.0f };
		SetAddOnBlueprintSprite(ETerranAddOnType::PHYSICS_LAB, 2, 2, L"PhscLbO", L"PhscLbX");
	}
	break;

	case ECommandType::BUILD_COVERT_OPS:
	{
		m_pCnstrctOffset = { 16.0f, 16.0f };
		SetAddOnBlueprintSprite(ETerranAddOnType::COVERT_OPS, 2, 2, L"CvrtOpsO", L"CvrtOpsX");
	}
	break;

	default:
		SetCursorAnimState(ECursorAnimState::CROSS_ORDER);
		break;
	}
}

void CCursor::SetBlueprintSprite(int32 _iWidth, int32 _iHeight, const wstring& _strKeyO, const wstring& _strKeyX)
{
	CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
	CTilemapObject* pStaitcTilemap = CSceneManager::GetManager()->GetCurScene()->GetStaticTilemapObject();

	CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
	CStaticTilemapObject* pStaticTilemapObject = dynamic_cast<CStaticTilemapObject*>(pStaitcTilemap);
	Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);

	if (pDynamicTilemapObject->IsImpassableDynamicTiles(tTilePosition, { _iWidth, _iHeight }) || pStaticTilemapObject->IsImpassableStaticTiles(tTilePosition, { _iWidth, _iHeight }))
	{
		m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyX);
	}
	else { m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyO); }
}

void CCursor::SetRefineryBPSprite(int32 _iWidth, int32 _iHeight, const std::wstring& _strKeyO, const std::wstring& _strKeyX)
{
	Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
	std::vector<Vector2Int>& vecVspnGasTilePosition = CGameManager::GetManager()->GetVspnGasTilePosition();

	for (const auto& tVspnGasTilePosition : vecVspnGasTilePosition)
	{
		if (tVspnGasTilePosition == tTilePosition)
		{
			m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyO);
			break;
		}
	}

	m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyX);
}

void CCursor::SetAddOnBlueprintSprite(ETerranAddOnType _eAddOnType, int32 _iWidth, int32 _iHeight, const std::wstring& _strKeyO, const std::wstring& _strKeyX)
{
	vector<Vector2Int> vecMachineShopTilePosition = CGameManager::GetManager()->GetAddOnTilePosition(_eAddOnType);

	Vector2Int tTilePosition = CGeometry::ToTilePosition(m_tPosition);
	for (const auto& TilePosition : vecMachineShopTilePosition)
	{
		if (TilePosition == tTilePosition)
		{
			m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyO);
			return;
		}
	}
	m_pCnstrctBPSprite = CResourceManager::GetManager()->GetSprite(_strKeyX);
}

void CCursor::RenderCnstrctnBP(HDC _hDC)
{
	// 스프라이트를 렌더합니다.
	VERIFY_NULLPTR(m_pCnstrctBPSprite);
	tagSpriteInfo tSpriteInfo = m_pCnstrctBPSprite->GetSpriteInfo();

	Vector2Int tSize = tSpriteInfo.m_tSize;
	Vector2Int tPosition = tSpriteInfo.m_tPosition;
	uint32 uiAlpha = m_pCnstrctBPSprite->GetTextureAlpha();

	// 스크롤된 위치를 구합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		::BitBlt(_hDC,																							// 사본 이미지의 DC
			(int32)(m_pCnstrctBPPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),	// 사본 이미지에서 원본 이미지가 렌더될 좌상단 위치
			(int32)(m_pCnstrctBPPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
			tSize.m_iWidth,																						// 원본 이미지의 밑변
			tSize.m_iHeight,																					// 원본 이미지의 높이
			m_pCnstrctBPSprite->GetTextureDC(),																	// 원본 이미지의 DC
			tPosition.m_iX,																						// 원본 이미지의 좌상단 위치
			tPosition.m_iY,
			SRCCOPY);
	}
	else
	{
		GdiTransparentBlt(_hDC,
			(int32)(m_pCnstrctBPPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f) + m_pCnstrctOffset.m_fX),
			(int32)(m_pCnstrctBPPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f) + m_pCnstrctOffset.m_fY),
			tSize.m_iWidth,
			tSize.m_iHeight,
			m_pCnstrctBPSprite->GetTextureDC(),
			tPosition.m_iX,
			tPosition.m_iY,
			tSize.m_iWidth,
			tSize.m_iHeight,
			uiAlpha);
	}
}

void CCursor::RenderDragBox(HDC _hDC)
{
	if (m_tDragEndPosition.m_fX == 0.0f && m_tDragEndPosition.m_fY == 0.0f)
	{
		return;
	}

	// 스크롤된 위치를 구합니다.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();


	float fWidth = abs(m_tDragBeginPosition.m_fX - m_tDragEndPosition.m_fX);
	float fHeight = abs(m_tDragBeginPosition.m_fY - m_tDragEndPosition.m_fY);
	float fX = (m_tDragBeginPosition.m_fX + m_tDragEndPosition.m_fX) * 0.5f;
	float fY = (m_tDragBeginPosition.m_fY + m_tDragEndPosition.m_fY) * 0.5f;

	Vector2 tDragBoxPosition = { fX, fY };
	Vector2Int tDragBoxSize = { (int32)fWidth, (int32)fHeight };

	CGeometry::DrawTransparentRectangle(_hDC, { tDragBoxPosition.m_fX - (tCameraPosition.m_fX - FWINCX * 0.5f), tDragBoxPosition.m_fY - (tCameraPosition.m_fY - FWINCY * 0.5f) }, tDragBoxSize, RGB(0, 255, 55));
}

void CCursor::PlayUnitSound(CTerranObject* _pObject)
{
	CUnit* pUnit = dynamic_cast<CUnit*>(_pObject);
	ETerranUnitType eTerranUnitType = pUnit->GetTerranUnitType();

	srand((unsigned int)time(NULL));

	switch (eTerranUnitType)
	{
	case ETerranUnitType::SCV:				RandomSound(4, L"tscwht0", L".wav");	break;
	case ETerranUnitType::MARINE:			RandomSound(4, L"tmawht0", L".wav");	break;
	case ETerranUnitType::FIREBAT:			RandomSound(4, L"tfbwht0", L".wav");	break;
	case ETerranUnitType::MEDIC:			RandomSound(4, L"tmdwht0", L".wav");	break;
	case ETerranUnitType::GHOST:			RandomSound(4, L"tghwht0", L".wav");	break;
	case ETerranUnitType::VULTURE:			RandomSound(4, L"tvuwht0", L".wav");	break;
	case ETerranUnitType::TANK:				RandomSound(4, L"ttawht0", L".wav");	break;
	case ETerranUnitType::GOLIATH:			// RandomSound(4, L"tfbwht0", L".wav");	break;
	case ETerranUnitType::WRAITH:			// RandomSound(4, L"tscwht0", L".wav");	break;
	case ETerranUnitType::DROPSHIP:			// RandomSound(4, L"tmawht0", L".wav");	break;
	case ETerranUnitType::VALKYRIE:			// RandomSound(4, L"tfbwht0", L".wav");	break;
	case ETerranUnitType::SCIENCE_VESSEL:	RandomSound(4, L"tvewht0", L".wav");	break;
	case ETerranUnitType::BATTLE_CRUISER:	RandomSound(4, L"tbawht0", L".wav");	break;
	break;
	}
}

void CCursor::PlayStructureSound(CTerranObject* _pObject)
{
	CBuilding* pBuilding = dynamic_cast<CBuilding*>(_pObject);
	ETerranBuildingType eTerranBuildingType = pBuilding->GetTerranBuildingType();

	switch (eTerranBuildingType)
	{
	case ETerranBuildingType::COMMAND_CENTER:	break;
	case ETerranBuildingType::SUPPLY_DEPOT:		CSoundManager::GetManager()->PlaySoundEx(L"tpgwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::REFINERY:			CSoundManager::GetManager()->PlaySoundEx(L"trewht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::BARRACKS:			break;
	case ETerranBuildingType::ENGINEERING_BAY:	CSoundManager::GetManager()->PlaySoundEx(L"twpwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::ACADEMY:			CSoundManager::GetManager()->PlaySoundEx(L"tacwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::MISSILE_TURRET:	CSoundManager::GetManager()->PlaySoundEx(L"tmtwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::BUNKER:			break;
	case ETerranBuildingType::FACTORY:			break;
	case ETerranBuildingType::ARMORY:			CSoundManager::GetManager()->PlaySoundEx(L"tclwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::STARPORT:			break;
	case ETerranBuildingType::SCIENCE_FACILITY:	CSoundManager::GetManager()->PlaySoundEx(L"trlwht00.wav", ESoundChannel::BUILDING, 1.0f);	break; 
	case ETerranBuildingType::COMSAT_STATION:	CSoundManager::GetManager()->PlaySoundEx(L"tcswht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::NUCLEAR_SILO:		CSoundManager::GetManager()->PlaySoundEx(L"tnswht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::MACHINE_SHOP:		CSoundManager::GetManager()->PlaySoundEx(L"tmswht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::CONTROL_TOWER:	CSoundManager::GetManager()->PlaySoundEx(L"tddwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::PHYSICS_LAB:		CSoundManager::GetManager()->PlaySoundEx(L"tplwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	case ETerranBuildingType::COVERT_OPS:		CSoundManager::GetManager()->PlaySoundEx(L"tglwht00.wav", ESoundChannel::BUILDING, 1.0f);	break;
	}
}

void CCursor::RandomSound(int32 _iIndex, const std::wstring& _strName, const std::wstring& _strEx)
{
	int32 iIndex = rand() % _iIndex;
	const wstring& strPath = _strName + to_wstring(iIndex) + _strEx;
	CSoundManager::GetManager()->PlaySoundEx(strPath.c_str(), ESoundChannel::BUILDING, 1.0f);
}
