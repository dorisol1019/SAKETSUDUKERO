#pragma once

//キャラクター（自機・敵）の基底クラス
//自機と敵はコレを継承する
class BaseCharacter{
protected:
	int Graph;
	int x,y,width,height;
public:
	BaseCharacter();
	~BaseCharacter(){}

	virtual void Draw();
	virtual void Update();
	virtual void Init();
	virtual void End();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();


};