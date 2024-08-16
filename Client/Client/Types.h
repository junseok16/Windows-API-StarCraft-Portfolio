#pragma once

/***************
	기본 타입
***************/
using int8   =  __int8;
using int16  = __int16;
using int32  = __int32;
using int64  = __int64;
using uint8  = unsigned  __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;


/***************
	사용자 정의 타입
***************/
struct Vector2 final
{
public:
	Vector2(float _fX = 0.0f, float _fY = 0.0f) : m_fX(_fX), m_fY(_fY) {}
	Vector2(POINT _tPoint = { 0, 0 }) : m_fX((float)_tPoint.x), m_fY((float)_tPoint.y) {}
	Vector2(const Vector2& rhs) : m_fX(rhs.m_fX), m_fY(rhs.m_fY) {}
	~Vector2() = default;

public:
	Vector2& operator=(const Vector2& rhs)
	{
		if (&rhs == this) { return *this; }
		m_fX = rhs.m_fX;
		m_fY = rhs.m_fY;
		return *this;
	}

	Vector2 operator+(const Vector2& rhs)
	{
		Vector2 plus(0.0f, 0.0f);
		plus.m_fX = m_fX + rhs.m_fX;
		plus.m_fY = m_fY + rhs.m_fY;
		return plus;
	}

	Vector2 operator-(const Vector2& rhs)
	{
		Vector2 minus(0.0f, 0.0f);
		minus.m_fX = m_fX - rhs.m_fX;
		minus.m_fY = m_fY - rhs.m_fY;
		return minus;
	}

	Vector2 operator*(float _fOperand)
	{
		Vector2 multiply(0.0f, 0.0f);
		multiply.m_fX = m_fX * _fOperand;
		multiply.m_fY = m_fY * _fOperand;
		return multiply;
	}

	Vector2 operator/(float _fOperand)
	{
		if (_fOperand < 0.000'001f) { return *this; }
		Vector2 divide(0.0f, 0.0f);
		divide.m_fX = m_fX * _fOperand;
		divide.m_fY = m_fY * _fOperand;
		return divide;
	}

	void operator+=(const Vector2& rhs)
	{
		m_fX += rhs.m_fX;
		m_fY += rhs.m_fY;
	}

	void operator-=(const Vector2& rhs)
	{
		m_fX -= rhs.m_fX;
		m_fY -= rhs.m_fY;
	}

	void operator*=(float _fOperand)
	{
		m_fX *= _fOperand;
		m_fY *= _fOperand;
	}

	void operator/=(float _fOperand)
	{
		if (_fOperand < 0.000'001f) { return; }
		m_fX /= _fOperand;
		m_fY /= _fOperand;
	}

public:
	void Normalize()
	{
		float fMagnitude = Magnitude();
		if (fMagnitude < 0.000'001f) { return; }
		m_fX /= fMagnitude;
		m_fY /= fMagnitude;
	}

	float Magnitude()
	{
		return sqrtf(SqrMagnitude());
	}

	float SqrMagnitude()
	{
		return m_fX * m_fX + m_fY * m_fY;
	}

	float Distance(const Vector2& rhs)
	{
		return sqrtf((m_fX - rhs.m_fX) * (m_fX - rhs.m_fX) + (m_fY - rhs.m_fY) * (m_fY - rhs.m_fY));
	}

	float DotProduct(const Vector2& rhs)
	{
		return m_fX * rhs.m_fX + m_fY * rhs.m_fY;
	}

public:
	static Vector2 PointToVector2(POINT _tPoint)
	{
		return Vector2((float)_tPoint.x, (float)_tPoint.y);
	}

	static POINT Vector2ToPoint(Vector2 _tVector2)
	{
		return POINT((int32)_tVector2.m_fX, (int32)_tVector2.m_fY);
	}

public:
	union
	{
		float m_fX = 0.0f;
		float m_fWidth;
	};

	union
	{
		float m_fY = 0.0f;
		float m_fHeight;
	};
};

struct Vector2Int final
{
public:
	Vector2Int(int32 _iX = 0, int32 _iY = 0) : m_iX(_iX), m_iY(_iY) {}

	Vector2Int(POINT _tPoint) : m_iX(_tPoint.x), m_iY(_tPoint.y) {}

	Vector2Int(const Vector2Int& rhs) : m_iX(rhs.m_iX), m_iY(rhs.m_iY) {}

	~Vector2Int() = default;

public:
	Vector2Int& operator=(const Vector2Int& rhs)
	{
		if (&rhs == this) { return *this; }
		m_iX = rhs.m_iX;
		m_iY = rhs.m_iY;
		return *this;
	}

	Vector2Int operator+(const Vector2Int& rhs)
	{
		Vector2Int plus(0, 0);
		plus.m_iX = m_iX + rhs.m_iX;
		plus.m_iY = m_iY + rhs.m_iY;
		return plus;
	}

	Vector2Int operator-(const Vector2Int& rhs)
	{
		Vector2Int minus(0, 0);
		minus.m_iX = m_iX - rhs.m_iX;
		minus.m_iY = m_iY - rhs.m_iY;
		return minus;
	}

	Vector2Int operator*(int32 _fOperand)
	{
		Vector2Int multiply(0, 0);
		multiply.m_iX = m_iX * _fOperand;
		multiply.m_iY = m_iY * _fOperand;
		return multiply;
	}

	Vector2Int operator/(int32 _fOperand)
	{
		if (_fOperand < 0.000'001f) { return *this; }
		Vector2Int divide(0, 0);
		divide.m_iX = m_iX * _fOperand;
		divide.m_iY = m_iY * _fOperand;
		return divide;
	}

	void operator+=(const Vector2Int& rhs)
	{
		m_iX += rhs.m_iX;
		m_iY += rhs.m_iY;
	}

	void operator-=(const Vector2Int& rhs)
	{
		m_iX -= rhs.m_iX;
		m_iY -= rhs.m_iY;
	}

	void operator*=(int32 _fOperand)
	{
		m_iX *= _fOperand;
		m_iY *= _fOperand;
	}

	void operator/=(int32 _fOperand)
	{
		if (_fOperand < 0.000'001f) { return; }
		m_iX /= _fOperand;
		m_iY /= _fOperand;
	}

	bool operator==(const Vector2Int& rhs)
	{
		return (m_iX == rhs.m_iX && m_iY == rhs.m_iY);
	}

public:
	static Vector2Int PointToVector2(POINT _tPoint)
	{
		return Vector2Int(_tPoint.x, _tPoint.y);
	}

public:
	union
	{
		int32 m_iX = 0;
		int32 m_iWidth;
	};

	union
	{
		int32 m_iY = 0;
		int32 m_iHeight;
	};
};

using Vec2 = Vector2;

using Vec2Int = Vector2Int;

struct tagTileInfo final
{
	ETileType m_eTileType = ETileType::PASSABLE;
	EOwnerType m_eOwnerType = EOwnerType::PLAYER;
};

using Vec2Map = std::vector<std::vector<tagTileInfo>>;

/* Vec2MapInfo: 맵정보, 맵의 최대크기, 맵의 출발지점, 맵의 도착지점 */
struct Vec2MapInfo
{
	Vec2Map tMap;

	int32 iMapCol;
	int32 iMapRow;

	int32 iStartX;
	int32 iStartY;

	int32 iDestX;
	int32 iDestY;
};

/* CostCoord: 한 정점의 좌표와 비용 */
struct CostCoord
{
	int32 iCost;
	int32 iX, iY;
};

/* Coord: 한 정점의 좌표 */
struct Coord
{
	int32 iX, iY;
};

/* CellDetails: 비용과 부모노드 */
struct CellDetails
{
	int32 f, g, h;
	int32 iParentX, iParentY;
};

/* PointDecl: 맵에 표기 되어있는 문자의 역할 */
struct PointDecl
{
	std::string strBeginPoint;
	std::string strDestinationPoint;
	std::string strVoid;
	std::string strWall;
	std::string strTracedPath;
};