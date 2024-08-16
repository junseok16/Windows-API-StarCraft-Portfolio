#include "pch.h"
#include "Unit.h"
#include "UnitProperty.h"

#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "DynamicTilemapObject.h"
#include "Animation.h"
#include "Sprite.h"

#include "RectangleColliderComponent.h"
using namespace std;

CUnit::CUnit(CUnitProperty& _unitProperty)
	: m_unitProperty(_unitProperty) { }

void CUnit::Initialize()
{
	CAnimationObject::Initialize();
}

void CUnit::Update()
{
	CAnimationObject::Update();
	UpdateDynamicTilemap();
	UpdateWireframe();
	UpdateHitedSprite();
	UpdateHitingSprite();
}

void CUnit::LateUpdate()
{
	CAnimationObject::LateUpdate();
}

void CUnit::Render(HDC _hDC)
{
	CAnimationObject::Render(_hDC);
	RenderHitedSprite(_hDC);
	RenderHitingSprite(_hDC);
}

void CUnit::Release()
{
	CAnimationObject::Release();
}

void CUnit::OnCollisionEnter2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CRectangleColliderComponent* _pSrcRectCmpnt = dynamic_cast<CRectangleColliderComponent*>(_pSrcCollider);
	CRectangleColliderComponent* _pDstRectCmpnt = dynamic_cast<CRectangleColliderComponent*>(_pDstCollider);

	CTerranObject* pSrcTerranObject = dynamic_cast<CTerranObject*>(_pSrcRectCmpnt->GetComponentOwner());
	CTerranObject* pDstTerranObject = dynamic_cast<CTerranObject*>(_pDstRectCmpnt->GetComponentOwner());

	if (pSrcTerranObject == nullptr || pDstTerranObject == nullptr) { return; }

	if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::AIR_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::AIR_UNIT)
	{
		CCollisionManager::GetManager()->BlockRect2Rect(_pSrcRectCmpnt, _pDstRectCmpnt, 0.000'1f);
	}
	else if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT)
	{
		CCollisionManager::GetManager()->BlockRect2Rect(_pSrcRectCmpnt, _pDstRectCmpnt, 0.01f);
	}
	else if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::BUILDING)
	{
		CCollisionManager::GetManager()->BlockSrcRectFromDstRect(_pSrcRectCmpnt, _pDstRectCmpnt, 1.0f);
	}
}

void CUnit::OnCollisionStay2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{
	CRectangleColliderComponent* _pSrcRectCmpnt = dynamic_cast<CRectangleColliderComponent*>(_pSrcCollider);
	CRectangleColliderComponent* _pDstRectCmpnt = dynamic_cast<CRectangleColliderComponent*>(_pDstCollider);

	CTerranObject* pSrcTerranObject = dynamic_cast<CTerranObject*>(_pSrcRectCmpnt->GetComponentOwner());
	CTerranObject* pDstTerranObject = dynamic_cast<CTerranObject*>(_pDstRectCmpnt->GetComponentOwner());

	if (pSrcTerranObject == nullptr || pDstTerranObject == nullptr) { return; }

	if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::AIR_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::AIR_UNIT)
	{
		CCollisionManager::GetManager()->BlockRect2Rect(_pSrcRectCmpnt, _pDstRectCmpnt, 0.000'1f);
	}
	else if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT)
	{
		CCollisionManager::GetManager()->BlockRect2Rect(_pSrcRectCmpnt, _pDstRectCmpnt, 0.01f);
	}
	else if (pSrcTerranObject->GetTerranObjectType() == ETerranObjectType::GROUND_UNIT && pDstTerranObject->GetTerranObjectType() == ETerranObjectType::BUILDING)
	{
		CCollisionManager::GetManager()->BlockSrcRectFromDstRect(_pSrcRectCmpnt, _pDstRectCmpnt, 1.0f);
	}
}

void CUnit::OnCollisionExit2D(CColliderComponent* _pSrcCollider, CColliderComponent* _pDstCollider)
{

}

bool CUnit::GetAttacked(int32 _iAttackDamage)
{
	if (m_iCurShield > 0)
	{
		m_iCurShield -= _iAttackDamage;

		if (m_iCurShield <= 0)
		{
			m_iCurShield = 0;
		}
		return false;
	}

	m_iCurHP = m_iCurHP - _iAttackDamage + m_unitProperty.GetDefensePoint();
	return (m_iCurHP <= 0);
}

bool CUnit::GetHealed(int32 _iHeal)
{
	m_iCurHP += _iHeal;
	if (m_iCurHP >= m_unitProperty.GetMaxHP())
	{
		m_iCurHP = m_unitProperty.GetMaxHP();
	}
	return (m_iCurHP >= m_unitProperty.GetMaxHP());
}

void CUnit::IncreaseHP(uint32 _iHP) {
	if (GetCurHP() >= m_unitProperty.GetMaxHP())
	{
		return;
	}

	m_iCurHP += _iHP;
	if (m_iCurHP >= m_unitProperty.GetMaxHP())
	{
		m_iCurHP = m_unitProperty.GetMaxHP();
	}
}

void CUnit::DecreaseHP(uint32 _iHP) {
	if (GetCurHP() <= 0)
	{
		return;
	}

	m_iCurHP -= _iHP;
	if (m_iCurHP <= 0)
	{
		m_iCurHP = 0;
	}
}

void CUnit::IncreaseMP(uint32 _iMP) {
	if (GetCurMP() >= m_unitProperty.GetMaxMP())
	{
		return;
	}

	m_iCurMP += _iMP;
	if (m_iCurMP >= m_unitProperty.GetMaxMP())
	{
		m_iCurMP = m_unitProperty.GetMaxMP();
	}
}

void CUnit::DecreaseMP(uint32 _iMP) {
	if (GetCurMP() <= 0)
	{
		return;
	}

	m_iCurMP -= _iMP;
	if (m_iCurMP <= 0)
	{
		m_iCurMP = 0;
	}
}

void CUnit::IncreaseShield(uint32 _iShield)
{
	m_iCurShield += _iShield;
}

void CUnit::DecreaseShield(uint32 _iShield)
{
	if (GetCurShield() <= 0)
	{
		return;
	}

	m_iCurShield -= _iShield;
	if (m_iCurShield <= 0)
	{
		m_iCurShield = 0;
	}
}

void CUnit::RecoverMP()
{
	float fRecoverMPDS = CTimeManager::GetManager()->GetDeltaSeconds();
	m_fSumRecoverMPDS += fRecoverMPDS;

	if (m_fSumRecoverMPDS >= 3.0f)
	{
		IncreaseMP(2);
		m_fSumRecoverMPDS = 0.0f;
	}
}

void CUnit::UpdateDirection()
{
	Vector2 tDirection = m_tDstPosition - m_tPosition;
	tDirection.Normalize();
	m_fDegree = acosf(tDirection.m_fX) * 180.0f / PI;

	if (0.0f <= m_fDegree && m_fDegree < 22.5f)
	{
		m_eDirectionState = EDirectionState::EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_EAST;
	}
	else if (22.5f <= m_fDegree && m_fDegree < 67.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_EAST;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH;
	}
	else if (67.5f <= m_fDegree && m_fDegree < 112.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH;
	}
	else if (112.5 <= m_fDegree && m_fDegree < 157.5f && tDirection.m_fY < 0.0f)
	{
		m_eDirectionState = EDirectionState::NORTH_WEST;
	}
	else if (112.5 <= m_fDegree && m_fDegree < 157.5f && tDirection.m_fY > 0.0f)
	{
		m_eDirectionState = EDirectionState::SOUTH_WEST;
	}
	else if (157.5f <= m_fDegree && m_fDegree < 181.0f)
	{
		m_eDirectionState = EDirectionState::WEST;
	}
}

void CUnit::UpdateWireframe()
{
	// ü�� ���¿� ���� ���̾��������� ������Ʈ�մϴ�.
	int32 iMaxHP = GetUnitProperty().GetMaxHP();
	int32 iCurHP = GetCurHP();

	int32 i56HP = iMaxHP * 5 / 6;
	int32 i46HP = iMaxHP * 4 / 6;
	int32 i36HP = iMaxHP * 3 / 6;
	int32 i26HP = iMaxHP * 2 / 6;
	int32 i16HP = iMaxHP * 1 / 6;

	if (i56HP < iCurHP && iCurHP <= iMaxHP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[0];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[0];
		m_iCurHPColor = RGB(0, 255, 0);
	}
	else if (i46HP < iCurHP && iCurHP <= i56HP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[1];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[1];
		m_iCurHPColor = RGB(0, 255, 0);
	}
	else if (i36HP < iCurHP && iCurHP <= i46HP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[2];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[2];
		m_iCurHPColor = RGB(255, 255, 0);
	}
	else if (i26HP < iCurHP && iCurHP <= i36HP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[3];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[3];
		m_iCurHPColor = RGB(255, 255, 0);
	}
	else if (i16HP < iCurHP && iCurHP <= i26HP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[4];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[4];
		m_iCurHPColor = RGB(255, 0, 0);
	}
	else if (0 < iCurHP && iCurHP <= i56HP)
	{
		m_pUnitCurBigWireframe = m_pUnitBigWireframes[5];
		m_pUnitCurSmallWireframe = m_pUnitSmallWireframes[5];
		m_iCurHPColor = RGB(255, 0, 0);
	}
}

void CUnit::UpdateDynamicTilemap()
{
	// �� ������Ʈ�� ���� ��ǥ���� �»�� ��ǥ�� ���Ѵ�.
	Vector2 tLeftTopPosition{ m_tPosition.m_fX - m_tSize.m_iX * 0.1f, m_tPosition.m_fY - m_tSize.m_iY * 0.1f };

	// �»�� ��ǥ���� Ÿ�ϸ� ��� ���� ���Ѵ�.
	Vector2Int tTilemapPosition{ (int32)(tLeftTopPosition.m_fX) / ITILECX, (int32)(tLeftTopPosition.m_fY) / ITILECY };

	// ���� Ÿ�ϸ� ��ǥ�� ���� ���, �ǳʶڴ�.
	if ((m_tPrevTilePosition.m_iX == tTilemapPosition.m_iX) && (m_tPrevTilePosition.m_iY == tTilemapPosition.m_iY))
	{
		return;
	}

	Vector2Int tTileSize = m_unitProperty.GetTileSize();

	// ���� Ÿ�ϸ��� �ҷ��ɴϴ�.
	CTilemapObject* pObject = CSceneManager::GetManager()->GetCurScene()->GetDynamicTilemapObject();
	CDynamicTilemapObject* pDynamicTilemapObject = dynamic_cast<CDynamicTilemapObject*>(pObject);

	if (GetOwnerType() == EOwnerType::PLAYER)
	{
		// ���� Ÿ�ϸ� ������ �����մϴ�.
		pDynamicTilemapObject->EraseDynamicTiles(m_tPrevTilePosition, tTileSize, { ETileType::PASSABLE, EOwnerType::PLAYER });
		pDynamicTilemapObject->InsertDynamicTiles(tTilemapPosition, tTileSize, { ETileType::UNIT, EOwnerType::PLAYER });
	}
	else if (GetOwnerType() == EOwnerType::COMPUTER)
	{
		// ���� Ÿ�ϸ� ������ �����մϴ�.
		pDynamicTilemapObject->EraseDynamicTiles(m_tPrevTilePosition, tTileSize, { ETileType::PASSABLE, EOwnerType::COMPUTER });
		pDynamicTilemapObject->InsertDynamicTiles(tTilemapPosition, tTileSize, { ETileType::UNIT, EOwnerType::COMPUTER });
	}

	// ���� Ÿ�ϸ��� �����մϴ�.
	m_tPrevTilePosition = tTilemapPosition;
}

void CUnit::SetCurHitedAnim(CAnimation* _pCurUnitHitedAnim)
{
	if (m_bPlayHitedAnim) { return; }
	if (m_pCurUnitHitedAnim == _pCurUnitHitedAnim) { return; }
	m_pCurUnitHitedAnim = _pCurUnitHitedAnim;

	m_fHitedSumDeltaSeconds = 0.0f;
	m_iHitedOffset = 0;
}

void CUnit::SetCurHitingAnim(CAnimation* _pCurUnitHitingAnim)
{
	if (m_bPlayHitingAnim) { return; }
	if (m_pCurUnitHitingAnim == _pCurUnitHitingAnim) { return; }
	m_pCurUnitHitingAnim = _pCurUnitHitingAnim;

	m_fHitingSumDeltaSeconds = 0.0f;
	m_iHitingOffset = 0;
}

void CUnit::UpdateHitedSprite()
{
	// �ִϸ��̼��� ������Ʈ�մϴ�.
	VERIFY_NULLPTR(m_pCurUnitHitedAnim);
	m_bPlayHitedAnim = true;

	tagAnimationInfo tAnimationInfo = m_pCurUnitHitedAnim->GetAnimationInfo();

	pair<int32, int32> tXIndex{ 0, 0 };
	pair<int32, int32> tYIndex{ 0, 0 };
	int32 iNumSprite = 0;
	float fDeltaDuration = 0.0f;

	// �ִϸ��̼��� �ε����� �����մϴ�.
	if (tAnimationInfo.m_bVertical == true)
	{
		// �ִϸ��̼��� ��� �� ������ �����Ǿ� �ִٰ� �����մϴ�.
		tYIndex = tAnimationInfo.m_tYIndex;
		iNumSprite = tYIndex.second - tYIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}
	else
	{
		// �ִϸ��̼��� ��� �� �࿡�� �����Ǿ� �ִٰ� �����մϴ�.
		tXIndex = tAnimationInfo.m_tXIndex;
		iNumSprite = tXIndex.second - tXIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}


	m_fHitedSumDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

	// �� ���� �ִϸ��̼��� �����մϴ�.
	if (tAnimationInfo.m_bPlayOnce == true)
	{
		if (m_fHitedSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHitedSumDeltaSeconds = 0.0f;
			m_iHitedOffset = (m_iHitedOffset + 1) % iNumSprite;

			if (m_iHitedOffset == 0)
			{
				m_iHitedOffset = iNumSprite - 1;
				m_bPlayHitedAnim = false;
			}
		}
	}
	// �ݺ��ؼ� �ִϸ��̼��� �����մϴ�.
	else if (tAnimationInfo.m_bRepeat == true)
	{
		// ���� ��������Ʈ�� �����ϵ��� �������� ������ŵ�ϴ�.
		if (m_fHitedSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHitedSumDeltaSeconds = 0.0f;
			m_iHitedOffset = (m_iHitedOffset + 1) % iNumSprite;
		}

		if (m_iHitedOffset == 0)
		{
			m_bPlayHitedAnim = false;
		}
	}
}

void CUnit::UpdateHitingSprite()
{
	// �ִϸ��̼��� ������Ʈ�մϴ�.
	VERIFY_NULLPTR(m_pCurUnitHitingAnim);
	m_bPlayHitingAnim = true;

	tagAnimationInfo tAnimationInfo = m_pCurUnitHitingAnim->GetAnimationInfo();

	pair<int32, int32> tXIndex{ 0, 0 };
	pair<int32, int32> tYIndex{ 0, 0 };
	int32 iNumSprite = 0;
	float fDeltaDuration = 0.0f;

	// �ִϸ��̼��� �ε����� �����մϴ�.
	if (tAnimationInfo.m_bVertical == true)
	{
		// �ִϸ��̼��� ��� �� ������ �����Ǿ� �ִٰ� �����մϴ�.
		tYIndex = tAnimationInfo.m_tYIndex;
		iNumSprite = tYIndex.second - tYIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}
	else
	{
		// �ִϸ��̼��� ��� �� �࿡�� �����Ǿ� �ִٰ� �����մϴ�.
		tXIndex = tAnimationInfo.m_tXIndex;
		iNumSprite = tXIndex.second - tXIndex.first + 1;
		fDeltaDuration = tAnimationInfo.m_fDuration / (float)iNumSprite;
	}

	m_fHitingSumDeltaSeconds += CTimeManager::GetManager()->GetDeltaSeconds();

	// �� ���� �ִϸ��̼��� �����մϴ�.
	if (tAnimationInfo.m_bPlayOnce == true)
	{
		if (m_fHitingSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHitingSumDeltaSeconds = 0.0f;
			m_iHitingOffset = (m_iHitingOffset + 1) % iNumSprite;

			if (m_iHitingOffset == 0)
			{
				m_iHitingOffset = iNumSprite - 1;
				m_bPlayHitingAnim = false;
			}
		}
	}
	// �ݺ��ؼ� �ִϸ��̼��� �����մϴ�.
	else if (tAnimationInfo.m_bRepeat == true)
	{
		// ���� ��������Ʈ�� �����ϵ��� �������� ������ŵ�ϴ�.
		if (m_fHitingSumDeltaSeconds >= fDeltaDuration)
		{
			m_fHitingSumDeltaSeconds = 0.0f;
			m_iHitingOffset = (m_iHitingOffset + 1) % iNumSprite;

			if (m_iHitingOffset == 0)
			{
				m_bPlayHitingAnim = false;
			}
		}
	}
}

void CUnit::RenderHitedSprite(HDC _hDC)
{
	VERIFY_NULLPTR(m_pCurUnitHitedAnim);
	tagAnimationInfo tAnimationInfo = m_pCurUnitHitedAnim->GetAnimationInfo();

	bool bVertical = tAnimationInfo.m_bVertical;
	Vector2Int tSize = tAnimationInfo.m_tSize;
	pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
	pair<int32, int32> tYIndex = tAnimationInfo.m_tYIndex;
	uint32 uiAlpha = m_pCurUnitHitedAnim->GetTextureAlpha();

	// ī�޶� ��ġ�� ���մϴ�.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tHitedPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitedPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitedAnim->GetTextureDC(),
				(tXIndex.first + m_iHitedOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				SRCCOPY);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			::BitBlt(_hDC,
				(int32)(m_tHitedPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitedPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitedAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHitedOffset) * tSize.m_iHeight,
				SRCCOPY);
		}
	}
	else
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHitedPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitedPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitedAnim->GetTextureDC(),
				(tXIndex.first + m_iHitedOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHitedPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitedPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitedAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHitedOffset) * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
}

void CUnit::RenderHitingSprite(HDC _hDC)
{
	VERIFY_NULLPTR(m_pCurUnitHitingAnim);
	tagAnimationInfo tAnimationInfo = m_pCurUnitHitingAnim->GetAnimationInfo();

	bool bVertical = tAnimationInfo.m_bVertical;
	Vector2Int tSize = tAnimationInfo.m_tSize;
	pair<int32, int32> tXIndex = tAnimationInfo.m_tXIndex;
	pair<int32, int32> tYIndex = tAnimationInfo.m_tYIndex;
	uint32 uiAlpha = m_pCurUnitHitingAnim->GetTextureAlpha();

	// ī�޶� ��ġ�� ���մϴ�.
	CScene* pCurScene = CSceneManager::GetManager()->GetCurScene();
	Vector2 tCameraPosition = pCurScene->GetCameraPosition();

	if (m_bGdiRender == false)
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			::BitBlt(_hDC,
				(int32)(m_tHitingPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitingPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitingAnim->GetTextureDC(),
				(tXIndex.first + m_iHitingOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				SRCCOPY);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			::BitBlt(_hDC,
				(int32)(m_tHitingPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitingPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitingAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHitingOffset) * tSize.m_iHeight,
				SRCCOPY);
		}
	}
	else
	{
		// ������ ������ �ִϸ��̼�
		if (bVertical == false)
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHitingPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitingPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitingAnim->GetTextureDC(),
				(tXIndex.first + m_iHitingOffset) * tSize.m_iWidth,
				tYIndex.first * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
		// ���� ������ �ִϸ��̼�
		else
		{
			GdiTransparentBlt(_hDC,
				(int32)(m_tHitingPosition.m_fX - tSize.m_iX * 0.5f - (tCameraPosition.m_fX - FWINCX * 0.5f)),
				(int32)(m_tHitingPosition.m_fY - tSize.m_iY * 0.5f - (tCameraPosition.m_fY - FWINCY * 0.5f)),
				tSize.m_iWidth,
				tSize.m_iHeight,
				m_pCurUnitHitingAnim->GetTextureDC(),
				tXIndex.first * tSize.m_iWidth,
				(tYIndex.first + m_iHitingOffset) * tSize.m_iHeight,
				tSize.m_iWidth,
				tSize.m_iHeight,
				uiAlpha);
		}
	}
}

