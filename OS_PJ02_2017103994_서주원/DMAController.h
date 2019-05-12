#ifndef DMACONTROLLER_H
#define DMACONTROLLER_H
#include <iostream>
#include <vector>
#include <mutex>
#include "task.h"


using namespace std;

class DMAController {
private:
	vector<task> memoryBuffer;
	mutex m;
public:
	void assignTask(task newTask);
	void print();
};

#endif // !DMACONTROLLER_H