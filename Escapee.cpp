#include "stdafx.h"
#include"MyWindow.h"
Escapee::Escapee() {}

void Escapee::Init(Difficulty difficulty) {

	Graph = LoadGraph("Picture/Me.png");

	GetGraphSize(Graph, &width, &height);

	//座標を中央に配置
	x = MyWindow::Width / 2 - width / 2;
	y = MyWindow::Height / 2 - height / 2;

	speed = DecideSpeed(difficulty);

	isBreak = false;
}

void Escapee::Update() {
	if (!isBreak) {
		KeyUpdate();
	}
}

void Escapee::Draw() {
	if (!isBreak) {
		DrawGraph(x - width / 2, y - height / 2, Graph, TRUE);
	}
}

void Escapee::KeyUpdate() {
	//↓座標に直接距離を足すのは斜め入力のときに√2倍進むのでダメ（三平方の定理）
	//どうすればいいかはOpponentの方参照
	if (GetKey(KEY_INPUT_RIGHT) != 0 || GetKey(KEY_INPUT_D) != 0) {
			x += speed;
	}
	if (GetKey(KEY_INPUT_LEFT) != 0 || GetKey(KEY_INPUT_A) != 0) {
			x -= speed;
	}

	if (GetKey(KEY_INPUT_UP) != 0 || GetKey(KEY_INPUT_W) != 0) {
			y -= speed;
	}
	if (GetKey(KEY_INPUT_DOWN) != 0 || GetKey(KEY_INPUT_S) != 0) {
			y += speed;
	}

	if (x < width / 2) {
		x = width / 2;
	}
	else if (x > MyWindow::Width - width / 2) {
		x = MyWindow::Width - width / 2;
	}

	if (y < height / 2) {
		y = height / 2;
	}
	else if (y > MyWindow::Height - height / 2) {
		y = MyWindow::Height - height / 2;
	}
}

int Escapee::DecideSpeed(Difficulty difficulty)
{
	switch (difficulty)
	{
	case Difficulty::easy:
		break;
	case Difficulty::normal:
		break;
	case Difficulty::hard:
		break;
	case Difficulty::god:
		return 8;
	default:
		break;
	}
	return 5;
}

void Escapee::SetBreak(bool flag) {
	isBreak = flag;
}
bool Escapee::IsBreak() {
	return isBreak;
}