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
Button::Button()
{
	canThrough = true;
	type = UI;
}



void Button::onFrameUpdate()
{
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(body.posx, body.posy, body.posx + body.width, body.posy + body.height);
	int textWide = textwidth(Text);
	int textHeight = textheight(Text);
	outtextxy(body.posx + (body.width - textWide) / 2, body.posy + (body.height - textHeight) / 2, Text);
	setbkcolor(WHITE);

}
void Button::onGetMessage(ExMessage message)
{
	if (message.message == WM_LBUTTONDOWN &&
		message.x >= body.posx && message.x <= body.posx + body.width &&
		message.y >= body.posy && message.y <= body.posy + body.height)
	{
		onClick();
	}
}

void Button::onClick()
{
}
