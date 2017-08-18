#ifndef STDAFX_H
#define STDAFX_H  

typedef enum{
	First,Second,Third,Fourth,Fifth,Sixth
}eNum;


//include
//　クソの塊のようなヘッダファイルの読み込み方
//　こうすると各ファイルの関係がガチガチに絡み合ったり、
//　コンパイル速度が遅くなったり
//　自分のヘッダの順番を入れ替えるだけでコンパイルエラー起こしたりと
//　使いものにならないので絶対にしないこと
#include	"DxLib.h"
#include	"resource.h"
#include	<ctime>
#include	<vector>
#include	<deque>
#include	<string>
#include	<fstream>
#include	<algorithm>
#include	<functional>
using namespace std;
#include	"GetKey.h"
#include	"ISceneChanger.h"
#include	"ScoreLabel.h"
#include	"CountDown.h"
#include	"BaseScene.h"
#include	"BaseCharacter.h"
#include	"Escapee.h"
#include	"Opponent.h"
#include	"Ranking.h"
#include	"Game.h"
#include	"Menu.h"
#include	"SceneMgr.h"


#endif