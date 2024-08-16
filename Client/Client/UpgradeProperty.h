#pragma once
#include "TerranProperty.h"

class CUpgradeProperty : public CTerranProperty
{
public:
	CUpgradeProperty(
		std::wstring _strName,
		ERaceType _eRaceType,
		Vector2Int _tTileSize,
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

	virtual ~CUpgradeProperty() = default;

public:
	int32 GetConsumeSupply() const { return m_iConsumeSupply; }

	// 소비하는 보급품
	int32 m_iConsumeSupply = 0;
};

