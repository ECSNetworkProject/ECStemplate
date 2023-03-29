#include "coin.h"
#include "MonoSystem.h"

void coin::onCreate()
{
	canThrough = true;
	setPosX(rand() % 600);
	setPosY(0);
	vy = -100;
	img = gcnew Sprite;
	img->open("Image/coin1.png");
	this->addChild(img);
}

void coin::onFrameUpdate()
{
	vy += 1;
	if (getPosY() > 800)
		DestroyObject(this);
}
