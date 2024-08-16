#pragma once
#include "TerranObject.h"

class CSprite;

class CVespeneGas : public CTerranObject
{
public:
	CVespeneGas() = default;
	virtual ~CVespeneGas() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetLeftGas(int32 _iLeftGas) { m_iLeftGas = _iLeftGas; }
	int32 GetLeftGas() const { return m_iLeftGas; }

	void DecreaseGas(int32 _iGas) { m_iLeftGas -= _iGas; }

protected:
	int32 m_iLeftGas = 5'000;

public:
	CSprite* GetCurBigWireframeSprite() { return m_pGasCurBigWireframe; }
	void SetCurBigWireframeSprite(CSprite* _pGasCurBigWireframe) { m_pGasCurBigWireframe = _pGasCurBigWireframe; }

	CAnimation* GetPortraitAnim() { return m_pGasPortrait; }
	void SetPortraitAnim(CAnimation* _pGasPortrait) { m_pGasPortrait = _pGasPortrait; }

protected:
	// 가스 정지 애니메이션 모음
	CAnimation* m_pGasStopAnim = nullptr;

	// 큰 와이어프레임 모음
	CSprite* m_pGasBigWireframes[6]{ nullptr };

	// 현재 체력의 큰 와이어프레임
	CSprite* m_pGasCurBigWireframe = nullptr;

	// 유닛 초상화
	CAnimation* m_pGasPortrait = nullptr;
};

