#include "pch.h"
#include "ScienceFacility.h"

#include "GameManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "PropertyManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TimeManager.h"

#include "RectangleColliderComponent.h"
#include "Command.h"
#include "Scene.h"
#include "DynamicTilemapObject.h"

#include "UpgradeProperty.h"
#include "BuildingProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "CovertOps.h"
#include "PhysicsLab.h"

CScienceFacility::CScienceFacility(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CScienceFacility::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 96, 64 });
	SetGdiRender(true);

	// 배럭에 사각형 콜라이더 컴포넌트를 붙입니다.
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
	m_pCnstrctnAnim = CResourceManager::GetManager()->GetAnimation(L"ScncFcltyCnstrctn");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"ScncFcltyLand");
	m_pUpgradeAnim = CResourceManager::GetManager()->GetAnimation(L"ScncFcltyUpgrd");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"ScncFcltyBgWrfrm5");

	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);

	SetCurCommandWidgetState(ECommandWidgetState::STATE_Z);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::UPGRADE_IRRADIATE);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_PHYSICS_LAB);
	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].push_back(ECommandType::BUILD_COVERT_OPS);

	m_vecCommandTypes[(int32)ECommandWidgetState::STATE_G].push_back(ECommandType::CANCEL_UPGRADE);


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
	SetTerranBuildingType(ETerranBuildingType::SCIENCE_FACILITY);

	/********************
		Academy 클래스
	********************/
	SetScienceFacilityState(EScienceFacilityState::CONSTRUCTION);
	SetAnimation(m_pCnstrctnAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];

	m_pIrradiateProperty = CPropertyManager::GetManager()->GetUpgradeProperty(ETerranUpgradeType::IRRADIATE);

	m_pCovertOpsProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::COVERT_OPS);
	m_pPhysicsLabProperty = CPropertyManager::GetManager()->GetBuildingProperty(ETerranBuildingType::PHYSICS_LAB);
}

void CScienceFacility::Update()
{
	CBuilding::Update();
	AnalyseCommand();
	ExecuteCommand();
	Upgrade();
}

void CScienceFacility::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CScienceFacility::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CScienceFacility::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CScienceFacility::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CScienceFacility::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CScienceFacility::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

void CScienceFacility::AnalyseCommand()
{
	if (GetDead() == true)
	{
		SetScienceFacilityState(EScienceFacilityState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (IsEmptyCommandQueue()) { return; }

	CCommand* pCmd = FrontCommandQueue();
	switch (pCmd->m_eCommandType)
	{
	case ECommandType::UPGRADE_IRRADIATE:
	{
		if (m_queUpgrades.size() >= 1) { break; }
		CGameManager::GetManager()->IncreaseProducedMineral(-m_pIrradiateProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pIrradiateProperty->GetGas());
		m_queUpgrades.push_back(ETerranUpgradeType::IRRADIATE);
	}
	break;

	case ECommandType::CANCEL_UPGRADE:
	{
		if (m_queUpgrades.size() <= 0) { break; }

		ETerranUpgradeType eTerranUpgradeType = m_queUpgrades.back();
		switch (eTerranUpgradeType)
		{
		case ETerranUpgradeType::IRRADIATE:
		{
			CGameManager::GetManager()->IncreaseProducedMineral(m_pIrradiateProperty->GetMineral());
			CGameManager::GetManager()->IncreaseProducedGas(m_pIrradiateProperty->GetGas());
		}
		break;
		}

		m_queUpgrades.pop_back();
		if (m_queUpgrades.empty())
		{
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetScienceFacilityState(EScienceFacilityState::LAND);
		}
	}
	break;

	case ECommandType::BUILD_COVERT_OPS:
	{
		Vector2 tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		Vector2Int tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;

		CCovertOps* pCovertOps = new CCovertOps(*m_pCovertOpsProperty);
		pCovertOps->SetOwnerType(EOwnerType::PLAYER);

		Vector2 tLeftTop = { tDstTile.m_iX * FTILECX, tDstTile.m_iY * FTILECY };
		Vector2 tOffset = { (float)m_pCovertOpsProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pCovertOpsProperty->GetTileSize().m_iY * FTILECY * 0.5f };
		Vector2 tPosition = tLeftTop + tOffset;

		pCovertOps->SetPosition({ tPosition });
		pCovertOps->Initialize();
		CSceneManager::GetManager()->GetCurScene()->InsertObject(pCovertOps);

		CGameManager::GetManager()->IncreaseProducedMineral(-m_pCovertOpsProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pCovertOpsProperty->GetGas());

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		pDynamicTilemapObject->InsertDynamicTiles(tDstTile, m_pCovertOpsProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_COVERT_OPS),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_PHYSICS_LAB),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);
	}
	break;
	

	case ECommandType::BUILD_PHYSICS_LAB:
	{
		Vector2 tDstPosition = static_cast<CConstruct*>(pCmd)->m_tDstPosition;
		Vector2Int tDstTile = static_cast<CConstruct*>(pCmd)->m_tDstTile;

		CPhysicsLab* pPhysicsLab = new CPhysicsLab(*m_pPhysicsLabProperty);
		pPhysicsLab->SetOwnerType(EOwnerType::PLAYER);

		Vector2 tLeftTop = { tDstTile.m_iX * FTILECX, tDstTile.m_iY * FTILECY };
		Vector2 tOffset = { (float)m_pPhysicsLabProperty->GetTileSize().m_iX * FTILECX * 0.5f, (float)m_pPhysicsLabProperty->GetTileSize().m_iY * FTILECY * 0.5f };
		Vector2 tPosition = tLeftTop + tOffset;

		pPhysicsLab->SetPosition({ tPosition });
		pPhysicsLab->Initialize();
		CSceneManager::GetManager()->GetCurScene()->InsertObject(pPhysicsLab);

		CGameManager::GetManager()->IncreaseProducedMineral(-m_pPhysicsLabProperty->GetMineral());
		CGameManager::GetManager()->IncreaseProducedGas(-m_pPhysicsLabProperty->GetGas());

		CTilemapObject* pDynamicTilemap = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
		CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pDynamicTilemap);
		pDynamicTilemapObject->InsertDynamicTiles(tDstTile, m_pPhysicsLabProperty->GetTileSize(), { ETileType::BUILDING, EOwnerType::PLAYER });

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_COVERT_OPS),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);

		m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
			remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::BUILD_PHYSICS_LAB),
			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
		);
	}
	break;

	default:
	break;
	}

	SAFE_DELETE(pCmd);
	PopCommandQueue();
}

void CScienceFacility::ExecuteCommand()
{
	switch (m_eScienceFacilityState)
	{
	case EScienceFacilityState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::SCIENCE_FACILITY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetScienceFacilityState(EScienceFacilityState::LAND);
			SetAnimation(m_pLandAnim);

			CGameManager::GetManager()->InsertAddOnTilePosition(ETerranAddOnType::PHYSICS_LAB, CGeometry::ToTilePosition({ m_tPosition.m_fX + 80.0f, m_tPosition.m_fY }));
			CGameManager::GetManager()->InsertAddOnTilePosition(ETerranAddOnType::COVERT_OPS, CGeometry::ToTilePosition({ m_tPosition.m_fX + 80.0f, m_tPosition.m_fY }));
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case EScienceFacilityState::LAND:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case EScienceFacilityState::UPGRADE:
	{
		SetAnimation(m_pUpgradeAnim);
	}
	break;

	case EScienceFacilityState::DIE:
	{

	}
	break;

	default:
	break;
	}
}

void CScienceFacility::Upgrade()
{
	if (GetDead() == true)
	{
		SetScienceFacilityState(EScienceFacilityState::DIE);
		SetTarget(nullptr);
		return;
	}

	if (m_queUpgrades.empty()) { return; }
	SetScienceFacilityState(EScienceFacilityState::UPGRADE);

	float fDeltaSeconds = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fCurUpgradeDeltaSecond += fDeltaSeconds;

	switch (m_queUpgrades.front())
	{
	case ETerranUpgradeType::IRRADIATE:
	{
		if (m_fCurUpgradeDeltaSecond >= m_pIrradiateProperty->GetSeconds())
		{
			CGameManager::GetManager()->SetUpgrade(ETerranUpgradeType::IRRADIATE, true);
			CSoundManager::GetManager()->PlaySoundEx(L"tadupd02.wav", ESoundChannel::UNIT, 1.0f);
			SetScienceFacilityState(EScienceFacilityState::LAND);

			m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].erase(
				remove(m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].begin(), m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end(), ECommandType::UPGRADE_IRRADIATE),
				m_vecCommandTypes[(int32)ECommandWidgetState::STATE_A].end()
			);

			m_queUpgrades.pop_front();
			if (m_queUpgrades.empty())
			{
				SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			}

			m_fCurUpgradeDeltaSecond = 0.0f;
		}
	}
	break;
	}
}
