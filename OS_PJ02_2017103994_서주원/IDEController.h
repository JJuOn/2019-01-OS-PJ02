#ifndef IDECONTROLLER_H
#define IDECONTROLLER_H

#include <queue>
#include <mutex>
#include "task.h"
#include "DMAController.h"


using namespace std;

//class IDEController
class IDEController {
private:
	int deviceType; //deviceType, DISK, PRINTER, MONITOR 등등...
	queue<task> taskQueue; //task가 저장되어있는 queue.
	mutex m; //mutual exclusion을 보장.
public:
	IDEController(int deviceType); //IDEController constructor, deviceType을 함수 인자로 받음.
	void assignTask(task newTask); //IDEController에 task를 할당하는 method.
	void processTask(DMAController& DMA); //task를 process하는 method. task의 process가 끝나면, 해당 task를 함수인자로 받아온 DMA에게 transfer.
	void print(); //IDEController의 할당되어있는 task를 출력해주는 method.
	int size(); //taskQueue의 size를 반환해주는 method.
};

#endif // !IDECONTROLLER_H