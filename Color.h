#pragma once
#include<DxLib.h>
using uint = unsigned int;

class Color{
public:
	static uint GetColor(int red,int green,int blue)
	{
		return DxLib::GetColor(red, green, blue);
	}

	static const uint Red(){
		return GetColor(255, 0, 0);
	}

	static const uint White() {
		return GetColor(255, 255, 255);
	}

	static const uint Green() {
		return GetColor(0, 255, 0);
	}

	static const uint Black() {
		return GetColor(0, 0, 0);
	}
};