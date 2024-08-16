#pragma once
#include "TerranProperty.h"

class CUnitProperty : public CTerranProperty
{
public:
	CUnitProperty(
		std::wstring _strName,
		ERaceType _eRaceType,
		Vector2Int _tTileSize,
		std::wstring _strRank,	// ����� ���ָ� �ֽ��ϴ�.
		int32 _iRank,			// ����� ���ָ� �ֽ��ϴ�.
		int32 _iMaxHP,
		int32 _iMaxMP,
		int32 _iMaxShield,
		int32 _iAttackPoint,
		int32 _iDefensePoint,
		float _fSpeed,
		float _fAttackDeltaSeconds,
		int32 _iSight,
		int32 _iRange,
		int32 _iMineral,
		int32 _iGas,
		int32 _iSeconds,
		int32 _iConsumeSupply);

	virtual ~CUnitProperty() = default;

public:
	std::wstring GetStrRank() const { return m_strRank; }
	int32 GetIntRank() const { return m_iRank; }
	int32 GetConsumeSupply() const { return m_iConsumeSupply; }

protected:
	// ���ڿ� ���
	std::wstring m_strRank = L"";

	// ���� ���
	int32 m_iRank = 0;

	// �Һ��ϴ� ����ǰ
	int32 m_iConsumeSupply = 0;
};

