#pragma once

/***************
	전처리기
***************/
#define VERIFY_NULLPTR(_ptr) if (_ptr == nullptr) { return; }

#define _CRTDEBG_MAP_ALLOC
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


/***************
	심볼릭 상수
***************/
const int IWINCX = 800;
const int IWINCY = 600;
const float FWINCX = 800.0f;
const float FWINCY = 600.0f;

const int IWORLDCX = 4096;
const int IWORLDCY = 4096;
const float FWORLDCX = 4096.0f;
const float FWORLDCY = 4096.0f;

const int ITILECX = 32;
const int ITILECY = 32;
const float FTILECX = 32.0f;
const float FTILECY = 32.0f;

const int ITILEMAPCX = 128;
const int ITILEMAPCY = 128;

const float PI = 3.141592f;
const float SCROLL_SPEED = 1024.0f;
const int INF = 999'999'999;

/***************
	템플릿
***************/
template<typename T>
void SAFE_DELETE(T& _ptr)
{
	if (_ptr)
	{
		delete _ptr;
		_ptr = nullptr;
	}
}

struct SAFE_DELETE_FUNCTOR
{
	template<typename T>
	void operator()(T& _ptr)
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
};
