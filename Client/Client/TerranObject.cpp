#include "pch.h"
#include "TerranObject.h"

void CTerranObject::Initialize()
{
	CAnimationObject::Initialize();
}

void CTerranObject::Update()
{
	CAnimationObject::Update();
}

void CTerranObject::LateUpdate()
{
	CAnimationObject::LateUpdate();
}

void CTerranObject::Render(HDC _hDC)
{
	CAnimationObject::Render(_hDC);
}

void CTerranObject::Release()
{
	CAnimationObject::Release();
}

void CTerranObject::PushCommandQueue(CCommand* _pCommand)
{
	VERIFY_NULLPTR(_pCommand);
	m_queCommands.push(_pCommand);
}

void CTerranObject::PopCommandQueue()
{
	if (!m_queCommands.empty())
	{
		m_queCommands.pop();
	}
}

CCommand* CTerranObject::FrontCommandQueue()
{
	if (!m_queCommands.empty())
	{
		return m_queCommands.front();
	}
	return nullptr;
}

int32 CTerranObject::SizeCommandQueue()
{
	return m_queCommands.size();
}

bool CTerranObject::IsEmptyCommandQueue()
{
	return m_queCommands.empty();
}
