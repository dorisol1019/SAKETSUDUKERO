#include"stdafx.h"
static int BufFlag[256];
void KeyUpdate(){
	char Buf[256];
	GetHitKeyStateAll(Buf);
	for(int i=0;i<256;i++){
		if(Buf[i]!=0){
			BufFlag[i]++;
		}else{
			BufFlag[i]=0;
		}
	}
}
int GetKey(int KeyCode){
	return BufFlag[KeyCode];
}