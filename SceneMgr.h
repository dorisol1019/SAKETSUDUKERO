#pragma once
#include"stdafx.h"

#include<memory>

//���j���[��ʁA�Q�[����ʂ̑��݂̍s�������Ǘ�����N���X
//�Q�l����
//�V�Q�[���v���O���~���O�̊�
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