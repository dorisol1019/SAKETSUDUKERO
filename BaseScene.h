#pragma once
#include"stdafx.h"
#include"IScene.h"

class BaseScene :public IScene {
protected:
	int backgroundImage;
	ISceneChanger* sceneChanger;
public:
	BaseScene(ISceneChanger* changer);
	~BaseScene() {}
	virtual void Init()override {}
	virtual void End()override;
	virtual void Update()override {};
	virtual void Draw()override;
};