#pragma once

#include "stdafx.h"

//３，２，１，Goの画像を持たせるためのクラス
class CountDown{
private:
	int x,y;
	int Graph;
public:
	CountDown();
	~CountDown();

	void Init(int index,int x,int y);
	void End();
	void Draw();
	void Update();

	void SetGraph(int graphNum);
};