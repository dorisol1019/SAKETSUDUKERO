#pragma once

#include "stdafx.h"
#include"Difficulty.h"
//�����ҁB���Ȃ킿�v���[���[
class Escapee :public BaseCharacter {
private:
	bool isBreak;
	int speed;
public:
	Escapee();

	void Init(Difficulty difficulty);
	void Update();
	void Draw();

	void SetBreak(bool flag);
	bool IsBreak();
private:
	void KeyUpdate();

	//��Փx�Ŏ��@�̃X�s�[�h�����肵�����I�ȃA��
	int DecideSpeed(Difficulty difficulty);
};