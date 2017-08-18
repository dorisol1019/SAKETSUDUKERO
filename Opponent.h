#pragma once

#include "stdafx.h"
#include "Difficulty.h"
//追跡者。すなわちエネミー
//追跡ではなく飛び回ってるだけだろと言ってはいけない
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

	//難易度で敵のスピードを決定したい的なアレ
	int DecideSpeed(Difficulty difficulty);
};