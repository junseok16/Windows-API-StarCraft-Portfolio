#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CompeteScene.h"
#include "TestScene.h"
using namespace std;

CSceneManager* CSceneManager::s_pSceneManager = nullptr;

void CSceneManager::Initialize()
{
	VERIFY_NULLPTR(m_pCurScene);
	m_pCurScene->Initialize();
}

void CSceneManager::Update()
{
	VERIFY_NULLPTR(m_pCurScene);
	m_pCurScene->Update();
}

void CSceneManager::LateUpdate()
{
	VERIFY_NULLPTR(m_pCurScene);
	m_pCurScene->LateUpdate();
}

void CSceneManager::Render(HDC _hDC)
{
	VERIFY_NULLPTR(m_pCurScene);
	m_pCurScene->Render(_hDC);
}

void CSceneManager::Release()
{
	VERIFY_NULLPTR(m_pCurScene);
	m_pCurScene->Release();
	SAFE_DELETE(m_pCurScene);

	// TODO: s_pSceneManager ������ ���� �����ؾ� �մϴ�.
	VERIFY_NULLPTR(s_pSceneManager);
	SAFE_DELETE(s_pSceneManager);
}

void CSceneManager::OpenScene(ESceneType _eSceneType)
{
	if (m_eCurSceneType == _eSceneType) { return; }

	CScene* pScene = nullptr;
	switch (_eSceneType)
	{
		// TODO: ���� �����մϴ�.
	case ESceneType::TEST:
		pScene = new CTestScene();
		break;

	case ESceneType::COMPETE:
		pScene = new CCompeteScene();
		break;

	case ESceneType::ENUM_END:
		break;
	}

	// TODO: ���� ���� ���� �ִ� �����͸� �Ҹ��Ű��, �ŵ� �Ҹ��ŵ�ϴ�.
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		SAFE_DELETE(m_pCurScene);
	}

	VERIFY_NULLPTR(pScene);
	m_pCurScene = pScene;
	m_ePrevSceneType = m_eCurSceneType;
	m_eCurSceneType = _eSceneType;
	m_pCurScene->Initialize();
}
