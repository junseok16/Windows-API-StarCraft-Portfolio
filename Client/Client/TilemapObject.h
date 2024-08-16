#pragma once
#include "Object.h"

class CTilemap;

class CTilemapObject : public CObject
{
public:
	CTilemapObject() = default;
	virtual ~CTilemapObject() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void PickTile();

public:
	CTilemap* GetTilemap() const { return m_pTilemap; }
	void SetTilemap(CTilemap* _pTilemap) { m_pTilemap = _pTilemap; }
	
	bool GetDebug() const { return m_bDebug; }
	void SetDebug(bool _bDebug) { m_bDebug = _bDebug; }
	
private:
	CTilemap* m_pTilemap = nullptr;
	bool m_bDebug = true;
};

