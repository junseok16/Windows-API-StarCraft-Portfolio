#include "pch.h"
#include "VespeneGas.h"

#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "RectangleColliderComponent.h"
#include "SelectCircleUI.h"
#include "Scene.h"

void CVespeneGas::Initialize()
{
	CTerranObject::Initialize();

	/********************
		Object 클래스
	********************/
	SetObjectType(EObjectType::MINERAL);
	SetSize({ 128, 64 });
	SetGdiRender(true);

	// 미네랄에 사각형 콜라이더 컴포넌트를 붙입니다.
	CRectangleColliderComponent* pRectCollider = new CRectangleColliderComponent();
	pRectCollider->SetColliderType(EColliderType::RECTANGLE);
	pRectCollider->SetComponentOwner(this);
	pRectCollider->SetColliderSize({ 128, 64 });

	pRectCollider->SetCollisionType(ECollisionType::GAS);
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
		m_pGasStopAnim = CResourceManager::GetManager()->GetAnimation(L"VspnGas");
		
		m_pGasPortrait = CResourceManager::GetManager()->GetAnimation(L"AdvsrPrtrt");

		m_pGasBigWireframes[0] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm0");
		m_pGasBigWireframes[1] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm1");
		m_pGasBigWireframes[2] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm2");
		m_pGasBigWireframes[3] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm3");
		m_pGasBigWireframes[4] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm4");
		m_pGasBigWireframes[5] = CResourceManager::GetManager()->GetSprite(L"VspnGasBgWrfrm5");

		SetAnimation(m_pGasStopAnim);
	}

	/********************
		TerranObject 클래스
	********************/
	SetTerranObjectType(ETerranObjectType::VESPENE_GAS);
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

void CVespeneGas::Update()
{
	CTerranObject::Update();
}

void CVespeneGas::LateUpdate()
{
	CTerranObject::LateUpdate();
}

void CVespeneGas::Render(HDC _hDC)
{
	CTerranObject::Render(_hDC);
}

void CVespeneGas::Release()
{
	CTerranObject::Release();
	CSceneManager::GetManager()->GetCurScene()->EraseDynamicUI(m_pCircleUI);
}
