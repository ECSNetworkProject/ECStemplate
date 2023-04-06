﻿#include "MonoSystem.h"
#include "NetWorkSystem.h"


// 用于控制每秒多少帧
clock_t lastFrame = clock();
int frameCnt = 0;

void MonoSystem::onUpdate()
{
	// 固定时间戳运行一次,保证帧同步
	if (clock() - lastFrame > frameCnt * 1000 / Sceneconfig::GetInstance()->MaxFrame)
	{
		NetworkSystem::GetInstance()->Run();
		// 自己需要后运行，否则初始化物体其他系统无法捕捉
		Run();
		frameCnt++;
		if (frameCnt == Sceneconfig::GetInstance()->MaxFrame)
		{
			frameCnt = 0;
			// cout << Sceneconfig::GetInstance()->MaxFrame << "帧运行时间" << clock() - lastFrame << endl;
			lastFrame = clock();
		}
		// cout << "第" << frameCnt << "帧:" << clock() << endl;
	}
}

MonoSystem* MonoSystem::GetInstance()
{
	// 饿汉式
	static MonoSystem m_Instance;
	return &m_Instance;
}


void MonoSystem::Run()
{
	// 新的一帧开始，清除前一帧新增物体
	m_newObjects.clear();
	//先清除要删除的物体
	while (!m_deletingObjects.empty())
	{
		// 获取当前帧删除的物体
		MonoObject* obj = m_deletingObjects.front();
		m_deletingObjects.pop();
		// 查询字典看看物体是否已经删除，避免重复删除
		map<MonoObject*, bool>::iterator iter = m_activeObjects.find(obj);
		if (iter != m_activeObjects.end())
		{
			// 从父节点移除，避免继续走更新逻辑
			obj->removeFromParent();
			m_activeObjects.erase(obj);
			delete obj;
		}
	}
	// 创建迭代器，准备执行其他物体的动作
	map<MonoObject*, bool>::iterator it; 
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// 执行物体帧更新
		it->first->onFrameUpdate();
		if (it->first->vx != 0 || it->first->vy != 0) m_moveingObjects.push(it->first);
	}
	// 计算物体移动
	calculateMove();
}


void MonoSystem::AddObject(MonoObject* obj)
{
	m_activeObjects.insert(pair<MonoObject*, bool>(obj, true));
	m_newObjects.push_back(obj);
}

void MonoSystem::DeleteObject(MonoObject* obj)
{
	m_deletingObjects.push(obj);
}


void MonoSystem::calculateMove()
{
	// 遍历m_moveingObjects并获取他们的速度v，来更改他们的位置
	while (!m_moveingObjects.empty())
	{
		// 逐个获取准备移动的物体
		MonoObject* obj = m_moveingObjects.front();
		m_moveingObjects.pop();
		// 计算当前帧位移
		float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;
		float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;
		// 无碰撞情况下理想的运动位置
		Utils::Rect address = Utils::Rect{ obj->getPosX() + x,obj->getPosY() + y ,
											obj->getSize().width,obj->getSize().height};
		
		// 获取理想运动位置处所有可能会碰到的物体（可穿越物体不计算）
		vector<MonoObject*> crashObjs = caculateCrash(address);
		MonoObject *crashObj_x= nullptr,*crashObj_y= nullptr;
		// 分别找到x和y方向上碰到的第一个物体
		for (int i = 0; i < crashObjs.size(); i++)
		{
			MonoObject* it = crashObjs[i];
			// 排除自身
			if (it->GetHashID() == obj->GetHashID()) continue;
			// x方向上碰到的第一个物体
			if (crashObj_x== nullptr ||
				abs(crashObj_x->getPosX() - address.posx) < abs(it->getPosX() - address.posx))
			{
				crashObj_x = it;
			}
			// y方向上碰到的第一个物体
			if (crashObj_y == nullptr ||
				abs(crashObj_y->getPosY() - address.posy) < abs(it->getPosY() - address.posy))
			{
				crashObj_y = it;
			}
		}
		if (crashObj_x != nullptr)
		{
			// 添加到碰撞单位，key代表碰撞者，value代表被碰撞者
			m_crashObjects[make_pair(obj, crashObj_x)] = true;
			// 如果碰撞者不可穿越，两者均会产生碰撞
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x,obj)] = true;
		}
		if (crashObj_y != nullptr)
		{
			m_crashObjects[make_pair(obj, crashObj_y)] = true;
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)] = true;
		}
		if (obj->canThrough || 
			(crashObj_x== nullptr && crashObj_y == nullptr))
		{
			// 改变body的位置
			obj->setPos(address.posx,address.posy) ;
		}
		
	}
	// 执行碰撞效果
	noticeCrash(); 
}



vector<MonoObject*> MonoSystem::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;
	map<MonoObject*, bool>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// 计算所有不能穿越的物体的碰撞情况
		if (!it->first->canThrough && Utils::CrossLine(
			it->first->GetBody(), address))
		{
			crashObjs.push_back(it->first);
		}
	}
	return crashObjs;
}

vector<MonoObject*> MonoSystem::getAllObjects()
{
	vector<MonoObject*> rev;
	map<MonoObject*, bool>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		rev.push_back(it->first);
	}
	return rev;
}

vector<MonoObject*> MonoSystem::getNewObjects()
{
	return m_newObjects;
}


void MonoSystem::noticeCrash()
{
	// 如果noticeMove碰到了不可穿越物体，通知他们碰到了什么
	map<pair<MonoObject*, MonoObject*>, bool>::iterator it;
	for (it =m_crashObjects.begin(); it != m_crashObjects.end(); it++) {
		it->first.first->onCrash(it->first.second);
	}
	m_crashObjects.clear();

}
