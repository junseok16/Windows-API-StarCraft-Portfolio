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
	// ���� ���� �ִϸ��̼� ����
	CAnimation* m_pGasStopAnim = nullptr;

	// ū ���̾������� ����
	CSprite* m_pGasBigWireframes[6]{ nullptr };

	// ���� ü���� ū ���̾�������
	CSprite* m_pGasCurBigWireframe = nullptr;

	// ���� �ʻ�ȭ
	CAnimation* m_pGasPortrait = nullptr;
};

