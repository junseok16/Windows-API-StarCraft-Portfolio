#pragma once

class CUI
{
public:
	CUI() = default;
	virtual ~CUI() = default;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void SetUIActive(bool _bUIActive) { m_bUIActive = _bUIActive; }
	bool GetUIActive() const { return m_bUIActive; }

	EUIType GetUIType() const { return m_eUIType; }
	void SetUIType(EUIType _eUIType) { m_eUIType = _eUIType; }

	Vector2 GetPosition() const { return m_tPosition; }
	void SetPosition(Vector2 _tPosition) { m_tPosition = _tPosition; }

	Vector2Int GetSize() const { return m_tSize; }
	void SetSize(Vector2Int _tSize) { m_tSize = _tSize; }

	void SetGdiRender(bool _bGdiRender) { m_bGdiRender = _bGdiRender; }
	bool GetGdiRender() const { return m_bGdiRender; }

public:
	bool IsCursorInRect();

protected:	
	// BitBlt / GdiTransparentBlt 렌더 여부
	bool m_bGdiRender = true;

	// UI 활성화 여부
	bool m_bUIActive = true;

	EUIType m_eUIType = EUIType::ENUM_END;

	// UI의 중앙 위치
	Vector2 m_tPosition{ 0.0f, 0.0f };

	// UI의 가로, 세로 길이
	Vector2Int m_tSize{ 0, 0 };
};

