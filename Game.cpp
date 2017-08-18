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
	//�o�ߎ��Ԃ��o�����߂Ƀt���[�������J�E���g����
	//�{���Ȃ�Timer�N���X�ł���`���Ă������������
	frameCount++;
	switch (gameScene) {
	//�J�E���g�_�E��
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
	//�Q�[���{��
	case eMainGame:

		escapee.Update();

		{
			//���b���o�œG�𐶂ݏo����
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

		//���@�����Ă����
		if (escapee.IsBreak()) {
			lastCount++;
		}
		//���@�����ĂȂ����
		else {
			if (CheckHitMeAndBall())
			{
				escapee.SetBreak(true);
				//�t���[������b�ɒ����Ă���͂�
				scoreTime = frameCount / 60 + frameCount % 60 / 60.0;
				PlaySoundMem(explosionSoundHandle, DX_PLAYTYPE_BACK);
			}
		}

		//���@���j�󂳂��1�b�o������
		if (lastCount >= 60) {
			//�����L���O��ʂɔ�Ԃ�
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

//���@�ƃ{�[��(�G)�̓����蔻��
bool Game::CheckHitMeAndBall() {
	using std::pow;
	int meX = escapee.GetX();
	int meY = escapee.GetY();
	int meWidth = escapee.GetWidth();
	for (int i = 0; i < opponents.size(); i++) {
		float ballX = opponents[i].GetX();
		float ballY = opponents[i].GetY();
		float ballWidth = opponents[i].GetWidth();
		//�~�Ɖ~�̓����蔻��
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
