#pragma once

class CSoundManager final
{
private:
	CSoundManager() = default;

public:
	~CSoundManager() = default;
	CSoundManager(const CSoundManager& rhs) = delete;
	CSoundManager(CSoundManager&& rhs) = delete;
	CSoundManager& operator=(const CSoundManager& rhs) = delete;
	CSoundManager& operator=(CSoundManager&& rhs) = delete;

public:
	static CSoundManager* GetManager() {
		if (s_pSoundManager == nullptr)
		{
			s_pSoundManager = new CSoundManager();
		}
		return s_pSoundManager;
	}

public:
	void Initialize(); 
	void Release(); 

public:
	void PlaySoundEx(const TCHAR* _pSoundKey, ESoundChannel _eSoundChannel, float _fVolume);
	void PlayBGM(const TCHAR* _pSoundKey, float _fVolume);
	void StopSound(ESoundChannel _eSoundChannel);
	void StopAll();
	void SetChannelVolume(ESoundChannel _eSoundChannel, float _fVolume);
	void RandomPlaySound(int32 _iIndex, ESoundChannel _eSoundChannel, const std::wstring& _strName, const std::wstring& _strEx);

private:
	void LoadSoundFile();

/***************
	µ•¿Ã≈Õ ∏‚πˆ
***************/
public:
	static CSoundManager* s_pSoundManager;

private:
	std::map<TCHAR*, FMOD_SOUND*> m_mapSounds; 
	FMOD_CHANNEL* m_pChannelArr[(int32)ESoundChannel::ENUM_END]{ nullptr };
	FMOD_SYSTEM* m_pSystem = nullptr;
};

