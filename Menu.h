#pragma once

#include"stdafx.h"

//�s���ɂ��int�^�ɃL���X�g����������enum���g���Ă��邪
//���ʂ�enum class(C++11���)���g������
enum MenuItem{
	eazy,
	normal,
	hard,
	god,
	gameEnd,

	allNum //����
};

//���j���[��ʂ̃V�[���N���X
//������Ƃ����Ă���悤�Ɍ����邪�A�v�͎Q�l�����̂قڃR�s�y�ł���
//�Q�l����
//�V�Q�[���v���O���~���O�̊�
//http://dixq.net/g/sp_07.html
class Menu :public BaseScene {
private:
	string bgmFileName;
public:
	Menu(ISceneChanger* changer);
	void Init() override;
	void Update() override;
	void Draw() override;
	void Music();
};