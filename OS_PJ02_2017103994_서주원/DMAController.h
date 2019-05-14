#ifndef DMACONTROLLER_H
#define DMACONTROLLER_H
#include <iostream>
#include <vector>
#include <mutex>
#include "task.h"

using namespace std;

//class DMAController
class DMAController {
private:
	vector<task> memoryBuffer; //�Ϸ�� task���� ���� �� memeory buffer
	mutex m; //mutual exclusion ����
public:
	void assignTask(task newTask); //�Ϸ�� task�� memoryBuffer�� �����ϴ� method
	void print(); //memoryBuffer�� ����� task���� ����� �ִ� method
};

#endif // !DMACONTROLLER_H