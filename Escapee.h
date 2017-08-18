#pragma once

#include "stdafx.h"
#include"Difficulty.h"
//逃走者。すなわちプレーヤー
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

	//難易度で自機のスピードを決定したい的なアレ
	int DecideSpeed(Difficulty difficulty);
};