#pragma once
#include<Windows.h>
#include<DxLib.h>

/*
処理速度がディスプレイの更新速度より早く、60fpsを保てないとき、処理を待機して60fpsに保つクラス
しかし今見たらちゃんと動いているか不安なためこのクラスは参考にしないこと
	2017/8/18 @dorisol1019
*/
class WaitTimer {
private:
	int startTime;
	int frameCount;
	float WaitTimes;
	static constexpr int fps = 60;
	static constexpr int WT = 60;
public:
	WaitTimer() {
		startTime = 0;
		frameCount = 0;
		WaitTimes = 0;
	}
	bool Update() {
		if (frameCount == 0) {
			startTime = GetNowCount();
		}
		if (frameCount == fps) {
			int t = GetNowCount();
			WaitTimes = 1000.f / ((t - startTime) / (float)fps);
			frameCount = 0;
			startTime = t;
		}
		frameCount++;
		return true;
	}
	void Wait() {
		int waitTime = frameCount * 1000 / WT - (GetNowCount() - startTime);
		if (waitTime > 0) {
			Sleep(waitTime);
		}
	}

};