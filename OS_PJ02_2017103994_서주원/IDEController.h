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
	int deviceType; //deviceType, DISK, PRINTER, MONITOR ���...
	queue<task> taskQueue; //task�� ����Ǿ��ִ� queue.
	mutex m; //mutual exclusion�� ����.
public:
	IDEController(int deviceType); //IDEController constructor, deviceType�� �Լ� ���ڷ� ����.
	void assignTask(task newTask); //IDEController�� task�� �Ҵ��ϴ� method.
	void processTask(DMAController& DMA); //task�� process�ϴ� method. task�� process�� ������, �ش� task�� �Լ����ڷ� �޾ƿ� DMA���� transfer.
	void print(); //IDEController�� �Ҵ�Ǿ��ִ� task�� ������ִ� method.
	int size(); //taskQueue�� size�� ��ȯ���ִ� method.
};

#endif // !IDECONTROLLER_H