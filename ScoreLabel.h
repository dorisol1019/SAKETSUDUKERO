#pragma once
#include "stdafx.h"

class ScoreLabel{
private:
	int fonthandle;
	int rank;
	double time;
	int x,y;
public:
	void Init(int rank,double time,int x,int y);
	void End();
	void Update();
	void Draw();
};