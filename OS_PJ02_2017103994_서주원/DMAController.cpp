#include <iostream>
#include <mutex>
#include <string>
#include "DMAController.h"
#include "task.h"

using namespace std;

//task 출력 시, task의 type을 string으로 변환해 주는 함수.
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

//완료된 task를 memoryBuffer에 저장하는 method
void DMAController::assignTask(task newTask) {
	//mutual exclusion 보장.
	lock_guard<mutex> lock(m);
	//memoryBuffer의 마지막에 완료된 task 삽입.
	memoryBuffer.push_back(newTask);
}

//memoryBuffer에 저장된 task들을 출력해 주는 method
void DMAController::print() {
	//모든 task의 처리가 끝났다고 알린다.
	cout << "All tasks are done.\nMemoryBuffer\n";
	//memoryBuffer의 크기
	int size = memoryBuffer.size();
	//memoryBuffer에 저장된 task들에 대하여 출력
	for (int i = 0; i < size; i++) {
		cout << "[PROCESSED]PID: " << memoryBuffer[i].pid << "\tTYPE: " << typeToString2(memoryBuffer[i].type) << endl;
	}
	//처음 입력한 task의 갯수와 처리 된 task의 갯수가 같은지 확인.
	cout << "Size of MemoryBuffer : " << memoryBuffer.size() << endl;
}