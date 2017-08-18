#include"stdafx.h"
#include<DxLib.h>
#include"WaitTimer.h"
#include"MyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//ここから
	SetGraphMode(MyWindow::Width, MyWindow::Height, 16);
	SetWindowIconID(IDI_ICON1);
	SetMainWindowText("避け続けろ");

	ChangeWindowMode(TRUE);
	SetOutApplicationLogValidFlag(FALSE);
	if (DxLib_Init() == -1) {
		MessageBox(GetMainWindowHandle(), _T("起動失敗"), _T("エラー！"), MB_OK);
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//ここまで起動前のアレコレ

	//乱数を初期化する
	//しかしこれはC言語のクソのような乱数生成器のため、使わないこと
	//C++の場合<random>内のメルセンヌ・ツイスタあたりを使おう
	srand((unsigned)time(NULL));

	SceneMgr sceneMgr{};

	//私が書いたWaitTimerクラスとDxLib::WaitTimer関数の名前が衝突している
	//だからこういう風に書いてグローバル空間のWaitTimerにアクセスしている（正しいのかは知らない）
	//名前空間の管理はしっかりしたいね、というお話
	::WaitTimer waitTimer;

	//コンストラクタとデストラクタではなくInit,Endを定義した理由はどこかのサイトの丸写しであり
	//私自身よく理由が分かってないので参考にしてはいけない
	sceneMgr.Init();


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		KeyUpdate();
		sceneMgr.Update();
		sceneMgr.Draw();
		waitTimer.Update();
		waitTimer.Wait();
	}

	sceneMgr.End();
	DxLib_End();
	return 0;
}