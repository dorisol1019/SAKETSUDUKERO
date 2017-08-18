#pragma once
#include"stdafx.h"
#include<vector>
#include<queue>
#include<string>
#include"Difficulty.h"

enum eGameScene{
	eCountdown,eMainGame
};

//ÉNÉâÉXêÈåæ
class Game:public BaseScene{
private:
	Difficulty difficulty;

	std::queue<CountDown>countdowns{};
	Escapee escapee;
	std::vector<Opponent>opponents{};

	eGameScene gameScene;

	int frameCount;

	double scoreTime;

	int lastCount;

	int countdownSoundHandle[2];

	std::string bgmFileName;

	int explosionSoundHandle;


public:
	Game(ISceneChanger* changer, Difficulty difficulty);
	void Init() override;
	void Update() override;
	void Draw() override;
	void End() override;
	void Music();

	bool CheckHitMeAndBall();

private:
	std::string DecideBgmFileName(Difficulty difficulty);
};