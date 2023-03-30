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
	// �Խ�easy2d
	void onUpdate();
	// ������ʹ�ú�ɫ��ʶ��ʵ����ײ��,��ɫ��ʶ����Ϊ�ɴ�Խ����ײ��
	bool debugModel = true;
	static MonoSystem* GetInstance();
	/// <summary>
	/// ��������
	/// </summary>
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	/// <summary>
	/// ɾ������
	/// </summary>
	friend void DestroyObject(MonoObject* destroyObject);
	/// <summary>
	/// ֡����
	/// </summary>
	void Run();
	/// <summary>
	/// ��ȡָ����Χ�ڿ���ײ��λ
	/// </summary>
	vector<MonoObject*> caculateCrash(Utils::Rect address);
	/// <summary>
	/// ��ȡ���������л�Ծ����
	/// </summary>
	vector<MonoObject*> getAllObjects();
	/// <summary>
	/// ��ȡ��ǰ֡��������
	/// </summary>
	vector<MonoObject*> getNewObjects();
private:
	MonoSystem() = default;
	int hashID=0;
	// ��ǰ֡��������
	vector<MonoObject*> m_newObjects;
	// �ȴ�ɾ��������
	queue<MonoObject*> m_deletingObjects;
	// ��ǰ�ؿ���Ծ������
	map<MonoObject*, bool> m_activeObjects;
	// ��ǰ֡Ҫ�����ƶ�������
	queue<MonoObject*> m_moveingObjects;
	// ������ײ������,Ԫ���һ��ֵΪ����
	map < pair<MonoObject*, MonoObject*>,bool> m_crashObjects;
	void AddObject(MonoObject* obj);
	void DeleteObject(MonoObject* obj);
	void calculateMove();
	void noticeCrash();
};

template <typename T> 
inline static T* CreateObject(Utils::Rect body) 
{	
	//��ʼ����
	MonoObject* newObject = new T();
	MonoSystem::GetInstance()->AddObject(newObject);
	// ���뵽����������,����easy2d����ʾ
	MonoSystem::GetInstance()->addChild(newObject);
	// ������ز���
	newObject->setPos(body.posx,body.posy);
	newObject->setSize(body.width, body.height);
	newObject->hashId = ++MonoSystem::GetInstance()->hashID;
	newObject->onCreate();
	// �ж��Ƿ�ʼdebugģʽ
	if (MonoSystem::GetInstance()->debugModel)
	{
		//���ɴ�Խ������Ƴɺ�ɫ���ɴ�Խ������Ƴ���ɫ
		auto Rect = ShapeNode::createRect(newObject->getSize());
		Rect->setDrawingMode(DrawingStyle::Mode::Round);
		if (!newObject->canThrough) Rect->setStrokeColor(Color::Red);
		else Rect->setStrokeColor(Color::Green);
		newObject->addChild(Rect);
	}
	// ��̬ת��
	return dynamic_cast<T*>(newObject);
}

inline static void DestroyObject(MonoObject* destroyObject)
{
	MonoSystem::GetInstance()->DeleteObject(destroyObject);
}