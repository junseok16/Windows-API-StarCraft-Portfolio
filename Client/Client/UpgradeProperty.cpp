#include "pch.h"
#include "UpgradeProperty.h"

CUpgradeProperty::CUpgradeProperty(
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
	int32 _iConsumeSupply)
	: CTerranProperty(
		_strName,
		_eRaceType,
		_tTileSize,
		_iMaxHP,
		_iMaxMP,
		_iMaxShield,
		_iAttackPoint,
		_iDefensePoint,
		_fSpeed,
		_fAttackDeltaSeconds,
		_iSight,
		_iRange,
		_iMineral,
		_iGas,
		_iSeconds),
	m_iConsumeSupply(_iConsumeSupply) { }
