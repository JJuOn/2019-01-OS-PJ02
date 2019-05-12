#ifndef IDECONTROLLER_H
#define IDECONTROLLER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "task.h"
#include "DMAController.h"


using namespace std;

class IDEController {
private:
	int deviceType;
	queue<task> taskQueue;
	mutex m;
	condition_variable condition;
public:
	IDEController(int deviceType);
	void assignTask(task newTask);
	void processTask(DMAController& DMA);
	void print();
	int size();
};

#endif // !IDECONTROLLER_H