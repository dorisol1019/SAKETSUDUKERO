#pragma once

#include "stdafx.h"
#include "Difficulty.h"
//�ǐՎҁB���Ȃ킿�G�l�~�[
//�ǐՂł͂Ȃ���щ���Ă邾������ƌ����Ă͂����Ȃ�
class Opponent:public BaseCharacter{
private:
	float x,y,dx,dy;
	int speed;
	double angle;
public:
	Opponent();

	void Init(Difficulty difficulty);
	void End();
	void Update();
	void Draw();


	float GetX();
	float GetY();

	double GetAngle();

private :
	void SetXY();

	//��Փx�œG�̃X�s�[�h�����肵�����I�ȃA��
	int DecideSpeed(Difficulty difficulty);
};