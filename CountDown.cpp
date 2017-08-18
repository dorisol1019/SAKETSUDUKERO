#include "stdafx.h"

CountDown::CountDown() {
	x = 0;
	y = 0;
}

void CountDown::Init(int index, int x, int y) {
	this->x = x;
	this->y = y;

	SetGraph(index);
}

void CountDown::Update() {
	x += 10;
}

void CountDown::Draw() {
	DrawGraph(x, y, Graph, TRUE);
}

void CountDown::End() {

}

void CountDown::SetGraph(int graphNum) {
	string path = "Picture/";

	//“V×‹S‚È‚Ì‚Å”’l‚Æ‰æ‘œ‚ÌŠÖŒW‚ğ‚â‚â‚±‚µ‚­‚µ‚Ä‚µ‚Ü‚Á‚Ä‚¢‚é
	switch (graphNum) {
	case 0:
		path += "Count3";
		break;
	case 1:
		path += "Count2";
		break;
	case 2:
		path += "Count1";
		break;
	case 3:
		path += "CountGo";
		break;
	default:
		MessageBox(GetMainWindowHandle(), _T("Error"), _T("in SetGraph"), MB_OK);
		exit(-1);
		break;
	}

	path += ".png";

	Graph = LoadGraph(path.c_str());


}

CountDown::~CountDown() {

}