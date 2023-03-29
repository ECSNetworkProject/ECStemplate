#pragma once
#include "head.h"
using namespace easy2d;

enum objectType {
	none,
	player,
	enemy,
	groud,
	effect,
	camera,
	UI     //标签顺序决定执行顺序
};

/// <summary>
/// 场景中的物体都要继承
/// </summary>
class MonoObject:virtual public Node
{
public:
	// 物体数据，方便起见直接放monoobject就行
	int life = 5;
	int score = 0;
	Utils::Rect GetBody();
	// 物体移动速度，单位分别为m/s,没有移动速度的物体不会主动产生碰撞
	float vx = 0;
	float vy = 0;
	// 代表物体类型
	objectType type=none;
	// 物体唯一编号
	int GetHashID();
	// 能否穿越,为true情况可以撞到其他物体，但不能被其他物体撞到
	bool canThrough = false;
	// 物体创建时调用
	virtual void onCreate();
	// 物体发生碰撞时调用
	virtual void onCrash(MonoObject* collider);
	// 每帧调用
	virtual void onFrameUpdate();
	// 友元函数，用于修改哈希id
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	// 析构函数
	virtual ~MonoObject();
protected:
	MonoObject() = default;
private:
	int hashId = 0;
};

