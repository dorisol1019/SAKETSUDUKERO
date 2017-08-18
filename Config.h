#pragma once

#include"stdafx.h"

class Config:public BaseScene{
public:
	Config(ISceneChanger* changer);
	void Init() override;
	void Update() override;
	void Draw() override;

	//void End() override;
};