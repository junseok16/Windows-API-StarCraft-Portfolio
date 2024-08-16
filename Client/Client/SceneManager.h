#pragma once

class CScene;

class CSceneManager final
{
private:
	CSceneManager() = default;

public:
	~CSceneManager() = default;

public:
	static CSceneManager* GetManager()
	{
		if (s_pSceneManager == nullptr)
		{
			s_pSceneManager = new CSceneManager();
		}
		return s_pSceneManager;
	}

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

public:
	void OpenScene(ESceneType _eSceneType);
	CScene* GetCurScene() const { return m_pCurScene; };

public:
	static CSceneManager* s_pSceneManager;

private:
	ESceneType m_eCurSceneType = ESceneType::ENUM_END;
	ESceneType m_ePrevSceneType = ESceneType::ENUM_END;
	CScene* m_pCurScene = nullptr;
};

