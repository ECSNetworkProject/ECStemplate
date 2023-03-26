#include <iostream>
#include "easyx.h"
#include<graphics.h>
#include<stdio.h>
#include<vector>
#include<mmsystem.h>
#include <conio.h>
#include"button.h"
#include "head.h"
#include "SceneConfig.h"
#include "GameVoice.h"
using namespace Utils;
CustomButton::CustomButton()
{
	canThrough = true;
	type = UI;
}



void CustomButton::onFrameUpdate()
{
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(getPosX(), getPosY(), 
		getPosX() + getSize().width, getPosY() + getSize().height);
	// ·ÅÖÃ°´Å¥Ãû×Ö
	int textWide = textwidth(Text);
	int textHeight = textheight(Text);
	outtextxy(getPosX() + (getSize().width - textWide) / 2, 
		getPosY() + (getSize().height - textHeight) / 2, Text);
	setbkcolor(WHITE);

}
void CustomButton::onGetMessage(ExMessage message)
{
	if (message.message == WM_LBUTTONDOWN &&
		message.x >= getPosX() && message.x <= getPosX() + getSize().width &&
		message.y >= getPosY() && message.y <= getPosY() + getSize().height)
	{
		onClick();
	}
}

void CustomButton::onClick()
{
}
