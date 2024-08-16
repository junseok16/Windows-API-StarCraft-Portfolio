#include "pch.h"
#include "TerranProperty.h"

CTerranProperty::CTerranProperty(
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
	int32 _iSeconds)
	: m_strName(_strName),
	m_eRaceType(_eRaceType),
	m_tTileSize(_tTileSize),
	m_iMaxHP(_iMaxHP),
	m_iMaxMP(_iMaxMP),
	m_iMaxShield(_iMaxShield),
	m_iAttackPoint(_iAttackPoint),
	m_iDefensePoint(_iDefensePoint),
	m_fSpeed(_fSpeed),
	m_fAttackDeltaSeconds(_fAttackDeltaSeconds),
	m_iSight(_iSight),
	m_iRange(_iRange),
	m_iMineral(_iMineral),
	m_iGas(_iGas),
	m_iSeconds(_iSeconds)
{

}