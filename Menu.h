#pragma once

#include"stdafx.h"

//都合によりint型にキャストしたいからenumを使っているが
//普通はenum class(C++11より)を使うこと
enum MenuItem{
	eazy,
	normal,
	hard,
	god,
	gameEnd,

	allNum //総数
};

//メニュー画面のシーンクラス
//難しいことをしているように見えるが、要は参考資料のほぼコピペである
//参考資料
//新ゲームプログラミングの館
//http://dixq.net/g/sp_07.html
class Menu :public BaseScene {
private:
	string bgmFileName;
public:
	Menu(ISceneChanger* changer);
	void Init() override;
	void Update() override;
	void Draw() override;
	void Music();
};