#include "pch.h"
#include "SupplyDepot.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "RectangleColliderComponent.h"
#include "BuildingProperty.h"
#include "SelectCircleUI.h"
#include "HPBarUI.h"

CSupplyDepot::CSupplyDepot(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CSupplyDepot::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object Ŭ����
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 96, 64 });
	SetGdiRender(true);

	// �跰�� �簢�� �ݶ��̴� ������Ʈ�� ���Դϴ�.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 64, 48 });

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
		AnimationObject Ŭ����
	********************/
	m_pCnstrctnAnim	= CResourceManager::GetManager()->GetAnimation(L"SplyDptCnstrctn");
	m_pLandAnim = CResourceManager::GetManager()->GetAnimation(L"SplyDptIdle");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"SplyDptBgWrfrm5");


	/********************
		Terran Ŭ����
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_F);


	/********************
		�� ���� UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct6"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);

	m_pHPBarUI = new CHPBarUI();
	m_pHPBarUI->SetUIActive(false);
	m_pHPBarUI->SetBarOwner(this);
	m_pHPBarUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pHPBarUI->SetDistance(48.0f);
	m_pHPBarUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pHPBarUI);


	/********************
		Building Ŭ����
	********************/
	SetCurHP(m_buildingProperty.GetMaxHP());
	SetCurMP(0);
	SetCurShield(0);
	SetTerranBuildingType(ETerranBuildingType::SUPPLY_DEPOT);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_F);

	/********************
		Supply Ŭ����
	********************/
	SetSupplyDepotState(ESupplyDepotState::CONSTRUCTION);
	SetAnimation(m_pCnstrctnAnim);
	m_pCurBigWireframe = m_pBigWireframe[0];
}

void CSupplyDepot::Update()
{
	CBuilding::Update();
	ExecuteCommand();
}

void CSupplyDepot::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CSupplyDepot::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CSupplyDepot::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CSupplyDepot::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CSupplyDepot::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CSupplyDepot::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CSupplyDepot::ExecuteCommand()
{
	switch (m_eSupplyDepotState)
	{
	case ESupplyDepotState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::SUPPLY_DEPOT, 1);
			CGameManager::GetManager()->IncreaseProducedSupply(8);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetSupplyDepotState(ESupplyDepotState::IDLE);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case ESupplyDepotState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case ESupplyDepotState::DIE:
	{

	}
	break;

	default:
	break;
	}
}
