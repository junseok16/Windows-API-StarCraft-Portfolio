#include "pch.h"
#include "SoundManager.h"
using namespace std;

CSoundManager* CSoundManager::s_pSoundManager = nullptr;

void CSoundManager::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	LoadSoundFile(); 
}

void CSoundManager::Release()
{
	for (auto& pair : m_mapSounds)
	{
		delete[] pair.first;
		FMOD_Sound_Release(pair.second);
	}
	m_mapSounds.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);

	VERIFY_NULLPTR(s_pSoundManager);
	SAFE_DELETE(s_pSoundManager);
}

void CSoundManager::PlaySoundEx(const TCHAR* _pSoundKey, ESoundChannel _eSoundChannel, float _fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_mapSounds.begin(), m_mapSounds.end(), [&](auto& iter)->bool { return !lstrcmp(_pSoundKey, iter.first); });
	if (iter == m_mapSounds.end()) { return; }

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(int32)_eSoundChannel]);

	/*FMOD_BOOL bPlay = FALSE; 
	if (FMOD_Channel_IsPlaying(m_pChannelArr[(int32)_eSoundChannel], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(int32)_eSoundChannel]);
	}*/

	FMOD_Channel_SetVolume(m_pChannelArr[(int32)_eSoundChannel], _fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlayBGM(const TCHAR * _pSoundKey, float _fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_mapSounds.begin(), m_mapSounds.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(_pSoundKey, iter.first);
	});
	
	if (iter == m_mapSounds.end()) { return; }
	
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(int32)ESoundChannel::BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[(int32)ESoundChannel::BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[(int32)ESoundChannel::BGM], _fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StopSound(ESoundChannel _eSoundChannel)
{
	FMOD_Channel_Stop(m_pChannelArr[(int32)_eSoundChannel]);
}

void CSoundManager::StopAll()
{
	for (int iIndex = 0; iIndex < (int32)ESoundChannel::ENUM_END; ++iIndex)
	{
		FMOD_Channel_Stop(m_pChannelArr[iIndex]);
	}
}

void CSoundManager::SetChannelVolume(ESoundChannel _eSoundChannel, float _fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[(int32)ESoundChannel::BGM], _fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::RandomPlaySound(int32 _iIndex, ESoundChannel _eSoundChannel, const std::wstring& _strName, const std::wstring& _strEx)
{
	int32 iIndex = rand() % _iIndex;
	const wstring& strPath = _strName + to_wstring(iIndex) + _strEx;
	PlaySoundEx(strPath.c_str(), _eSoundChannel, 1.0f);
}

void CSoundManager::LoadSoundFile()
{
	_finddata_t fd; 
	long handle = _findfirst("..\\Resources\\Sound\\*.*", &fd);

	if (handle == -1) { return; }
	int iResult = 0; 

	char szCurPath[128] = "..\\Resources\\Sound\\";
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 
		strcat_s(szFullPath, fd.name);// Success.wav

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1; 
			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);
			m_mapSounds.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);
	_findclose(handle);
}
