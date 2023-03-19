#pragma once
#include<easyx.h>

//把像素的颜色拆解出来ARGB
typedef struct _ARGB
{
	byte a; 
	byte r; 
	byte g; 
	byte b;

}ARGB;

// 把颜色拆解
ARGB color2Argb(DWORD c);

DWORD argb2Color(ARGB c);
//把彩色图转成黑白图
void toGray(IMAGE* src);
/*
*@png透明贴图
*/
void drawImg(int x, int y, IMAGE* src);
