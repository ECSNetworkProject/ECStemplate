#include "AnimationManager.h"
#include "Utils.h"
#include "tools.h"
#define PI 3.14159265359

AnimationManager::AnimationManager()
{
	type = effect;
}

AnimationManager::~AnimationManager()
{
	cout << "动画部分清除" << endl;
}

void AnimationManager::onFrameUpdate()
{
}

void AnimationManager::createAnimation(const vector<wstring>& imagenames,
	int sizeX, int sizeY)
{
	vector<IMAGE> images;
	for (const auto& filename : imagenames)
	{
		IMAGE image;
		loadimage(&image, filename.c_str(),sizeX,sizeY);
		images.push_back(image);
	}
	animations[finalType] = images;
}

// 复制数组
template <typename T>
inline void MultipleVector(vector<T> &target,int n)
{
	// 用于复制的数组
	vector<T> copyArray;
	int originLength = target.size();
	for (int i = 0; i < originLength; i++)
	{
		for (int j = 0; j < n; j++)
			copyArray.push_back(target[i]);
	}
	target = copyArray;
}

void AnimationManager::initAnimation(animationType animType,int sizeX,int sizeY)
{
	finalType = animType;
	vector<wstring> fileName;
	switch (finalType)
	{
	case Man_walk:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "man");
		break;
	case DebuffMan_walk:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "mandebuff");
		break;
	case Pangxie_walk:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "螃蟹");
		break;
	case Bat_fly:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "Bat");
		break;
	case Ghost_fly:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "ghost");
		break;
	case Pig_Idle:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "pigIdle");
		break;
	case Pig_Walk:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "pigWalk");
		break;
	case Coin_rotate:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "coin");
		break;
	case Man_Idle:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "Idle");
		break;
	case Music:
		fileName = Utils::FindAnimationFiles("./Image/Animation", "音乐动效");
		break;
	default:
		break;
	}
	MultipleVector(fileName, 4);
	createAnimation(fileName,sizeX,sizeY);
}

void AnimationManager::playAnimation(int x, int y)		
{
	auto it = animations.find(finalType);
	if (it == animations.end())
	{
		//cout << "无该动画类型" << endl;
		return;
	}
	else
	{
		//绘制动画
		drawImg(x, y, &(it->second[i]));
		i = (i + 1) % it->second.size();
	}
}
