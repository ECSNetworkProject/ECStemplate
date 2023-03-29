#include <iostream>
#include<graphics.h>
#include<stdio.h>
#include<vector>
#include<mmsystem.h>
#include <conio.h>
#include"button.h"
#include "head.h"
#include "SceneConfig.h"
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
	// 判断点击
	if (!MouseStatus && Input::isDown(MouseCode::Left))
	{
		// 获取自身边界
		auto Rect = this->getBoundingBox();
		// 判断点是否在边界内部
		if (Rect.containsPoint(Input::getMousePos()))
		{
			MouseStatus = true;
			onClick();
		}
	}
	// 需要记录鼠标状态，否则会出现持续按压
	if (Input::isRelease(MouseCode::Left)) MouseStatus = false;
}


void CustomButton::onClick()
{
}

CustomButton::~CustomButton()
{
	delete button;
}
