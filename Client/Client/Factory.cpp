#include "pch.h"
#include "Factory.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "PropertyManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TimeManager.h"

#include "Scene.h"
#include "Player.h"

#include "RectangleColliderComponent.h"
#include "Command.h"

#include "UnitProperty.h"
#include "BuildingProperty.h"
#include "DynamicTilemapObject.h"

#include "Vulture.h"
#include "SiegeTank.h"
#include "Goliath.h"
#include "MachineShop.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
using namespace std;

CFactory::CFactory(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CFactory::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 128, 96 });
	SetGdiRender(true);

	// 팩토리에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 98, 64 });

	pRectCollider->SetCollisionType(ECollisionType::BUILDING);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
	pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	pRectCollider->InsertCollisionFlag(ECollisionType::MINERAL);
	pRectCollider->InsertCollisionFlag(ECollisionType::GAS);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);

	/********************
		AnimationObject 클래스
	********************/
	m_pCnstrctnAnim		= CResourceManager::GetManager()->GetAnimation(L"FctryCnstrctn");
	m_pBuildAnim		= CResourceManager::GetManager()->GetAnimation(L"FctryPrdc");
	m_pLandAnim			= CResourceManager::GetManager()->GetAnimation(L"FctryLnd");
	// m_pLandingAnim	= CResourceManager::GetManager()->GetAnimation(L"BrrcksLnding");
	// m_pLiftAnim		= CResourceManager::GetManager()->GetAnimation(L"BrrcksLft");
	// m_pLiftingAnim	= CResourceManager::GetManager()->GetAnimation(L"BrrcksLfting");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"FctryBgWrfrm5");
	SetAnimation(m_pCnstrctnAnim);

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_VULTURE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_SIEGE_TANK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_GOLIATH);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::SET_RALLY_POINT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_MACHINE_SHOP);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_VULTURE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_SIEGE_TANK);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::BUILD_GOLIATH);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::SET_RALLY_POINT);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_B].push_back(ECommandType::CANCEL_LAST);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_E].push_back(ECommandType::CANCEL);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct8"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(64.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);

	/********************
		Building 클래스
	********************/
	SetCurHP(m_buildingProperty.GetMaxHP());
	SetCurMP(0);
	SetCurShield(0);
	SetTerranBuildingType(ETerranBuildingType::FACTORY);
	m_pCurBigWireframe = m_pBigWireframe[0];


	/********************
		Factory 클래스
	********************/
	SetFactoryState(EFactoryState::CONSTRUCTION);

	m_pVultureProperty	 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::VULTURE);
	m_pTankProperty		 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::TANK);
	m_pSiegeTankProperty = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::SIEGE_TANK);
	m_pGoliathProperty	 = CPropertyManager::GetManager()->GetUnitProperty(ETerranUnitType::GOLIATH);
	m_pMachineShopProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::MACHINE_SHOP);
}

void CFactory::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	BuildUnit();
}

void CFactory::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CFactory::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CFactory::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CFactory::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetFactoryState(EFactoryState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::MOVE:
	{
		if (m_eFactoryState != EFactoryState::LIFT_OFF) { break; }
		SetFactoryState(EFactoryState::LIFT_OFF);
		m_tDstPosition = static_cast<CMove*>(pCmd)->m_tDstPosition;
		m_tDstTilePosition = static_cast<CMove*>(pCmd)->m_tDstTile;
		m_pTarget = static_cast<CMove*>(pCmd)->m_pTarget;

		// TODO: 길 찾기 알고리즘 없이 바로 이동합니다.
	}
	break;

	case ECommandType::SET_RALLY_POINT:
	{
		m_tRallyPosition = static_cast<CRallyPoint*>(pCmd)->m_tDstPosition;
		m_tRallyTilePosition = static_cast<CRallyPoint*>(pCmd)->m_tDstTile;
		m_bRallyPoint = true;
		SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
	}
	break;

	case ECommandType::BUILD_VULTURE:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pVultureProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pVultureProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pVultureProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::VULTURE);
	}
	break;

	case ECommandType::BUILD_SIEGE_TANK:
	{
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pTankProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pTankProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pTankProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::TANK);
	}
	break;

	case ECommandType::BUILD_GOLIATH:
	{
		// 큐가 가득 찬 경우
		if (m_queBuildingUnits.size() >= 5) { break; }

		CGameManager::GetManager()->IncreaseConsumedSupply(m_pGoliathProperty->GetConsumeSupply());
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pGoliathProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pGoliathProperty->GetGas());
		m_queBuildingUnits.push_back(ETerranUnitType::GOLIATH);
	}
	break;

	case ECommandType::BUILD_MACHINE_SHOP:
	{
		Vector2 tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		Vector2Int tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;

		CMachineShop* pMachineShop = new CMachineShop(*m_pMachineShopProperty);
		pMachineShop->SetOwnerType(EOwnerType::PLAYER);

		Vector2 tLeftTop = { tDstTile.m_iX * FTILECX, tDstTile.m_iY * FTILECY };
		Vector2 tOffset = { (float)m_pMachineShopProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pMachineShopProperty->GetTileSize().m_iY * FTILECY * 0.5f };
		Vector2 tPosition = tLeftTop + tOffset;

		pMachineShop->SetPosition({ tPosition });
		pMachineShop->Initialize();
		CSceneManager::GetManager()->GetCurScene()->InsertObject(pMachineShop);

		CGameManager::GetManager()->IncreaseProducedMineral(-m_pMachineShopProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pMachineShopProperty->GetGas());

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		pDynamicTilemapObject->InsertDynamicTiles(tDstTile, m_pMachineShopProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_MACHINE_SHOP),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);
	}
	break;

	case ECommandType::CANCEL_LAST:
	{
		ETerranUnitType eTerranUnitType = m_queBuildingUnits.back();
		switch (eTerranUnitType)
		{
		case ETerranUnitType::VULTURE:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pVultureProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pVultureProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pVultureProperty->GetGas());
		}
		break;


		case ETerranUnitType::TANK:
		{
			CGameManager::GetManager()->IncreaseConsumedSupply(-m_pTankProperty->GetConsumeSupply());
			CGameManager::GetManager()->IncreaseProducedMineral(m_pTankProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pTankProperty->GetGas());
		}
		break;
		}

		m_queBuildingUnits.pop_back();
		if (m_queBuildingUnits.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetFactoryState(EFactoryState::LAND);
		}
	}
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CFactory::ExecuteCommand()
{
	switch (m_eFactoryState)
	{
	case EFactoryState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
		m_pCurCnstrctnDeltaSeconds += fDeltaSeconds;

		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::FACTORY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetFactoryState(EFactoryState::LAND);
			SetAnimation(m_pLandAnim);
			
			CGameManager::GetManager()->InsertAddOnTilePosition(ETerranAddOnType::MACHINE_SHOP, CGeometry::ToTilePosition({ m_tPosition.m_fX + 80.0f, m_tPosition.m_fY }));
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;
	
	case EFactoryState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;
	
	case EFactoryState::LANDING:
	{

	}
	break;
	
	case EFactoryState::LIFTING_OFF:
	{

	}
	break;

	case EFactoryState::LIFT_OFF:
	{

	}
	break;

	case EFactoryState::BUILD:
	{
		SetAnimation(m_pBuildAnim);
	}
	break;

	case EFactoryState::DIE:
	{

	}
	break;
	}
}

void CFactory::BuildUnit()
{
	if (GetDead() == true)
	{
		SetFactoryState(EFactoryState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queBuildingUnits.empty()) { return; }
	SetFactoryState(EFactoryState::BUILD);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurBuildDeltaSecond += fDeltaSeconds;

	switch (m_queBuildingUnits.front())
	{
	case ETerranUnitType::VULTURE:
	{
		if (m_fCurBuildDeltaSecond >= m_pVultureProperty->GetSeconds())
		{
			CVulture* pVultureObject = new CVulture(*m_pVultureProperty);
			pVultureObject->SetOwnerType(EOwnerType::PLAYER);

			// TODO: 배럭 위치에서 나오도록 변경합니다.
			pVultureObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pVultureObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pVultureObject);

			if (m_bRallyPoint)
			{
				pVultureObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tvurdy00.wav", ESoundChannel::UNIT, 1.0f);
			SetFactoryState(EFactoryState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::TANK:
	{
		if (m_fCurBuildDeltaSecond >= m_pTankProperty->GetSeconds())
		{
			CSiegeTank* pTankObject = new CSiegeTank(*m_pTankProperty, *m_pSiegeTankProperty);
			pTankObject->SetOwnerType(EOwnerType::PLAYER);

			pTankObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pTankObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pTankObject);

			if (m_bRallyPoint)
			{
				pTankObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"ttardy00.wav", ESoundChannel::UNIT, 1.0f);
			SetFactoryState(EFactoryState::LAND);

			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;

	case ETerranUnitType::GOLIATH:
	{
		if (m_fCurBuildDeltaSecond >= m_pGoliathProperty->GetSeconds())
		{
			CGoliath* pGoliathObject = new CGoliath(*m_pGoliathProperty);
			pGoliathObject->SetOwnerType(EOwnerType::PLAYER);

			pGoliathObject->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.0f });
			pGoliathObject->Initialize();
			CSceneManager::GetManager()->GetCurScene()->InsertObject(pGoliathObject);

			if (m_bRallyPoint)
			{
				pGoliathObject->PushCommandQueue(new CMove(ECommandType::MOVE, m_tRallyTilePosition, m_tRallyPosition));
			}

			m_fCurBuildDeltaSecond = 0.0f;
			m_queBuildingUnits.pop_front();
			CSoundManager::GetManager()->PlaySoundEx(L"tgordy00.wav", ESoundChannel::UNIT, 1.0f);
			SetFactoryState(EFactoryState::LAND);
			
			if (m_queBuildingUnits.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}
		}
	}
	break;
	}
}

void CFactory::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
}

void CFactory::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
}

void CFactory::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
}