#pragma once

#include"IScene.h"
#include<memory>

//シーン変更のためのインターフェース
//どうやって使うかはSceneMgr辺り見て
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(std::unique_ptr<IScene> NextScene) = 0;
};