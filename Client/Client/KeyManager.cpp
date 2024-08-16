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
		// Ű�� ���� ���
		if (asciiKeys[iKey] & 0x80)
		{
			switch (m_vecKeyStates[iKey])
			{
			// ������ �����ų� ������ ���� ���
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_vecKeyStates[iKey] = EKeyState::PRESSED;
				break;

			// ������ �ðų� ���� ���� ���
			case EKeyState::UP:
			case EKeyState::RELEASED:
				m_vecKeyStates[iKey] = EKeyState::DOWN;
				break;
			}
		}
		// Ű�� ������ ���� ���
		else
		{
			switch (m_vecKeyStates[iKey])
			{
			// ������ �����ų� ������ ���� ���
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_vecKeyStates[iKey] = EKeyState::UP;
				break;

			// ������ �ðų� ���� ���� ���
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