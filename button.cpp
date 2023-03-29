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
	// easy2d,无需设置节点坐标，addchild之后节点与父节点同步移动
	button = ShapeNode::createRect(getSize());
	button->setFillColor(Color::Gray);
	this->addChild(button);
	// 设置文本
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
