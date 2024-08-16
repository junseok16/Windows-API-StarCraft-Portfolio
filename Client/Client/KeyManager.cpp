#include "pch.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::s_pKeyManager = nullptr;

void CKeyManager::Initialize()
{
	m_vecKeyStates.assign(UINT8_MAX + 1, EKeyState::RELEASED);
}

void CKeyManager::Update()
{
	byte asciiKeys[UINT8_MAX + 1] = {};
	if (::GetKeyboardState(asciiKeys) == false)
	{
		return;
	}

	for (uint32 iKey = 0; iKey < UINT8_MAX + 1; iKey++)
	{
		// 키를 누른 경우
		if (asciiKeys[iKey] & 0x80)
		{
			switch (m_vecKeyStates[iKey])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_vecKeyStates[iKey] = EKeyState::PRESSED;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EKeyState::UP:
			case EKeyState::RELEASED:
				m_vecKeyStates[iKey] = EKeyState::DOWN;
				break;
			}
		}
		// 키를 누르지 않은 경우
		else
		{
			switch (m_vecKeyStates[iKey])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_vecKeyStates[iKey] = EKeyState::UP;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EKeyState::UP:
			case EKeyState::RELEASED:
				m_vecKeyStates[iKey] = EKeyState::RELEASED;
				break;
			}
		}
	}
}

void CKeyManager::Release()
{
	VERIFY_NULLPTR(s_pKeyManager);
	SAFE_DELETE(s_pKeyManager);
}