#include"stdafx.h"
#include"Color.h"
#include<cmath>
#include<filesystem>
#include<fstream>

Game::Game(ISceneChanger* changer, Difficulty difficulty) :BaseScene(changer) {

	this->difficulty = difficulty;

	for (int i = 0; i < 4; i++) {
		countdowns.push(CountDown{});
		countdowns.back().Init(i, -120, 180);
	}

	gameScene = eCountdown;
	frameCount = 0;

	lastCount = 0;

	opponents.emplace_back();

	scoreTime = 0;

	countdownSoundHandle[0] = LoadSoundMem("Music/SE/Countdown01-5.mp3");
	countdownSoundHandle[1] = LoadSoundMem("Music/SE/Countdown01-6.mp3");
	explosionSoundHandle = LoadSoundMem("Music/SE/explosion.mp3");
}
void Game::Init() {
	opponents[0].Init(difficulty);


	StopMusic();
}
void Game::Update() {
	if (GetKey(KEY_INPUT_F12) == 1 || GetKey(KEY_INPUT_ESCAPE) == 1) {
		sceneChanger->ChangeScene(std::make_unique<Menu>(sceneChanger));
	}
	else if (GetKey(KEY_INPUT_F11)) {
		sceneChanger->ChangeScene(std::make_unique<Game>(sceneChanger, difficulty));
	}
	Music();
	//経過時間を出すためにフレーム数をカウントする
	//本当ならTimerクラスでも定義してやった方がいい
	frameCount++;
	switch (gameScene) {
	//カウントダウン
	case eCountdown:
		if (!countdowns.empty()) {
			countdowns.front().Update();
		}
		if (frameCount >= 60) {
			frameCount = 0;
			countdowns.pop();
			if (!countdowns.empty())
			{
				PlaySoundMem(countdownSoundHandle[0], DX_PLAYTYPE_BACK);
			}
			else
			{
				PlaySoundMem(countdownSoundHandle[1], DX_PLAYTYPE_BACK);
				gameScene = eMainGame;
				escapee.Init(difficulty);
				bgmFileName = DecideBgmFileName(difficulty);
				StopMusic();
			}
		}
		break;
	//ゲーム本体
	case eMainGame:

		escapee.Update();

		{
			//何秒感覚で敵を生み出すか
			float opponentPopInterval_s = 10;
			if (difficulty == Difficulty::god) {
				opponentPopInterval_s = 5;
			}

			if (frameCount % (int)(60 * opponentPopInterval_s) == 0) {
				opponents.emplace_back();
				opponents.back().Init(difficulty);
			}
		}

		for (auto& opponent : opponents)
		{
			opponent.Update();
		}

		//自機が壊れていれば
		if (escapee.IsBreak()) {
			lastCount++;
		}
		//自機が壊れてなければ
		else {
			if (CheckHitMeAndBall())
			{
				escapee.SetBreak(true);
				//フレーム数を秒に直しているはず
				scoreTime = frameCount / 60 + frameCount % 60 / 60.0;
				PlaySoundMem(explosionSoundHandle, DX_PLAYTYPE_BACK);
			}
		}

		//自機が破壊されて1秒経ったら
		if (lastCount >= 60) {
			//ランキング画面に飛ぶよ
			sceneChanger->ChangeScene(std::make_unique<Ranking>(sceneChanger,difficulty,scoreTime));
		}
		break;
	}

}
void Game::Draw() {

	switch (gameScene) {
	case eCountdown:
		if (!countdowns.empty())
		{
			countdowns.front().Draw();
		}
		break;
	case eMainGame:
		escapee.Draw();
		for (auto& opponent : opponents)
		{
			opponent.Draw();
		}
		break;
	}
}

//自機とボール(敵)の当たり判定
bool Game::CheckHitMeAndBall() {
	using std::pow;
	int meX = escapee.GetX();
	int meY = escapee.GetY();
	int meWidth = escapee.GetWidth();
	for (int i = 0; i < opponents.size(); i++) {
		float ballX = opponents[i].GetX();
		float ballY = opponents[i].GetY();
		float ballWidth = opponents[i].GetWidth();
		//円と円の当たり判定
		if (pow(ballX - meX, 2) + pow(ballY - meY, 2) <= pow(meWidth / 2 + ballWidth / 2, 2)) {
			return true;
		}
	}
	return false;
}

std::string Game::DecideBgmFileName(Difficulty difficulty)
{
	switch (difficulty)
	{
	case Difficulty::easy:
		return "Music/BGM/017_AKATUKI.mp3";
	case Difficulty::normal:
		return "Music/BGM/008_simoguri.mp3";
	case Difficulty::hard:
		return "Music/BGM/009_Instant_divine.mp3";
	case Difficulty::god:
		return "Music/BGM/001_hitonowa.mp3";
	}
	return std::string{};
}


void Game::End() {
	escapee.End();
	for (auto& opponent : opponents)
	{
		opponent.End();
	}
}

void Game::Music() {
	if (CheckMusic() != 1) {
		PlayMusic(bgmFileName.c_str(), DX_PLAYTYPE_LOOP);
		SetVolumeMusic(155);
	}
}
