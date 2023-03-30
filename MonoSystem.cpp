#include "MonoSystem.h"
#include "NetWorkSystem.h"

// ���ڿ���ÿ�����֡
clock_t lastFrame = clock();
int frameCnt = 0;

void MonoSystem::onUpdate()
{
	// �̶�ʱ�������һ��,��֤֡ͬ��
	if (clock() - lastFrame > frameCnt * 1000 / Sceneconfig::GetInstance()->MaxFrame)
	{
		Run();
		NetworkSystem::GetInstance()->Run();
		frameCnt++;
		if (frameCnt == Sceneconfig::GetInstance()->MaxFrame)
		{
			frameCnt = 0;
			cout << Sceneconfig::GetInstance()->MaxFrame << "֡����ʱ��" << clock() - lastFrame << endl;
			lastFrame = clock();
		}
		// cout << "��" << frameCnt << "֡:" << clock() << endl;
	}
}

MonoSystem* MonoSystem::GetInstance()
{
	// ����ʽ
	static MonoSystem m_Instance;
	return &m_Instance;
}


void MonoSystem::Run()
{
	// �µ�һ֡��ʼ�����ǰһ֡��������
	m_newObjects.clear();
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
			// �Ӹ��ڵ��Ƴ�����������߸����߼�
			obj->removeFromParent();
			m_activeObjects.erase(obj);
			delete obj;
		}
	}
	// ������������׼��ִ����������Ķ���
	map<MonoObject*, bool>::iterator it; 
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// ִ������֡����
		it->first->onFrameUpdate();
		if (it->first->vx != 0 || it->first->vy != 0) m_moveingObjects.push(it->first);
	}
	// ���������ƶ�
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
		Utils::Rect address = Utils::Rect{ obj->getPosX() + x,obj->getPosY() + y ,
											obj->getSize().width,obj->getSize().height};
		
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
				abs(crashObj_x->getPosX() - address.posx) < abs(it->getPosX() - address.posx))
			{
				crashObj_x = it;
			}
			// y�����������ĵ�һ������
			if (crashObj_y == nullptr ||
				abs(crashObj_y->getPosY() - address.posy) < abs(it->getPosY() - address.posy))
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
		if (obj->canThrough || 
			(crashObj_x== nullptr && crashObj_y == nullptr))
		{
			// �ı�body��λ��
			obj->setPos(address.posx,address.posy) ;
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
	// ���noticeMove�����˲��ɴ�Խ���壬֪ͨ����������ʲô
	map<pair<MonoObject*, MonoObject*>, bool>::iterator it;
	for (it =m_crashObjects.begin(); it != m_crashObjects.end(); it++) {
		it->first.first->onCrash(it->first.second);
	}
	m_crashObjects.clear();

}
