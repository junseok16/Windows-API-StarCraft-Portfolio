#pragma once
#include "Unit.h"

enum class ESCVState
{
	STOP,
	MOVE,
	ATTACK,
	BUILD,
	CONSTRUCT,

	MOVE_TO_GATHER,

	GATHER,
	RETURN_CARGO,
	DIE,
	ENUM_END	
};

class CBuildingProperty;
class CRectangleColliderComponent;

class CSCV : public CUnit
{
public:
	CSCV(CUnitProperty& _unitProperty);
	virtual ~CSCV() = default;

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
	void SetSCVState(ESCVState _eSCVState) { m_eSCVState = _eSCVState; }
	ESCVState GetSCVState() const { return m_eSCVState; }

	std::vector<ECommandType> GetBscStrctrCommandTypes() { return m_vecBscStrctrCmdTypes; }
	std::vector<ECommandType> GetAdvStrctrCommandTypes() { return m_vecAdvStrctrCmdTypes; }

private:
	void AnalyseCommand();
	void ExecuteCommand();
	void RenderResource(HDC _hDC);
	void UpdateOrbPosition();

private:
	CBuildingProperty* m_pCommandCenterProperty = nullptr;
	CBuildingProperty* m_pSupplyDepotProperty = nullptr;
	CBuildingProperty* m_pRefineryProperty = nullptr;
	CBuildingProperty* m_pBarracksProperty = nullptr;
	CBuildingProperty* m_pEngineeringBayProperty = nullptr;
	CBuildingProperty* m_pAcademyProperty = nullptr;
	CBuildingProperty* m_pFactoryProperty = nullptr;
	CBuildingProperty* m_pStarportProperty = nullptr;
	CBuildingProperty* m_pScienceFacilityProperty = nullptr;
	CBuildingProperty* m_pArmoryProperty = nullptr;

private:
	// SCV ����
	ESCVState m_eSCVState = ESCVState::ENUM_END;

	ECommandType m_eCommandType = ECommandType::ENUM_END;


	// SCV�� ���� �ִ� �⺻ �ǹ� ��ɾ� ����
	std::vector<ECommandType> m_vecBscStrctrCmdTypes;

	// SCV�� ���� �ִ� ���� �ǹ� ��ɾ� ����
	std::vector<ECommandType> m_vecAdvStrctrCmdTypes;

	// �簢�� �ݶ��̴�
	CRectangleColliderComponent* pRectCollider = nullptr;

private:
	int32 m_iBuildDirection = -1;

	// �Ǽ� �ð� ī����(3��)
	float m_fSumCnstrctDeltaSeconds = 0.0f;

	// ä�� �ð� ī����
	float m_fSumGthrMnrlDeltaSeconds = 0.0f;

	Vector2Int m_tMnrlTile = { 0, 0 };

	Vector2Int m_tCmdCntrTile = { 0, 0 };

private:
	CSprite* m_pCurResourceSprite = nullptr;

	CSprite* m_pMineralOrb = nullptr;

	CSprite* m_pGasOrb = nullptr;

	Vector2 m_tOrbPosition = { 0.0f, 0.0f };
};

