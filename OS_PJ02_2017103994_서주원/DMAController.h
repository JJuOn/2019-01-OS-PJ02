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
	vector<task> memoryBuffer; //완료된 task들이 저장 될 memeory buffer
	mutex m; //mutual exclusion 보장
public:
	void assignTask(task newTask); //완료된 task를 memoryBuffer에 저장하는 method
	void print(); //memoryBuffer에 저장된 task들을 출력해 주는 method
};

#endif // !DMACONTROLLER_H