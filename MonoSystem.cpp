#include "MonoSystem.h"

MonoSystem* MonoSystem::GetInstance()
{
	// ����ʽ
	static MonoSystem m_Instance;
	return &m_Instance;
}

// ��ʾ��ײ��߿�
void ShowCollide(Utils::Rect address,int color)
{
	// ����������ɫ
	setlinecolor(color);
	// ���ƾ���
	rectangle((int)address.posx, (int)address.posy,
		(int)address.posx + (int)address.width,
		(int)address.posy + (int)address.height);
	setlinecolor(WHITE);
}


void MonoSystem::Run()
{
	//�����Ҫɾ��������
	while (!m_deletingObjects.empty())
	{
		// ��ȡ��ǰ֡ɾ��������
		MonoObject* obj = m_deletingObjects.front();
		m_deletingObjects.pop();
		// ��ѯ�ֵ俴�������Ƿ��Ѿ�ɾ���������ظ�ɾ��
		map<MonoObject*, bool>::iterator iter = m_activeObjects.find(obj);
		if (iter != m_activeObjects.end())
		{
			m_activeObjects.erase(obj);
			delete obj;
		}
	}
	// ������������׼��ִ����������Ķ���
	map<MonoObject*, bool>::iterator it; 
	// ��ȡ��ǰ֡��Ҳ���
	ExMessage msg;
	bool hasMessage=peekmessage(&msg);
	map<MonoObject*, bool> UIObjects;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// �����巢����Ϣ
		if (hasMessage) noticeMessage(it->first,&msg);
		// ִ������֡����
		it->first->onFrameUpdate();
		if (it->first->vx != 0 || it->first->vy != 0) m_moveingObjects.push(it->first);
		// �ж��Ƿ�ʼdebugģʽ
		if (debugModel)
		{
			// ���ɴ�Խ������Ƴɺ�ɫ���ɴ�Խ������Ƴ���ɫ
			if (!it->first->canThrough) ShowCollide(it->first->body, RED);
			else ShowCollide(it->first->body, GREEN);
		}
	}
	// ���������ƶ�
	calculateMove();
}


void MonoSystem::AddObject(MonoObject* obj)
{
	m_activeObjects.insert(pair<MonoObject*, bool>(obj, true));
}

void MonoSystem::DeleteObject(MonoObject* obj)
{
	m_deletingObjects.push(obj);
}

void MonoSystem::noticeMessage(MonoObject* obj, ExMessage* msg)
{
	obj->onGetMessage(*msg);
}

void MonoSystem::calculateMove()
{
	// ����m_moveingObjects����ȡ���ǵ��ٶ�v�����������ǵ�λ��
	while (!m_moveingObjects.empty())
	{
		// �����ȡ׼���ƶ�������
		MonoObject* obj = m_moveingObjects.front();
		m_moveingObjects.pop();
		// ���㵱ǰ֡λ��
		float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;
		float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;
		// ����ײ�����������˶�λ��
		Utils::Rect address = Utils::Rect{ obj->body.posx + x,obj->body.posy + y ,obj->body.width,obj->body.height };
		
		// ��ȡ�����˶�λ�ô����п��ܻ����������壨�ɴ�Խ���岻���㣩
		vector<MonoObject*> crashObjs = caculateCrash(address);
		MonoObject *crashObj_x= nullptr,*crashObj_y= nullptr;
		// �ֱ��ҵ�x��y�����������ĵ�һ������
		for (int i = 0; i < crashObjs.size(); i++)
		{
			MonoObject* it = crashObjs[i];
			// �ų�����
			if (it->GetHashID() == obj->GetHashID()) continue;
			// x�����������ĵ�һ������
			if (crashObj_x== nullptr ||
				abs(crashObj_x->body.posx - address.posx) < abs(it->body.posx - address.posx))
			{
				crashObj_x = it;
			}
			// y�����������ĵ�һ������
			if (crashObj_y == nullptr ||
				abs(crashObj_y->body.posy - address.posy) < abs(it->body.posy - address.posy))
			{
				crashObj_y = it;
			}
		}
		if (crashObj_x != nullptr)
		{
			// ��ӵ���ײ��λ��key������ײ�ߣ�value������ײ��
			m_crashObjects[make_pair(obj, crashObj_x)] = true;
			// �����ײ�߲��ɴ�Խ�����߾��������ײ
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x,obj)] = true;
		}
		if (crashObj_y != nullptr)
		{
			m_crashObjects[make_pair(obj, crashObj_y)] = true;
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)] = true;
		}
		if (crashObj_x== nullptr && crashObj_y == nullptr)
		{
			// �ı�body��λ��
			Utils::Rect positon = obj->body;
			positon.posx += x;
			positon.posy += y;
			obj->body = positon;
		}
		
	}
	// ִ����ײЧ��
	noticeCrash(); 
}



vector<MonoObject*> MonoSystem::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;
	map<MonoObject*, bool>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// �������в��ܴ�Խ���������ײ���
		if (!it->first->canThrough && Utils::CrossLine(it->first->body, address))
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


void MonoSystem::noticeCrash()
{
	// ���noticeMove�����˲��ɴ�Խ���壬֪ͨ����������ʲô
	map<pair<MonoObject*, MonoObject*>, bool>::iterator it;
	for (it =m_crashObjects.begin(); it != m_crashObjects.end(); it++) {
		it->first.first->onCrash(it->first.second);
	}
	m_crashObjects.clear();

}
