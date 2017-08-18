#pragma once
#include<Windows.h>
#include<DxLib.h>

/*
�������x���f�B�X�v���C�̍X�V���x��葁���A60fps��ۂĂȂ��Ƃ��A������ҋ@����60fps�ɕۂN���X
�������������炿���Ɠ����Ă��邩�s���Ȃ��߂��̃N���X�͎Q�l�ɂ��Ȃ�����
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