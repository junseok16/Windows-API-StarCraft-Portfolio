#pragma once

class CResourceEx
{
public:
	CResourceEx() = default;
	virtual ~CResourceEx() = default;

public:
	virtual void LoadFile(const std::wstring& _strPath) {};
	virtual void SaveFile(const std::wstring& _strPath) {};
};

