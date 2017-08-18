#include"stdafx.h"
#include<memory>
#include<string>
#include"Difficulty.h"
#include"Color.h"

//constexr : 定数式
//この場合ただのコンパイル時定数としてしか使ってないので、気にしなくて良い
//まずは大体constと同じという認識でいいんじゃないかな
constexpr int Eazy_Y = 240;
constexpr int Normal_Y = 270;
constexpr int Hard_Y = 300;
constexpr int God_Y = 330;
constexpr int End_Y = 360;

constexpr int X = 440;

Menu::Menu(ISceneChanger* changer) :BaseScene(changer) {}

void Menu::Init() {
	backgroundImage = LoadGraph("picture/Title.bmp");
	bgmFileName = "Music/BGM/theme01f_.mp3";
	StopMusic();
}

static int NowSelect = eazy;

void Menu::Update() {
	Music();
	if (GetKey(KEY_INPUT_DOWN) == 1 || GetKey(KEY_INPUT_S) == 1) {
		NowSelect = (NowSelect + 1) % (allNum);
	}
	else if (GetKey(KEY_INPUT_UP) == 1 || GetKey(KEY_INPUT_W) == 1) {
		NowSelect = (NowSelect + (allNum - 1)) % allNum;
	}

	bool isStartGame = false;
	Difficulty selectedDifficulty;
	if (GetKey(KEY_INPUT_RETURN) == 1 || GetKey(KEY_INPUT_Z) == 1) {
		switch (NowSelect) {
		case First:
			selectedDifficulty = Difficulty::easy;
			isStartGame = true;
			break;
		case Second:
			selectedDifficulty = Difficulty::normal;
			isStartGame = true;
			break;
		case Third:
			selectedDifficulty = Difficulty::hard;
			isStartGame = true;
			break;
		case Fourth:
			selectedDifficulty = Difficulty::god;
			isStartGame = true;
			break;
		case Fifth:
			End();
			exit(-1);
			break;
		default:
			MessageBox(GetMainWindowHandle(), _T("Menu::Updateでエラーが発生しました"), _T("エラー！"), MB_OK);
			End();
			exit(-1);
			break;
		}
	}

	if (isStartGame) {
		sceneChanger->ChangeScene(std::make_unique<Game>(sceneChanger,selectedDifficulty));
	}
}


void Menu::Draw() {
	BaseScene::Draw();
	DrawString(X, Eazy_Y, "かんたん", Color::White());
	DrawString(X, Normal_Y, "ふつう", Color::White());
	DrawString(X, Hard_Y, "むずかしい", Color::White());
	DrawString(X, God_Y, "おに", Color::White());
	DrawString(X, End_Y, "おわる", Color::White());
	int SelectY = 0;
	switch (NowSelect) {
	case First:
		SelectY = Eazy_Y;
		break;
	case Second:
		SelectY = Normal_Y;
		break;
	case Third:
		SelectY = Hard_Y;
		break;
	case Fourth:
		SelectY = God_Y;
		break;
	case Fifth:
		SelectY = End_Y;
		break;
	default:
		MessageBox(GetMainWindowHandle(), _T("Menu::Drawでエラーが発生しました"), _T("エラー！"), MB_OK);
		End();
		exit(-1);
		break;
	}
	DrawString(X - 30, SelectY, "■", Color::White());
}


void Menu::Music() {
	if (CheckMusic() != 1) {
		PlayMusic(bgmFileName.c_str(), DX_PLAYTYPE_LOOP);
		SetVolumeMusic(155);
	}
}