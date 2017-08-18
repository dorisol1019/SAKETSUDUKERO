#include "stdafx.h"
#include"Color.h"
void ScoreLabel::Init(int rank,double time, int x, int y) {
	fonthandle = CreateFontToHandle("���C���I", 120, 5, DX_FONTTYPE_ANTIALIASING);
	this->rank = rank;
	this->time = time;
	this->x = x;
	this->y = y;
}
void ScoreLabel::Update() {
	x -= 5;
}
void ScoreLabel::Draw() {
	DrawFormatStringToHandle(x - 240, y, GetColor(0, 255, 255), fonthandle, "%d��", rank);
	DrawFormatStringToHandle(x, y, Color::Green(), fonthandle, "%.2f�b", time);
}
void ScoreLabel::End() {
	DeleteFontToHandle(fonthandle);
}