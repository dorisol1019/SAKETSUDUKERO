#pragma once

#include "stdafx.h"

//�R�C�Q�C�P�CGo�̉摜���������邽�߂̃N���X
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