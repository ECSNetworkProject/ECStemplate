#include <iostream>
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
}


void CustomButton::onClick()
{
}

CustomButton::~CustomButton()
{
	delete button;
}
