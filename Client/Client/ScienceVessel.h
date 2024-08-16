#pragma once
#include "Unit.h"

enum class EScienceVesselState
{
	STOP,
	MOVE,
	DEFENSIVE_MATRIX,
	IRRADIATE,
	DIE,
	ENUM_END,
};

class CRectangleColliderComponent;

class CScienceVessel : public CUnit {
public:
	CScienceVessel(CUnitProperty& _unitProperty);
	virtual ~CScienceVessel() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;
	virtual void OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;
	virtual void OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider) override;

public:
	void SetScienceVesselState(EScienceVesselState _eScienceVesselState) { m_eScienceVesselState = _eScienceVesselState; }
	EScienceVesselState GetScienceVesselState() const { return m_eScienceVesselState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void UpdateHead();
	void RenderHead(HDC _hDC);

private:
	EScienceVesselState m_eScienceVesselState = EScienceVesselState::ENUM_END;

	CRectangleColliderComponent* pRectCollider = nullptr;

	float m_bUseIrdt = false;

	// 사이언스 배슬 머리
	Vector2 m_tHdPosition{ 0.0f, 0.0f };

	CSprite* m_pCurHdSprite = nullptr;

	CSprite* m_ScncVslHdSprite[8]{ nullptr };
};

