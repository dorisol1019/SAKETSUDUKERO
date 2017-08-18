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
		//move���ė������ʓ|�������񂾂���
		//�Ƃ肠����std::unique_ptr���w���|�C���^���E�ӂ��獶�ӂɈړ������Ă�
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