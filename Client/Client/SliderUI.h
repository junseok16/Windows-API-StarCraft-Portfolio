#pragma once
#include "UI.h"

// TODO: 체력바를 만들 때 다시 옵니다.
class CSliderUI : public CUI
{
public:
	CSliderUI() = default;
	virtual ~CSliderUI() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	Vector2 GetBackRectPosition() { return m_tBackRectPosition; }
	void SetBackRectPosition(Vector2 _tBackRectPosition) { m_tBackRectPosition = _tBackRectPosition; }

	Vector2 GetFillRectPosition() { return m_tFillRectPosition; }
	void SetFillRectPosition(Vector2 _tFillRectPosition) { m_tFillRectPosition = _tFillRectPosition; }

	Vector2Int GetBackRectSize() { return m_tBackRectSize; }
	void SetBackRectSize(Vector2Int _tBackRectSize) { m_tBackRectSize = _tBackRectSize; }

	Vector2Int GetFillRectSize() { return m_tFillRectSize; }
	void SetFillRectSize(Vector2Int _tFillRectSize) { m_tFillRectSize = _tFillRectSize; }

	int32 GetBackRectColor() const { return m_iBackColor; }
	void SetBackRectColor(int32 _iBackColor) { m_iBackColor = _iBackColor; }

	int32 GetFillRectColor() const { return m_iFillColor; }
	void SetFillRectColor(int32 _iFillColor) { m_iFillColor = _iFillColor; }

	int32 GetBackRectBorderColor() const { return m_iBackBorderColor; }
	void SetBackRectBorderColor(int32 _iBackBorderColor) { m_iBackBorderColor = _iBackBorderColor; }

	int32 GetFillRectBorderColor() const { return m_iFillBorderColor; }
	void SetFillRectBorderColor(int32 _iFillBorderColor) { m_iFillBorderColor = _iFillBorderColor; }

	float GetFillAmount() const { return m_fFillAmount; }
	void SetFillAmount(float _fFillAmount) { m_fFillAmount = _fFillAmount; }

protected:
	// 배경 사각형의 위치와 크기
	Vector2 m_tBackRectPosition{ 0.0f, 0.0f };
	Vector2Int m_tBackRectSize{ 0, 0 };

	// 채워지는 사각형의 위치와 크기
	Vector2 m_tFillRectPosition{ 0.0f, 0.0f };
	Vector2Int m_tFillRectSize{ 0, 0 };

	// 배경 사각형의 색상, 테두리 색상
	int32 m_iBackColor = 0;
	int32 m_iBackBorderColor = 0;

	// 채워지는 사각형의 색상, 테두리 색상
	int32 m_iFillColor = 0;
	int32 m_iFillBorderColor = 0;

	// 채워지는 사각형이 채워진 정도
	float m_fFillAmount = 1.0f;
};

