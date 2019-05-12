#pragma once
#include <iostream>
#include <Windows.h>
#include <mutex>
#include <string>
#include <sstream>
#include "IDEController.h"
#include "DMAController.h"

using namespace std;

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

IDEController::IDEController(int deviceType) {
	this->deviceType = deviceType;
}

void IDEController::assignTask(task newTask) {
	taskQueue.push(newTask);
}

void IDEController::processTask(DMAController& DMA) {
	task frontTask;
	unique_lock<mutex> unique(m);
	while (!taskQueue.empty()) {
		frontTask = taskQueue.front();
		DMA.assignTask(frontTask);
		stringstream output;
		output << "[PROCESSING]PID: " << frontTask.pid << "\tTYPE: " << typeToString1(frontTask.type) << '\n';
		cout << output.str();
		taskQueue.pop();
	}
}

void IDEController::print() {
	queue<task> temp(taskQueue);
	while (!temp.empty()) {
		cout << "[ASSIGNED]PID: " << temp.front().pid << "\tTYPE: " << typeToString1(temp.front().type) << '\n';
		temp.pop();
	}
}

int IDEController::size() {
	return taskQueue.size();
}
