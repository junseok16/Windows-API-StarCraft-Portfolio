#pragma once

class CColliderComponent;
class CRectangleColliderComponent;
class CCircleColliderComponent;
class CObject;

class CCollisionManager final
{
/***************
	메서드
***************/
private:
	CCollisionManager() = default;

public:
	~CCollisionManager() = default;
	CCollisionManager(const CCollisionManager& rhs) = delete;
	CCollisionManager(CCollisionManager&& rhs) = delete;
	CCollisionManager& operator=(const CCollisionManager& rhs) = delete;
	CCollisionManager& operator=(CCollisionManager&& rhs) = delete;

public:
	static CCollisionManager* GetManager()
	{
		if (s_pCollisionManager == nullptr)
		{
			s_pCollisionManager = new CCollisionManager();
		}
		return s_pCollisionManager;
	}

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Release();

public:
	void InsertColliderComponent(CColliderComponent* _pColliderComponent);
	void EraseColliderComponent(CColliderComponent* _pColliderComponent);

/***************
	정적 함수
***************/
public:
	static bool IntersectRect2Rect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst);
	static bool IntersectRect2Circle(CRectangleColliderComponent* _pSrc, CCircleColliderComponent* _pDst);
	static bool IntersectCircle2Circle(CCircleColliderComponent* _pSrc, CCircleColliderComponent* _pDst);
	
	static void BlockRect2Rect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst, float _fRatio);
	static void BlockSrcRectFromDstRect(CRectangleColliderComponent* _pSrc, CRectangleColliderComponent* _pDst, float _fRatio);
	static void BlockCircle2Circle(CCircleColliderComponent* _pSrc, CCircleColliderComponent* _pDst, float _fRatio);

/***************
	데이터 멤버
***************/
public:
	static CCollisionManager* s_pCollisionManager;

private:
	// 콜라이더 컴포넌트
	std::vector<CColliderComponent*> m_vecColliderComponents;
};

