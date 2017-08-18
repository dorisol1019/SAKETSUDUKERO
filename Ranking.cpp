#include "Ranking.h"
#include<DxLib.h>
#include<fstream>
#include<algorithm>
#include<filesystem>
#include<array>
#include"Color.h"

Ranking::Ranking(ISceneChanger*sceneChanger, Difficulty difficulty, double currentScore) :BaseScene(sceneChanger)
{
	this->currentScore = currentScore;
	namespace fs = std::experimental::filesystem;

	auto oldRankingScores = LoadRankedScores(difficulty);

	auto newRankingScores = MakeNewRankingScores(oldRankingScores, currentScore);

	if (newRankingScores[3] < currentScore) {
		isRanked = true;
	}

	if (isRanked) {
		WriteRankedScores(difficulty, newRankingScores);
	}

	for (int i = 0; i < 3; i++) {
		scoreLabels[i].Init(i + 1, newRankingScores[i], 960 + 240, 120 + i * 120);
	}

	frameCount = 0;
	StopMusic();
	bgmFileName = "Music/BGM/sousou1.mp3";
}


Ranking::~Ranking()
{
}


void Ranking::Init()
{
	currentScoreTimeFontHandle = CreateFontToHandle("MS����", 80, 3, DX_FONTTYPE_ANTIALIASING);
	messageFontHandle = CreateFontToHandle("���C���I", 55, 2, DX_FONTTYPE_ANTIALIASING);
}

void Ranking::Update()
{
	Music();
	frameCount++;
	for (int i = 0; i < 3; i++) {
		scoreLabels[i].Update();
	}
	//�T�b�o������V�[���J��
	if (frameCount / 60 > 5) {
		sceneChanger->ChangeScene(std::make_unique<Menu>(sceneChanger));
	}
}

void Ranking::Draw()
{
	if (isRanked) {
		DrawStringToHandle(300, 480, "�����N�C�����߂łƂ��I", Color::White(), messageFontHandle);
	}
	else {
		DrawStringToHandle(300, 480, "�����N�C���Ȃ炸���", Color::White(), messageFontHandle);
	}


	DrawFormatStringToHandle(10, 30, Color::White(), currentScoreTimeFontHandle, "���Ȃ��̃^�C�� %.2f�b", currentScore);

	for (int i = 0; i < 3; i++) {
		scoreLabels[i].Draw();
	}
}

void Ranking::End()
{
	for (int i = 0; i < 3; i++) {
		scoreLabels[i].End();
	}
	DeleteFontToHandle(currentScoreTimeFontHandle);
	DeleteFontToHandle(messageFontHandle);
}

void Ranking::Music()
{
	if (CheckMusic() != 1) {
		PlayMusic(bgmFileName.c_str(), DX_PLAYTYPE_LOOP);
		SetVolumeMusic(155);
	}
}




std::array<double, 3> Ranking::LoadRankedScores(const Difficulty difficulty)
{
	namespace fs = std::experimental::filesystem;
	std::array<double, 3> rankedScores{};
	std::string rankingFileName = DecideRankingFileName(difficulty);
	fs::path rankingFilePath = rankingFileName;

	//�����L���O�t�@�C��������ꍇ�A�����L���O��ǂݍ���Ŕz��(rankedScores)�Ɋi�[
	if (fs::exists(rankingFilePath)) {
		std::ifstream scoreFileReader{ rankingFileName };
		for (int i = 0; i < 3; i++) {
			scoreFileReader >> rankedScores[i];
		}
	}
	//�Ȃ��ꍇ�A�z���0���߂��� �͂�
	else {
		std::fill(std::begin(rankedScores), std::end(rankedScores), 0.0);
	}
	return rankedScores;
}

std::array<double, 4> Ranking::MakeNewRankingScores(const std::array<double, 3>& oldRankedScore, const double& currentScore)
{
	std::array<double, 4>rankedScores{ 4 };

	std::copy(oldRankedScore.begin(), oldRankedScore.end(), rankedScores.begin());

	rankedScores[3] = (currentScore);

	//�v�f��4�̔z��ɁA3�̃����N���肵�Ă���X�R�A�ƁA���݂̃X�R�A���i�[����
	//�~���\�[�g���邱�ƂŃ����L���O���������ɕ��בւ���͋Z
	std::stable_sort(std::begin(rankedScores), std::end(rankedScores), greater<double>());

	return rankedScores;
}

void Ranking::WriteRankedScores(const Difficulty difficulty, const std::array<double, 4>& rankedScores)
{
	std::ofstream scoreFileWriter{ DecideRankingFileName(difficulty), ios::out | ios::trunc };

	for (int i = 0; i < 3; i++) {
		scoreFileWriter << rankedScores[i] << endl;
	}

}

std::string Ranking::DecideRankingFileName(Difficulty difficulty)
{
	switch (difficulty)
	{
	case Difficulty::easy:
		return "rank_eazy.txt";
	case Difficulty::normal:
		return "rank_normal.txt";
	case Difficulty::hard:
		return "rank_hard.txt";
	case Difficulty::god:
		return "rank_god.txt";
	}
	return std::string{};
}