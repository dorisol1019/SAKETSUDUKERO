#include"stdafx.h"
#include<DxLib.h>
#include"WaitTimer.h"
#include"MyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//��������
	SetGraphMode(MyWindow::Width, MyWindow::Height, 16);
	SetWindowIconID(IDI_ICON1);
	SetMainWindowText("����������");

	ChangeWindowMode(TRUE);
	SetOutApplicationLogValidFlag(FALSE);
	if (DxLib_Init() == -1) {
		MessageBox(GetMainWindowHandle(), _T("�N�����s"), _T("�G���[�I"), MB_OK);
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//�����܂ŋN���O�̃A���R��

	//����������������
	//�����������C����̃N�\�̂悤�ȗ���������̂��߁A�g��Ȃ�����
	//C++�̏ꍇ<random>���̃����Z���k�E�c�C�X�^��������g����
	srand((unsigned)time(NULL));

	SceneMgr sceneMgr{};

	//����������WaitTimer�N���X��DxLib::WaitTimer�֐��̖��O���Փ˂��Ă���
	//�����炱���������ɏ����ăO���[�o����Ԃ�WaitTimer�ɃA�N�Z�X���Ă���i�������̂��͒m��Ȃ��j
	//���O��Ԃ̊Ǘ��͂������肵�����ˁA�Ƃ������b
	::WaitTimer waitTimer;

	//�R���X�g���N�^�ƃf�X�g���N�^�ł͂Ȃ�Init,End���`�������R�͂ǂ����̃T�C�g�̊ێʂ��ł���
	//�����g�悭���R���������ĂȂ��̂ŎQ�l�ɂ��Ă͂����Ȃ�
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