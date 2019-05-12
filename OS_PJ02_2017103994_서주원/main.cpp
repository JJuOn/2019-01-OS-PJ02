#include <thread>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include "IDEController.h"
#include "DMAController.h"
#include "task.h"

using namespace std;

enum types { DISK, PRINTER, MONITOR, MOUSE, KEYBOARD };

int main() {
	IDEController diskController(DISK), printerController(PRINTER), monitorController(MONITOR), mouseController(MOUSE), keyboardController(KEYBOARD);
	DMAController DMA;
	int taskNum,diskSize=0,printerSize=0,monitorSize=0,mouseSize=0,keyboardSize=0;
	srand(time(NULL));
	cout << "Enter the number of tasks : ";
	cin >> taskNum;
	while (taskNum < 500) {
		cout << "Too little number!\nEnter the number of tasks : ";
		cin >> taskNum;
	}
	task* taskArr = new task[taskNum];
	thread* threads = new thread[taskNum];
	for (int i = 0; i < taskNum; i++) {
		taskArr[i].pid = i + 1;
		taskArr[i].type = rand() % 5;
		if (taskArr[i].type == 0) {
			diskController.assignTask(taskArr[i]);
			diskSize++;
		}
		else if (taskArr[i].type == 1) {
			printerController.assignTask(taskArr[i]);
			printerSize++;
		}
		else if (taskArr[i].type == 2) {
			monitorController.assignTask(taskArr[i]);
			monitorSize++;
		}
		else if (taskArr[i].type == 3) {
			mouseController.assignTask(taskArr[i]);
			mouseSize++;
		}
		else if (taskArr[i].type == 4) {
			keyboardController.assignTask(taskArr[i]);
			keyboardSize++;
		}
	}
	diskController.print();
	printerController.print();
	monitorController.print();
	mouseController.print();
	keyboardController.print();
	thread diskThread(&IDEController::processTask, &diskController, ref(DMA));
	thread printerThread(&IDEController::processTask, &printerController, ref(DMA));
	thread monitorThread(&IDEController::processTask, &monitorController, ref(DMA));
	thread mouseThread(&IDEController::processTask, &mouseController, ref(DMA));
	thread keyboardThread(&IDEController::processTask, &keyboardController, ref(DMA));
	diskThread.join();
	printerThread.join();
	monitorThread.join();
	mouseThread.join();
	keyboardThread.join();
	DMA.print();
	//system("pause");
	return 0;
}