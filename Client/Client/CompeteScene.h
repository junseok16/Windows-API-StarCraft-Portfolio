#pragma once
#include "Scene.h"

class CCompeteScene : public CScene
{
public:
	CCompeteScene() = default;
	virtual ~CCompeteScene() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

