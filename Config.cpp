#include"stdafx.h"

Config::Config(ISceneChanger* changer):BaseScene(changer){
}

void Config::Init(){
	ImageGraph=LoadGraph("NULL");
}
void Config::Update(){
	if(GetKey(KEY_INPUT_ESCAPE)!=0){
		SceneChanger->ChangeScene(EnumSceneMenu);
	}
}

void Config::Draw(){
	BaseScene::Draw();
	DrawString(0,0,"�R���t�B�O��ʐ���",GetColor(255,255,255));
	DrawString(0,460,"ESC�L�[�Ń��j���[�ɖ߂�܂�",WHITE);
}