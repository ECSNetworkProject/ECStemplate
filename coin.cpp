#include "coin.h"
#include "MonoSystem.h"

void coin::onCreate()
{
	initAnimation(Coin_rotate);
	body.posx = rand() % 600;
	body.posy = 0;
	vy = -100;
}

void coin::onFrameUpdate()
{
	playAnimation(body.posx, body.posy);
	vy += 1;
	if (body.posy > 800) 
		DestroyObject(this);
}
