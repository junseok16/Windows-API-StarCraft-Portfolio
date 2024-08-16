#pragma once

class CTerranObject;

class CCommand
{
public:
	CCommand(ECommandType _eCommandType) : m_eCommandType(_eCommandType) { }
	virtual ~CCommand() = default;

public:
	ECommandType m_eCommandType = ECommandType::ENUM_END;
};

class CMove : public CCommand
{
public:
	CMove(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTarget)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition),
		m_pTarget(_pTarget) { }

	CMove(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition) { }

	virtual ~CMove() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	CTerranObject* m_pTarget = nullptr;
};

class CStop : public CCommand
{
public:
	CStop(ECommandType _eCommandType) : CCommand(_eCommandType) {	}
	virtual ~CStop() = default;
};

class CCancel : public CCommand
{
public:
	CCancel(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CCancel() = default;
};

class CGoBack : public CCommand {
public:
	CGoBack(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CGoBack() = default;
};

class CCancelLast : public CCommand {
public:
	CCancelLast(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CCancelLast() = default;
};

class CCancelUpgrade : public CCommand {
public:
	CCancelUpgrade(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CCancelUpgrade() = default;
};


class CAttack : public CCommand
{
public:
	CAttack(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTarget)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition),
		m_pTarget(_pTarget) { }

	virtual ~CAttack() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	CTerranObject* m_pTarget = nullptr;
};

class CBuild : public CCommand
{
public:
	CBuild(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CBuild() = default;
};

class CConstruct : public CCommand
{
public:
	CConstruct(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition) { }

	virtual ~CConstruct() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
};

class CUpgrade : public CCommand
{
public:
	CUpgrade(ECommandType _eCommandType) : CCommand(_eCommandType) { }
	virtual ~CUpgrade() = default;
};

class CUseStimpack : public CCommand
{
public:
	CUseStimpack(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CUseStimpack() = default;
};

class CSiegeMode : public CCommand {
public:
	CSiegeMode(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CSiegeMode() = default;
};

class CTankMode : public CCommand {
public:
	CTankMode(ECommandType _eCommandType) : CCommand(_eCommandType) {}
	virtual ~CTankMode() = default;
};

class CRallyPoint : public CCommand
{
public:
	CRallyPoint(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition) {
	}

	virtual ~CRallyPoint() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
};

class CGather : public CCommand
{
public:
	CGather(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTarget)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition),
		m_pTarget(_pTarget) { }

	virtual ~CGather() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	CTerranObject* m_pTarget = nullptr;
};

class CSkill : public CCommand
{
public:
	CSkill(ECommandType _eCommandType, CTerranObject* _pTarget)
		: CCommand(_eCommandType),
		m_pTarget(_pTarget) { }

	CSkill(ECommandType _eCommandType, Vector2Int _tDstTile, Vector2 _tDstPosition, CTerranObject* _pTarget)
		: CCommand(_eCommandType),
		m_tDstTile(_tDstTile),
		m_tDstPosition(_tDstPosition),
		m_pTarget(_pTarget) { }

	virtual ~CSkill() = default;

public:
	Vector2Int m_tDstTile{ 0, 0 };
	Vector2 m_tDstPosition{ 0.0f, 0.0f };
	CTerranObject* m_pTarget = nullptr;
};