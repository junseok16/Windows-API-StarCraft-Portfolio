#include "pch.h"
#include "Mineral.h"

#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "RectangleColliderComponent.h"
#include "SelectCircleUI.h"
#include "Scene.h"

void CMineral::Initialize()
{
	CTerranObject::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::MINERAL);
	SetSize({ 64, 32 });
	SetGdiRender(true);

	// 미네랄에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 64, 32 });

	pRectCollider->SetCollisionType(ECollisionType::MINERAL);
	pRectCollider->ResetCollisionFlag();
	pRectCollider->InsertCollisionFlag(ECollisionType::GROUND_UNIT);
	pRectCollider->InsertCollisionFlag(ECollisionType::CURSOR);
	pRectCollider->InsertCollisionFlag(ECollisionType::BUILDING);
	pRectCollider->InsertCollisionFlag(ECollisionType::GATHER);

	pRectCollider->SetScroll(true);
	pRectCollider->SetDebug(false);
	InsertComponent(pRectCollider);
	CCollisionManager::GetManager()->InsertColliderComponent(pRectCollider);

	
	/********************
		AnimationObject 클래스
	********************/
	{
		m_pMineralStopAnim[0][0] = CResourceManager::GetManager()->GetAnimation(L"MnrlA0");
		m_pMineralStopAnim[0][1] = CResourceManager::GetManager()->GetAnimation(L"MnrlA1");
		m_pMineralStopAnim[0][2] = CResourceManager::GetManager()->GetAnimation(L"MnrlA2");
		m_pMineralStopAnim[0][3] = CResourceManager::GetManager()->GetAnimation(L"MnrlA3");

		m_pMineralStopAnim[1][0] = CResourceManager::GetManager()->GetAnimation(L"MnrlB0");
		m_pMineralStopAnim[1][1] = CResourceManager::GetManager()->GetAnimation(L"MnrlB1");
		m_pMineralStopAnim[1][2] = CResourceManager::GetManager()->GetAnimation(L"MnrlB2");
		m_pMineralStopAnim[1][3] = CResourceManager::GetManager()->GetAnimation(L"MnrlB3");
		
		m_pMineralStopAnim[2][0] = CResourceManager::GetManager()->GetAnimation(L"MnrlC0");
		m_pMineralStopAnim[2][1] = CResourceManager::GetManager()->GetAnimation(L"MnrlC1");
		m_pMineralStopAnim[2][2] = CResourceManager::GetManager()->GetAnimation(L"MnrlC2");
		m_pMineralStopAnim[2][3] = CResourceManager::GetManager()->GetAnimation(L"MnrlC3");

		m_pMineralPortrait			= CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");
		m_pMineralBigWireframes[0]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm0");
		m_pMineralBigWireframes[1]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm1");
		m_pMineralBigWireframes[2]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm2");
		m_pMineralBigWireframes[3]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm3");
		m_pMineralBigWireframes[4]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm4");
		m_pMineralBigWireframes[5]	= CResourceManager::GetManager()->GetSprite(L"MnrlBgWrfrm5");

		SetAnimation(m_pMineralStopAnim[rand() % 3][0]);
	}

	/********************
		TerranObject 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::MINERAL);
	SetCurCommandWidgetState(ECommandWidgetState::STATE_A);

	/********************
		인 게임 UI
	********************/
	m_pCircleUI = new CSelectCircleUI();
	m_pCircleUI->SetUIActive(false);
	m_pCircleUI->SetSprite(CResourceManager::GetManager()->GetSprite(L"AllySlct3"));
	m_pCircleUI->SetCircleOwner(this);
	m_pCircleUI->SetUIType(EUIType::DYNAMIC_UI);
	m_pCircleUI->Initialize();
	CSceneManager::GetManager()->GetCurScene()->InsertDynamicUI(m_pCircleUI);
}

void CMineral::Update()
{
	CTerranObject::Update();
}

void CMineral::LateUpdate()
{
	CTerranObject::LateUpdate();
}

void CMineral::Render(HDC _hDC)
{
	CTerranObject::Render(_hDC);
}

void CMineral::Release()
{
	CTerranObject::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
}
