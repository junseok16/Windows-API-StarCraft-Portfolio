#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "UI.h"

CPlayer* CScene::s_pPlayer = nullptr;

CCursor* CScene::s_pCursor = nullptr;

void CScene::Initialize()
{
	// 신에 있는 오브젝트를 초기화합니다.
	for (const auto& lst : m_lstObjects)
	{
		for (const auto& pObject : lst)
		{
			pObject->Initialize();
		}
	}

	// 신에 있는 UI를 초기화합니다.
	for (const auto& pUI : m_lstStaticUIs)
	{
		pUI->Initialize();
	}

	for (const auto& pUI : m_lstDynamicUIs)
	{
		pUI->Initialize();
	}
}

void CScene::Update()
{
	// 신에 있는 오브젝트를 업데이트합니다.
	for (const auto& lst : m_lstObjects)
	{
		for (const auto& pObject : lst)
		{
			pObject->Update();
		}
	}

	// 신에 있는 UI를 업데이트합니다.
	for (const auto& pUI : m_lstStaticUIs)
	{
		pUI->Update();
	}

	for (const auto& pUI : m_lstDynamicUIs)
	{
		pUI->Update();
	}
}

void CScene::LateUpdate()
{
	// 신에 있는 오브젝트를 레이트 업데이트합니다.
	for (const auto& lst : m_lstObjects)
	{
		for (const auto& pObject : lst)
		{
			pObject->LateUpdate();
		}
	}

	// 신에 있는 UI를 레이트 업데이트합니다.
	for (const auto& pUI : m_lstStaticUIs)
	{
		pUI->LateUpdate();
	}

	for (const auto& pUI : m_lstDynamicUIs)
	{
		pUI->LateUpdate();
	}
}

void CScene::Render(HDC _hDC)
{

	for (const auto& pUI : m_lstDynamicUIs)
	{
		pUI->Render(_hDC);
	}

	// 신에 있는 오브젝트를 렌더합니다.
	for (const auto& lst : m_lstObjects)
	{
		for (const auto& pObject : lst)
		{
			pObject->Render(_hDC);
		}
	}                                                      


	// 신에 있는 UI를 레이트 렌더합니다.
	for (const auto& pUI : m_lstStaticUIs)
	{
		pUI->Render(_hDC);
	}
}

void CScene::Release()
{
	// TODO: 신에 있는 오브젝트를 해제합니다.
	for (auto& lst : m_lstObjects)
	{
		for (auto& pObject : lst)
		{
			pObject->Release();
			SAFE_DELETE(pObject);
		}
	}
	m_lstObjects->clear();

	for (auto& pUI : m_lstStaticUIs)
	{
		pUI->Release();
		SAFE_DELETE(pUI);
	}
	m_lstStaticUIs.clear();

	for (auto& pUI : m_lstDynamicUIs)
	{
		pUI->Release();
		SAFE_DELETE(pUI);
	}
	m_lstDynamicUIs.clear();
}

void CScene::InsertObject(CObject* _pObject)
{
	VERIFY_NULLPTR(_pObject);
	m_lstObjects[(int32)_pObject->GetObjectType()].push_back(_pObject);
}

void CScene::EraseObject(CObject* _pObject)
{
	VERIFY_NULLPTR(_pObject);
	m_lstObjects[(int32)_pObject->GetObjectType()].remove(_pObject);

	// TODO: 오브젝트 메모리를 여기서 해제해도 될까?
	SAFE_DELETE(_pObject);
}

void CScene::InsertStaticUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_lstStaticUIs.push_back(_pUI);
}

void CScene::EraseStaticUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_lstStaticUIs.remove(_pUI);

	SAFE_DELETE(_pUI);
}

void CScene::InsertDynamicUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_lstDynamicUIs.push_back(_pUI);
}

void CScene::EraseDynamicUI(CUI* _pUI)
{
	VERIFY_NULLPTR(_pUI);
	m_lstDynamicUIs.remove(_pUI);

	SAFE_DELETE(_pUI);
}