#pragma once
#include <iostream>
#include <Windows.h>
#include <mutex>
#include <string>
#include <sstream>
#include "IDEController.h"
#include "DMAController.h"

using namespace std;

//task 출력 시, task의 type을 string으로 변환해 주는 함수.
string typeToString1(int type) {
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

//IDEController constructor. deciveType을 함수 인자로 받아, 해당 객체의 deviceType을 지정함.
IDEController::IDEController(int deviceType) {
	this->deviceType = deviceType;
}

//task를 assign하는 method.
void IDEController::assignTask(task newTask) {
	//콘솔창에 출력
	cout << "[ASSIGNING]PID: " << newTask.pid << "\tTYPE: " << typeToString1(newTask.type) << '\n';
	//tashQueue에 newTask 삽입.
	taskQueue.push(newTask);
}

//task를 process하고 DMA에 transfer.
void IDEController::processTask(DMAController& DMA) {
	//taskQueue의 첫번째 task인 frontTask 선언.
	task frontTask;
	//mutual exclusion 보장.
	lock_guard<mutex> lock(m);
	//taskQueue에 처리할 task가 있을 때,
	while (!taskQueue.empty()) {
		//taskQueue의 첫번째 task 가져오기.
		frontTask = taskQueue.front();
		//콘솔 출력을 위한 stringstream output 선언.
		stringstream output;
		//output에 출력할 내용 입력.
		output << "[PROCESSING]PID: " << frontTask.pid << "\tTYPE: " << typeToString1(frontTask.type) << '\n';
		cout << output.str();
		//DMAController에 처리를 완료한 task를 전달한다.
		DMA.assignTask(frontTask);
		//처리 완료한 task를 taskQueue에서 제거한다.
		taskQueue.pop();
	}
}

void IDEController::print() {
	//taskQueue 출력하기 위한 tempQueue 생성
	queue<task> temp(taskQueue);
	//tempQueue가 빌 때 까지
	while (!temp.empty()) {
		//할당된 task 출력
		cout << "[ASSIGNED]PID: " << temp.front().pid << "\tTYPE: " << typeToString1(temp.front().type) << '\n';
		//다음 task 출력을 위해 tempQueue의 가장 첫번째 아이템을 제거한다.
		temp.pop();
	}
}

//taskQueue의 size를 반환해 주는 method.
int IDEController::size() {
	return taskQueue.size();
}
