#pragma once
#include<easyx.h>

//�����ص���ɫ������ARGB
typedef struct _ARGB
{
	byte a; 
	byte r; 
	byte g; 
	byte b;

}ARGB;

// ����ɫ���
ARGB color2Argb(DWORD c);

DWORD argb2Color(ARGB c);
//�Ѳ�ɫͼת�ɺڰ�ͼ
void toGray(IMAGE* src);
/*
*@png͸����ͼ
*/
void drawImg(int x, int y, IMAGE* src);
