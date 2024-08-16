#pragma once
#include "AnimationObject.h"

enum class ECursorAnimState
{
	RELEASE,
	SCROLL,
	ROTATE,			// ȸ�� �� UI				�Ʊ�, ����, �߸��� �����Ѵ�.
	CIRCLE_ORDER,	// ���׶� �� UI				�Ʊ�, ����, �߸��� �����Ѵ�.
	CROSS_ORDER,	// ���� �ִ� ���׶� �� UI	�Ʊ�, ����, �߸��� �����Ѵ�.
	DRAG,
	ENUM_END
};

enum class ECursorCommandMode
{
	KEYBOARD_MODE,
	MOUSE_MODE,
	ENUM_END
};

enum class ECursorState
{
	RELEASE,
	DRAG,
	ENUM_END
};

class CSprite;
class CTerranObject;

class CCursor : public CAnimationObject
{
public:
	CCursor() = default;
	virtual ~CCursor() = default;

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
	void SetDirState(EDirectionState _eDirectionState) { m_eDirectionState = _eDirectionState; }
	EDirectionState GetDirState() const { return m_eDirectionState; }

	void SetCursorAnimState(ECursorAnimState _eCursorAnimState) { m_eCursorAnimState = _eCursorAnimState; }
	ECursorAnimState GetCursorAnimState() const { return m_eCursorAnimState; }

	void SetCollidedOwnerType(EOwnerType _eCollidedOwnerType) { m_eCollidedOwnerType = _eCollidedOwnerType; }
	EOwnerType GetCollidedOwnerType() const { return m_eCollidedOwnerType; }

	void SetCursorCmdMode(ECursorCommandMode _eCursorCommandMode) { m_eCursorCommandMode = _eCursorCommandMode; }
	ECursorCommandMode GetCursorCmdMode() const { return m_eCursorCommandMode; }

	void SetWatingCmdType(ECommandType _eWatingCommandType) { m_eWatingCommandType = _eWatingCommandType; }
	ECommandType GetWatingCmdType() const { return m_eWatingCommandType; }

private:
	void UpdatePosition();
	void UpdateDirection();
	void UpdateAnim();
	void SelectObject();
	void CommandSelectObject();

	void UpdateBlueprintSprite();
	
	void SetBlueprintSprite(int32 _iWidth, int32 _iHeight, const std::wstring& _strKeyO, const std::wstring& _strKeyX);
	void SetRefineryBPSprite(int32 _iWidth, int32 _iHeight, const std::wstring& _strKeyO, const std::wstring& _strKeyX);
	void SetAddOnBlueprintSprite(ETerranAddOnType _eAddOnType, int32 _iWidth, int32 _iHeight, const std::wstring& _strKeyO, const std::wstring& _strKeyX);


	void RenderCnstrctnBP(HDC _hDC);
	void RenderDragBox(HDC _hDC);

	void PlayUnitSound(CTerranObject* _pObject);
	void PlayStructureSound(CTerranObject* _pObject);
	void RandomSound(int32 _iIndex, const std::wstring& _strName, const std::wstring& _strEx);

private:
	bool IsThereObject(std::list<CObject*>& _lstObjects, std::vector<CTerranObject*>& _vecSelectedObjects, RECT& _tDragRect, bool _bClick);

private:
	ECommandType m_eWatingCommandType = ECommandType::ENUM_END;

	Vector2 m_tDragBeginPosition{ 0.0f, 0.0f };

	Vector2 m_tDragEndPosition{ 0.0f, 0.0f };

private:
	bool m_bCollided = false;

	ECursorState m_eCursorState = ECursorState::ENUM_END;

	EDirectionState m_eDirectionState = EDirectionState::ENUM_END;

	ECursorAnimState m_eCursorAnimState = ECursorAnimState::ENUM_END;

	ECursorCommandMode m_eCursorCommandMode = ECursorCommandMode::ENUM_END;

public:
	void SetCursorCommandMode(ECursorCommandMode _eCursorCommandMode) { m_eCursorCommandMode = _eCursorCommandMode; }
	void SetWaitingCommandType(ECommandType _eWatingCommandType) { m_eWatingCommandType = _eWatingCommandType; }
	void SetCurBPSprite(CSprite* _pCnstrctBPSprite) { m_pCnstrctBPSprite = _pCnstrctBPSprite; }

private:
	// Ŀ���� �浹�� ������Ʈ�� ������(�÷��̾�, �߸�, ��ǻ��)
	EOwnerType m_eCollidedOwnerType = EOwnerType::ENUM_END;

	CAnimation* m_pCrsrReleaseAnim = nullptr;
	
	CAnimation* m_pCrsrDragAnim = nullptr;
	
	CAnimation* m_pCrsrCircleOrderAnim = nullptr;
	
	CAnimation* m_pCrsrScrollAnim[(int32)EDirectionState::ENUM_END]{ nullptr };
	
	CAnimation* m_pCrsrRotateAnim[(int32)EOwnerType::ENUM_END]{ nullptr };
	
	CAnimation* m_pCrsrCrossOrderAnim[(int32)EOwnerType::ENUM_END]{ nullptr };
	
private:
	// �ǹ� û����
	CSprite* m_pCnstrctBPSprite = nullptr;

	Vector2 m_pCnstrctBPPosition{ 0.0f, 0.0f };

	Vector2 m_pCnstrctOffset{ 0.0f, 0.0f };

	bool m_bWasKeyMode = false;
};

