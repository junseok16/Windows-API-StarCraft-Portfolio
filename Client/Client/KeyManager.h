#pragma once

class CCommand;

class CKeyManager final
{
/***************
	메서드
***************/
private:
	CKeyManager() = default;

public:
	~CKeyManager() = default;
	CKeyManager(const CKeyManager& rhs) = delete;
	CKeyManager(CKeyManager&& rhs) = delete;
	CKeyManager& operator=(const CKeyManager& rhs) = delete;
	CKeyManager& operator=(CKeyManager&& rhs) = delete;

public:
	static CKeyManager* GetManager()
	{
		if (s_pKeyManager == nullptr)
		{
			s_pKeyManager = new CKeyManager();
		}
		return s_pKeyManager;
	}

public:
	void Initialize();
	void Update();
	void Release();

public:
	bool IsKeyDown(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::DOWN; }
	bool IsKeyPressed(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::PRESSED; }
	bool IsKeyUp(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::UP; }
	bool IsKeyReleased(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::RELEASED; }

private:
	EKeyState GetKeyState(int32 _iKey) const { return m_vecKeyStates[_iKey]; }


/***************
	데이터 멤버
***************/
public:
	static CKeyManager* s_pKeyManager;

private:
	std::vector<EKeyState> m_vecKeyStates;
};

