#include"stdafx.h"

SceneMgr::SceneMgr() {
	currentScene = std::make_unique<Menu>(this);
}

void SceneMgr::Init() {
	currentScene->Init();
}

void SceneMgr::End() {
	currentScene->End();
}

void SceneMgr::Update() {
	if (nextScene != nullptr) {
		currentScene->End();
		//moveって理解が面倒くさいんだけど
		//とりあえずstd::unique_ptrが指すポインタを右辺から左辺に移動させてる
		currentScene = std::move(nextScene);
		currentScene->Init();
	}
	currentScene->Update();
}

void SceneMgr::Draw() {
	currentScene->Draw();
}


void SceneMgr::ChangeScene(std::unique_ptr<IScene> nextScene) {
	this->nextScene = std::move(nextScene);
}