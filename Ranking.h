#pragma once
#include "stdafx.h"
#include<array>
#include<string>
#include"ScoreLabel.h"

//�����L���O�̃V�[��
class Ranking :
	public BaseScene
{

private:
	std::string bgmFileName;
	bool isRanked = false;
	double currentScore = 0;
	ScoreLabel scoreLabels[3];

	int frameCount = 0;

	int currentScoreTimeFontHandle;
	int messageFontHandle;
public:
	Ranking(ISceneChanger*sceneChanger, Difficulty difficulty, double currentScore);
	~Ranking();


	void Init() override;
	void Update() override;
	void Draw() override;
	void End() override;
	void Music();

private:
	//�����̃����L���O�f�[�^��ǂݍ���
	std::array<double, 3>LoadRankedScores(const Difficulty difficulty);
	
	//���������L���O�f�[�^�ƐV�K�X�R�A���܂��܂����ĐV���������L���O�ɂ���
	std::array<double, 4>MakeNewRankingScores(const std::array<double, 3>& oldRankedScore, const double& currentScore);

	//�����L���O�f�[�^���t�@�C���ɏ�������
	void WriteRankedScores(const Difficulty difficulty, const std::array<double, 4>& rankedScores);


	std::string DecideRankingFileName(Difficulty difficulty);
};
