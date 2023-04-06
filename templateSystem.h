#pragma once
#include <vector>
#include "templateObject.h"
using namespace std;

class templateSystem
{
public:
	static templateSystem* GetInstance();
	void Run();
	bool Init();
	~templateSystem();
private:
	templateSystem() = default;
	// 存储所有物体
	vector<templateObject*> templateObjects;
};

