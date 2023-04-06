#include "templateSystem.h"
#include <fstream>
#include "MonoSystem.h"


templateSystem* templateSystem::GetInstance()
{
	// 饿汉式
	static templateSystem m_Instance;
	return &m_Instance;
}

void templateSystem::Run()
{
	// 判断新增物体是不是templateObject并添加到自身数组
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getNewObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		templateObject* obj = dynamic_cast<templateObject*>(objs[i]);
		if (obj) templateObjects.push_back(obj);
	}
}

bool templateSystem::Init()
{
    std::vector<std::vector<std::string>> data;  // 用于存储CSV数据
    std::ifstream file("./测试表格.csv");  // 打开CSV文件
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {  // 逐行读取CSV文件
        std::vector<std::string> row;
        size_t pos = 0;
        while ((pos = line.find(',')) != std::string::npos) {  // 分割每一行
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        row.push_back(line);  // 最后一个元素没有逗号
        data.push_back(row);
    }

    file.close();  // 关闭CSV文件

    // 遍历读取的数据并打印出来
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