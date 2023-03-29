#pragma once
#include <vector>
#include "Button.h"
#include "Utils.h"
#include "ÒôÀÖºĞ.h"

class GameWindow:public MonoObject
{
public:
	void onCreate();
	void musicMenu();
	void onFrameUpdate();
private:
	// ¼ÇÂ¼ÒôÀÖºĞÖ¸ÕëÓëÒôÀÖºĞ×´Ì¬
	vector<ÒôÀÖºĞ*> musicboxes;
	// ¼ÇÂ¼¿ªÆôµÄÒôÀÖºĞ
	ÒôÀÖºĞ* openingMusicbox;
};