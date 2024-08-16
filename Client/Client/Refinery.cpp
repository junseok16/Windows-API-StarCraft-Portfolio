#include "pch.h"
#include "Refinery.h"

#include "GameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

#include "RectangleColliderComponent.h"
#include "BuildingProperty.h"

#include "SelectCircleUI.h"
#include "HPBarUI.h"
#include "SceneManager.h"
#include "Scene.h"

CRefinery::CRefinery(CBuildingProperty& _buildingProperty)
	: CBuilding(_buildingProperty) { }

void CRefinery::Initialize()
{
	CBuilding::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::BUILDING);
	SetSize({ 96, 64 });
	SetGdiRender(true);

	// 리파이너리에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 128, 64 });

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
	m_pCnstrctnAnim		= CResourceManager::GetManager()->GetAnimation(L"RfnryCnstrct");
	m_pLandAnim			= CResourceManager::GetManager()->GetAnimation(L"RfnryIdle");

	m_pBuildingPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

	m_pBigWireframe[0] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm0");
	m_pBigWireframe[1] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm1");
	m_pBigWireframe[2] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm2");
	m_pBigWireframe[3] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm3");
	m_pBigWireframe[4] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm4");
	m_pBigWireframe[5] = CResourceManager::GetManager()->GetSprite(L"RfnryBgWrfrm5");


	/********************
		Terran 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::BUILDING);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_F);

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
	SetTerranBuildingType(ETerranBuildingType::REFINERY);
	m_pCurBigWireframe = m_pBigWireframe[0];

	/********************
		Supply 클래스
	********************/
	SetRefineryState(ERefineryState::CONSTRUCTION);
}

void CRefinery::Update()
{
	CBuilding::Update();
	ExecuteCommand();
}

void CRefinery::LateUpdate()
{
	CBuilding::LateUpdate();
}

void CRefinery::Render(HDC _hDC)
{
	CBuilding::Render(_hDC);
}

void CRefinery::Release()
{
	CBuilding::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pHPBarUI);
}

void CRefinery::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CRefinery::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CRefinery::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) {
}

void CRefinery::ExecuteCommand()
{
	switch (m_eRefineryState)
	{
	case ERefineryState::CONSTRUCTION:
	{
		SetAnimation(m_pCnstrctnAnim);

		m_pCurCnstrctnDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();
		if (m_pCurCnstrctnDeltaSeconds >= 3.0f)
		{
			CGameManager::GetManager()->IncreaseNumBuilding(ETerranBuildingType::REFINERY, 1);
			SetCurCommandWidgetState(ECommandWidgetState::STATE_A);
			SetRefineryState(ERefineryState::IDLE);
			SetAnimation(m_pLandAnim);
			m_pCurCnstrctnDeltaSeconds = 0.0f;
		}
	}
	break;

	case ERefineryState::IDLE:
	{
		SetAnimation(m_pLandAnim);
	}
	break;

	case ERefineryState::DIE:
	{

	}
	break;

	default:
	break;
	}
}
