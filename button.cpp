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
	// easy2d,�������ýڵ����꣬addchild֮��ڵ��븸�ڵ�ͬ���ƶ�
	button = ShapeNode::createRect(getSize());
	button->setFillColor(Color::Gray);
	this->addChild(button);
	// �����ı�
	text = gcnew Text;
	text->setText("Text");
	text->setFontSize(50);
	this->addChild(text);
}


void CustomButton::onFrameUpdate()
{
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(getPosX(), getPosY(), 
		getPosX() + getSize().width, getPosY() + getSize().height);
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

CustomButton::~CustomButton()
{
	delete button;
}
