#include <iostream>
#include <mutex>
#include <string>
#include "DMAController.h"
#include "task.h"

using namespace std;

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

void DMAController::assignTask(task newTask) {
	m.lock();
	memoryBuffer.push_back(newTask);
	m.unlock();
}

void DMAController::print() {
	cout << "MemoryBuffer\n";
	int size = memoryBuffer.size();
	for (int i = 0; i < size; i++) {
		cout << "[PROCESSED]PID: " << memoryBuffer[i].pid << "\tTYPE: " << typeToString2(memoryBuffer[i].type) << endl;
	}
	cout << "Size of MemoryBuffer : " << memoryBuffer.size() << endl;
}