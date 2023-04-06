#include "templateSystem.h"
#include <fstream>
#include "MonoSystem.h"

templateSystem* templateSystem::GetInstance()
{
	// ����ʽ
	static templateSystem m_Instance;
	return &m_Instance;
}

void templateSystem::Run()
{
	// �ж����������ǲ���templateObject����ӵ���������
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getNewObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		templateObject* obj = dynamic_cast<templateObject*>(objs[i]);
		if (obj) templateObjects.push_back(obj);
	}
}

bool templateSystem::Init()
{
    std::vector<std::vector<std::string>> data;  // ���ڴ洢CSV����
    std::ifstream file("./���Ա��.csv");  // ��CSV�ļ�
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {  // ���ж�ȡCSV�ļ�
        std::vector<std::string> row;
        size_t pos = 0;
        while ((pos = line.find(',')) != std::string::npos) {  // �ָ�ÿһ��
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        row.push_back(line);  // ���һ��Ԫ��û�ж���
        data.push_back(row);
    }

    file.close();  // �ر�CSV�ļ�

    // ������ȡ�����ݲ���ӡ����
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

	return true;
}

templateSystem::~templateSystem()
{
}