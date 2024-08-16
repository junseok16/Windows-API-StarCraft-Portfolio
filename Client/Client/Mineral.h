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
	// 미네랄 정지 애니메이션 모음
	CAnimation* m_pMineralStopAnim[3][4]{ nullptr };

	// 큰 와이어프레임 모음
	CSprite* m_pMineralBigWireframes[6]{ nullptr };

	// 현재 체력의 큰 와이어프레임
	CSprite* m_pMineralCurBigWireframe = nullptr;

	// 유닛 초상화
	CAnimation* m_pMineralPortrait = nullptr;
};

