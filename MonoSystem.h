#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "MonoObject.h"
#include "head.h"
#include "SceneConfig.h"
using namespace std;
using namespace easy2d;


class MonoSystem : public Node
{
public:
	// 对接easy2d
	void onUpdate();
	// 开启后使用红色标识真实的碰撞体,绿色标识设置为可穿越的碰撞体
	bool debugModel = true;
	static MonoSystem* GetInstance();
	/// <summary>
	/// 创建物体
	/// </summary>
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	/// <summary>
	/// 删除物体
	/// </summary>
	friend void DestroyObject(MonoObject* destroyObject);
	/// <summary>
	/// 帧主体
	/// </summary>
	void Run();
	/// <summary>
	/// 获取指定范围内可碰撞单位
	/// </summary>
	vector<MonoObject*> caculateCrash(Utils::Rect address);
	/// <summary>
	/// 获取场景中所有活跃物体
	/// </summary>
	vector<MonoObject*> getAllObjects();
	/// <summary>
	/// 获取当前帧新增物体
	/// </summary>
	vector<MonoObject*> getNewObjects();
private:
	MonoSystem() = default;
	int hashID=0;
	// 当前帧新增物体
	vector<MonoObject*> m_newObjects;
	// 等待删除的物体
	queue<MonoObject*> m_deletingObjects;
	// 当前关卡活跃的物体
	map<MonoObject*, bool> m_activeObjects;
	// 当前帧要进行移动的物体
	queue<MonoObject*> m_moveingObjects;
	// 发生碰撞的物体,元组第一个值为主体
	map < pair<MonoObject*, MonoObject*>,bool> m_crashObjects;
	void AddObject(MonoObject* obj);
	void DeleteObject(MonoObject* obj);
	void calculateMove();
	void noticeCrash();
};

template <typename T> 
inline static T* CreateObject(Utils::Rect body) 
{	
	//开始创建
	MonoObject* newObject = new T();
	MonoSystem::GetInstance()->AddObject(newObject);
	// 加入到管理器当中,用于easy2d的显示
	MonoSystem::GetInstance()->addChild(newObject);
	// 设置相关参数
	newObject->setPos(body.posx,body.posy);
	newObject->setSize(body.width, body.height);
	newObject->hashId = ++MonoSystem::GetInstance()->hashID;
	newObject->onCreate();
	// 判断是否开始debug模式
	if (MonoSystem::GetInstance()->debugModel)
	{
		//不可穿越物体绘制成红色，可穿越物体绘制成绿色
		auto Rect = ShapeNode::createRect(newObject->getSize());
		Rect->setDrawingMode(DrawingStyle::Mode::Round);
		if (!newObject->canThrough) Rect->setStrokeColor(Color::Red);
		else Rect->setStrokeColor(Color::Green);
		newObject->addChild(Rect);
	}
	// 动态转化
	return dynamic_cast<T*>(newObject);
}

inline static void DestroyObject(MonoObject* destroyObject)
{
	MonoSystem::GetInstance()->DeleteObject(destroyObject);
}