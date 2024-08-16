#pragma once
#include "Scene.h"

class CTestScene : public CScene
{
public:
	CTestScene() = default;
	virtual ~CTestScene() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

private:
	void LoadTileTexture();
	void LoadEffectTexture();
	void LoadUITexture();
	void LoadUnitTexture();
	void LoadBuildingTexture();
	void LoadResourceTexture();
};

