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
	// �洢��������
	vector<templateObject*> templateObjects;
};

