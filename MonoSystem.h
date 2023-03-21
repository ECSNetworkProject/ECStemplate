#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "MonoObject.h"
#include "head.h"
#include "SceneConfig.h"
using namespace std;


class MonoSystem
{
public:
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
private:
	MonoSystem() = default;
	int hashID=0;
	// �ȴ�ɾ��������
	queue<MonoObject*> m_deletingObjects;
	//�Զ���map��key����˳��,���������ǩ˳��������
	struct ObjectCompare {
		bool operator()(const MonoObject* l, const MonoObject* r)const
		{
			return l->type < r->type;
		}
	};
	// ��ǰ�ؿ���Ծ������
	map<MonoObject*, bool, ObjectCompare> m_activeObjects;
	// ��ǰ֡Ҫ�����ƶ�������
	queue<MonoObject*> m_moveingObjects;
	// ������ײ������,Ԫ���һ��ֵΪ����
	map < pair<MonoObject*, MonoObject*>,bool> m_crashObjects;
	void AddObject(MonoObject* obj);
	void DeleteObject(MonoObject* obj);
	void noticeMessage(MonoObject* obj, ExMessage* msg);
	void calculateMove();
	void noticeCrash();
};

template <typename T> 
inline static T* CreateObject(Utils::Rect body) 
{	
	//��ʼ����
	MonoObject* newObject = new T();
	MonoSystem::GetInstance()->AddObject(newObject);
	newObject->body = body;
	newObject->hashId = ++MonoSystem::GetInstance()->hashID;
	newObject->onCreate();
	// ��̬ת��
	return dynamic_cast<T*>(newObject);
}

inline static void DestroyObject(MonoObject* destroyObject)
{
	MonoSystem::GetInstance()->DeleteObject(destroyObject);
}