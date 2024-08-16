#pragma once
#include "TerranObject.h"

class CSprite;

class CMineral : public CTerranObject
{
public:
	CMineral() = default;
	virtual ~CMineral() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void SetLeftMineral(int32 _iLeftMineral) { m_iLeftMineral = _iLeftMineral; }
	int32 GetLeftMineral() const { return m_iLeftMineral; }

	void DecreaseMineral(int32 _iMineral) { m_iLeftMineral -= _iMineral; }

	void SetIsOccupied(bool _bIsMined) { m_bOccupied = _bIsMined; }
	bool GetIsOccupied() const { return m_bOccupied; }

protected:
	int32 m_iLeftMineral = 5'000;

	bool m_bOccupied = false;

public:
	CSprite* GetCurBigWireframeSprite() { return m_pMineralCurBigWireframe; }
	void SetCurBigWireframeSprite(CSprite* _pMineralCurBigWireframe) { m_pMineralCurBigWireframe = _pMineralCurBigWireframe; }

	CAnimation* GetPortraitAnim() { return m_pMineralPortrait; }
	void SetPortraitAnim(CAnimation* _pMineralPortrait) { m_pMineralPortrait = _pMineralPortrait; }

protected:
	// �̳׶� ���� �ִϸ��̼� ����
	CAnimation* m_pMineralStopAnim[3][4]{ nullptr };

	// ū ���̾������� ����
	CSprite* m_pMineralBigWireframes[6]{ nullptr };

	// ���� ü���� ū ���̾�������
	CSprite* m_pMineralCurBigWireframe = nullptr;

	// ���� �ʻ�ȭ
	CAnimation* m_pMineralPortrait = nullptr;
};

