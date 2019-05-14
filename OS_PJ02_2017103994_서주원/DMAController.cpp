#include <iostream>
#include <mutex>
#include <string>
#include "DMAController.h"
#include "task.h"

using namespace std;

//task ��� ��, task�� type�� string���� ��ȯ�� �ִ� �Լ�.
string typeToString2(int type) {
	switch (type) {
	case 0:
		return "DISK";
	case 1:
		return "PRINTER";
	case 2:
		return "MONITOR";
	case 3:
		return "MOUSE";
	case 4:
		return "KEYBOARD";
	default:
		return "";
	}
}

//�Ϸ�� task�� memoryBuffer�� �����ϴ� method
void DMAController::assignTask(task newTask) {
	//mutual exclusion ����.
	lock_guard<mutex> lock(m);
	//memoryBuffer�� �������� �Ϸ�� task ����.
	memoryBuffer.push_back(newTask);
}

//memoryBuffer�� ����� task���� ����� �ִ� method
void DMAController::print() {
	//��� task�� ó���� �����ٰ� �˸���.
	cout << "All tasks are done.\nMemoryBuffer\n";
	//memoryBuffer�� ũ��
	int size = memoryBuffer.size();
	//memoryBuffer�� ����� task�鿡 ���Ͽ� ���
	for (int i = 0; i < size; i++) {
		cout << "[PROCESSED]PID: " << memoryBuffer[i].pid << "\tTYPE: " << typeToString2(memoryBuffer[i].type) << endl;
	}
	//ó�� �Է��� task�� ������ ó�� �� task�� ������ ������ Ȯ��.
	cout << "Size of MemoryBuffer : " << memoryBuffer.size() << endl;
}