#pragma once

#include"IScene.h"
#include<memory>

//�V�[���ύX�̂��߂̃C���^�[�t�F�[�X
//�ǂ�����Ďg������SceneMgr�ӂ茩��
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(std::unique_ptr<IScene> NextScene) = 0;
};