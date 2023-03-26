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
void CustomButton::onCreate()
{
	canThrough = true;
	type = UI;
	// easy2d,无需设置节点坐标，addchild之后节点同步移动
	button = ShapeNode::createRect(getSize());
	button->setFillColor(Color::Gray);
	this->addChild(button);
}


void CustomButton::onFrameUpdate()
{
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(getPosX(), getPosY(), 
		getPosX() + getSize().width, getPosY() + getSize().height);
	// 放置按钮名字
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
