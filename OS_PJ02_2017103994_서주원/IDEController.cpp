#pragma once
#include <iostream>
#include <Windows.h>
#include <mutex>
#include <string>
#include <sstream>
#include "IDEController.h"
#include "DMAController.h"

using namespace std;

//task ��� ��, task�� type�� string���� ��ȯ�� �ִ� �Լ�.
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

//IDEController constructor. deciveType�� �Լ� ���ڷ� �޾�, �ش� ��ü�� deviceType�� ������.
IDEController::IDEController(int deviceType) {
	this->deviceType = deviceType;
}

//task�� assign�ϴ� method.
void IDEController::assignTask(task newTask) {
	//�ܼ�â�� ���
	cout << "[ASSIGNING]PID: " << newTask.pid << "\tTYPE: " << typeToString1(newTask.type) << '\n';
	//tashQueue�� newTask ����.
	taskQueue.push(newTask);
}

//task�� process�ϰ� DMA�� transfer.
void IDEController::processTask(DMAController& DMA) {
	//taskQueue�� ù��° task�� frontTask ����.
	task frontTask;
	//mutual exclusion ����.
	lock_guard<mutex> lock(m);
	//taskQueue�� ó���� task�� ���� ��,
	while (!taskQueue.empty()) {
		//taskQueue�� ù��° task ��������.
		frontTask = taskQueue.front();
		//�ܼ� ����� ���� stringstream output ����.
		stringstream output;
		//output�� ����� ���� �Է�.
		output << "[PROCESSING]PID: " << frontTask.pid << "\tTYPE: " << typeToString1(frontTask.type) << '\n';
		cout << output.str();
		//DMAController�� ó���� �Ϸ��� task�� �����Ѵ�.
		DMA.assignTask(frontTask);
		//ó�� �Ϸ��� task�� taskQueue���� �����Ѵ�.
		taskQueue.pop();
	}
}

void IDEController::print() {
	//taskQueue ����ϱ� ���� tempQueue ����
	queue<task> temp(taskQueue);
	//tempQueue�� �� �� ����
	while (!temp.empty()) {
		//�Ҵ�� task ���
		cout << "[ASSIGNED]PID: " << temp.front().pid << "\tTYPE: " << typeToString1(temp.front().type) << '\n';
		//���� task ����� ���� tempQueue�� ���� ù��° �������� �����Ѵ�.
		temp.pop();
	}
}

//taskQueue�� size�� ��ȯ�� �ִ� method.
int IDEController::size() {
	return taskQueue.size();
}
