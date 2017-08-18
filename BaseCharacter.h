#pragma once

//�L�����N�^�[�i���@�E�G�j�̊��N���X
//���@�ƓG�̓R�����p������
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