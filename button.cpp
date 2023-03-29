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
	// �жϵ��
	if (!MouseStatus && Input::isDown(MouseCode::Left))
	{
		// ��ȡ����߽�
		auto Rect = this->getBoundingBox();
		// �жϵ��Ƿ��ڱ߽��ڲ�
		if (Rect.containsPoint(Input::getMousePos()))
		{
			MouseStatus = true;
			onClick();
		}
	}
	// ��Ҫ��¼���״̬���������ֳ�����ѹ
	if (Input::isRelease(MouseCode::Left)) MouseStatus = false;
}


void CustomButton::onClick()
{
}

CustomButton::~CustomButton()
{
	delete button;
}
