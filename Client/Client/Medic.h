#pragma once
#include "Unit.h"

enum class EMedicState
{
    STOP,
    MOVE,
    HEAL,
    DIE,
    ENUM_END
};

class CMedic : public CUnit
{
public:
	CMedic(CUnitProperty& _unitProperty);
	virtual ~CMedic() = default;

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
	void SetMedicState(EMedicState _eMedicState) { m_eMedicState = _eMedicState; }
	EMedicState GetMedicState() const { return m_eMedicState; }

	virtual void UpdateDirection() override;

private:
	void AnalyseCommand();
	void ExecuteCommand();

private:
	// ¸Þµñ »óÅÂ
	EMedicState m_eMedicState = EMedicState::ENUM_END;
};

