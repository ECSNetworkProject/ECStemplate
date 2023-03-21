#pragma once
#include "head.h"

enum objectType {
	none,
	player,
	enemy,
	groud,
	effect,
	camera,
	UI     //��ǩ˳�����ִ��˳��
};

/// <summary>
/// �����е����嶼Ҫ�̳�
/// </summary>
class MonoObject
{
public:
	// �������ݣ��������ֱ�ӷ�monoobject����
	int life = 5;
	int score = 0;
	// ��ȡ�������������
	Utils::Rect body;
	// �����ƶ��ٶȣ���λ�ֱ�Ϊm/s,û���ƶ��ٶȵ����岻������������ײ
	float vx = 0;
	float vy = 0;
	// ������������
	objectType type=none;
	// ����Ψһ���
	int GetHashID();
	// �ܷ�Խ,Ϊtrue�������ײ���������壬�����ܱ���������ײ��
	bool canThrough = false;
	// ���崴��ʱ����
	virtual void onCreate();
	// ���巢����ײʱ����
	virtual void onCrash(MonoObject* collider);
	// ÿ֡����
	virtual void onFrameUpdate();
	// ��ȡ����������Ϣ(����������ƶ���Ϣ��
	virtual void onGetMessage(ExMessage message);
	// ��Ԫ�����������޸Ĺ�ϣid
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	// ��������
	virtual ~MonoObject();
protected:
	MonoObject() = default;
private:
	int hashId = 0;
};

