#include <thread>
#include <iostream>
#include <ctime>
#include "IDEController.h"
#include "DMAController.h"
#include "task.h"

using namespace std;

//task와 device의 type을 나타내는 열거형
enum types { DISK, PRINTER, MONITOR, MOUSE, KEYBOARD };

//main()
int main() {
	//device type별로 IDEController의 객체 생성
	IDEController diskController(DISK), printerController(PRINTER), monitorController(MONITOR), mouseController(MOUSE), keyboardController(KEYBOARD);
	//DMAController DMA 생성
	DMAController DMA;
	//task의 갯수
	int taskNum;
	//rand()를 위한 세팅
	srand(time(NULL));
	//task의 갯수 입력
	cout << "Enter the number of tasks : ";
	cin >> taskNum;
	//task의 갯수는 500개 이상이어야 하므로, 500보다 작은 값이 입력되었을 경우 재확인
	while (taskNum < 500) {
		cout << "Too little number!\nEnter the number of tasks : ";
		cin >> taskNum;
	}
	//task 갯수만큼의 크기를 갖는 taskArr 동적 할당
	task* taskArr = new task[taskNum];
	//생성한 모든 task 초기화
	for (int i = 0; i < taskNum; i++) {
		//task의 pid는 1부터 순서대로 지정
		taskArr[i].pid = i + 1;
		//task의 type을 0~4의 랜덤값으로 지정
		taskArr[i].type = rand() % 5;
		//현재 task의 type이 disk인 경우 diskController에 할당
		if (taskArr[i].type == DISK) {
			diskController.assignTask(taskArr[i]);
		}
		//현재 task의 type이 printer인 경우 printerController에 할당
		else if (taskArr[i].type == PRINTER) {
			printerController.assignTask(taskArr[i]);
		}
		//현재 task의 type이 monitor인 경우 monitorController에 할당
		else if (taskArr[i].type == MONITOR) {
			monitorController.assignTask(taskArr[i]);
		}
		//현재 task의 type이 mouse인 경우 mouseController에 할당
		else if (taskArr[i].type == MOUSE) {
			mouseController.assignTask(taskArr[i]);
		}
		//현재 task의 type이 keyboard인 경우 keyboardController에 할당
		else if (taskArr[i].type == KEYBOARD) {
			keyboardController.assignTask(taskArr[i]);
		}
	}
	//IDEController별로 할당된 task 출력
	diskController.print();
	printerController.print();
	monitorController.print();
	mouseController.print();
	keyboardController.print();
	//할당된 task들을 처리하기 위한 thread 생성
	thread diskThread(&IDEController::processTask, &diskController, ref(DMA));
	thread printerThread(&IDEController::processTask, &printerController, ref(DMA));
	thread monitorThread(&IDEController::processTask, &monitorController, ref(DMA));
	thread mouseThread(&IDEController::processTask, &mouseController, ref(DMA));
	thread keyboardThread(&IDEController::processTask, &keyboardController, ref(DMA));
	//thread들이 종료되기를 기다림
	diskThread.join();
	printerThread.join();
	monitorThread.join();
	mouseThread.join();
	keyboardThread.join();
	//thread가 모두 종료되면 DMAController의 memoryBuffer를 출력
	DMA.print();
	return 0;
}