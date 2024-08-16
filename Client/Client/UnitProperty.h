#pragma once
#include "TerranProperty.h"

class CUnitProperty : public CTerranProperty
{
public:
	CUnitProperty(
		std::wstring _strName,
		ERaceType _eRaceType,
		Vector2Int _tTileSize,
		std::wstring _strRank,	// 계급은 유닛만 있습니다.
		int32 _iRank,			// 계급은 유닛만 있습니다.
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
	// 문자열 계급
	std::wstring m_strRank = L"";

	// 정수 계급
	int32 m_iRank = 0;

	// 소비하는 보급품
	int32 m_iConsumeSupply = 0;
};

