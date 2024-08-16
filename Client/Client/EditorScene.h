#pragma once
#include "Scene.h"

class CEditorScene : public CScene
{
public:
	CEditorScene() = default;
	virtual ~CEditorScene() = default;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

