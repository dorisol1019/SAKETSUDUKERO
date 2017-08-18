#include"stdafx.h"

BaseScene::BaseScene(ISceneChanger* changer){
	backgroundImage=NULL;
	sceneChanger=changer;
}
void BaseScene::End(){

	DeleteGraph(backgroundImage);
}
void BaseScene::Draw(){
	DrawGraph(0,0,backgroundImage,FALSE);
}