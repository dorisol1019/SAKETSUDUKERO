#include "stdafx.h"
#include"MyWindow.h"
#include"MyMath.h"

Opponent::Opponent() {}

void Opponent::Init(Difficulty difficulty) {

	Graph = LoadGraph("picture/Ball.png");

	GetGraphSize(Graph, &width, &height);

	SetXY();

	speed = DecideSpeed(difficulty);

	//この乱数の使い方はダメ
	angle = rand() % 360;
	const float radian = MyMath::Pi / 360 * (angle);

	//座標更新のための差分を計算
	//参考資料
	//新ゲームプログラミングの館
	//http://dixq.net/g/03_07.html
	dx = cos(radian)*speed;
	dy = sin(radian)*speed;
}

void Opponent::Update() {
	x += dx;
	y += dy;

	if (x < width / 2) {
		x = width / 2;
		dx *= -1;
	}
	else if (x > MyWindow::Width - width / 2) {
		x = MyWindow::Width - width / 2;
		dx *= -1;
	}

	if (y < height / 2) {
		y = height / 2;
		dy *= -1;
	}
	else if (y > MyWindow::Height - height / 2) {
		y = MyWindow::Height - height / 2;
		dy *= -1;
	}
}

void Opponent::Draw() {
	//非公開関数
	DrawGraphF(x - width / 2, y - width / 2, Graph, TRUE);
}

// 画面を縦に四等分、横に三等分し、その交点12個のうちからランダムに座標を決定する
// あとから思えば絶対もっとスマートな方法ある
void Opponent::SetXY() {
	int tmpx[12], tmpy[12], index = rand() % 12;
	for (int i = 0, k = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			tmpx[k] = 192 * (i + 1);
			tmpy[k] = 135 * (j + 1);
			k++;
		}
	}
	x = tmpx[index];
	y = tmpy[index];
}

int Opponent::DecideSpeed(Difficulty difficulty)
{
	switch (difficulty)
	{
	case Difficulty::easy:
		return 3;
	case Difficulty::normal:
		return 5;
	case Difficulty::hard:
		return 7;
	case Difficulty::god:
		return 10;
	}
	return 5;
}

void Opponent::End() {

}

float Opponent::GetX() {
	return this->x;
}

float Opponent::GetY() {
	return this->y;
}

double Opponent::GetAngle() {
	return angle;
}
