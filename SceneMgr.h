#pragma once
#include"stdafx.h"

#include<memory>

//メニュー画面、ゲーム画面の相互の行き来を管理するクラス
//参考資料
//新ゲームプログラミングの館
//http://dixq.net/g/sp_06.html
class SceneMgr :public ISceneChanger {
private:
	std::unique_ptr<IScene> currentScene;
	std::unique_ptr<IScene> nextScene = nullptr;
public:
	SceneMgr();
	void Init();
	void End();
	void Update();
	void Draw();

	void ChangeScene(std::unique_ptr<IScene> nextScene);
};