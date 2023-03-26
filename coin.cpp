#include "coin.h"
#include "MonoSystem.h"

void coin::onCreate()
{
	canThrough = true;
	initAnimation(Coin_rotate);
	setPosX(rand() % 600);
	setPosY(0);
	vy = -100;
}

void coin::onFrameUpdate()
{
	playAnimation(getPosX(), getPosY());
	vy += 1;
	if (getPosY() > 800)
		DestroyObject(this);
}
