#include <thread>
#include <iostream>
#include <ctime>
#include "IDEController.h"
#include "DMAController.h"
#include "task.h"

using namespace std;

//task�� device�� type�� ��Ÿ���� ������
enum types { DISK, PRINTER, MONITOR, MOUSE, KEYBOARD };

//main()
int main() {
	//device type���� IDEController�� ��ü ����
	IDEController diskController(DISK), printerController(PRINTER), monitorController(MONITOR), mouseController(MOUSE), keyboardController(KEYBOARD);
	//DMAController DMA ����
	DMAController DMA;
	//task�� ����
	int taskNum;
	//rand()�� ���� ����
	srand(time(NULL));
	//task�� ���� �Է�
	cout << "Enter the number of tasks : ";
	cin >> taskNum;
	//task�� ������ 500�� �̻��̾�� �ϹǷ�, 500���� ���� ���� �ԷµǾ��� ��� ��Ȯ��
	while (taskNum < 500) {
		cout << "Too little number!\nEnter the number of tasks : ";
		cin >> taskNum;
	}
	//task ������ŭ�� ũ�⸦ ���� taskArr ���� �Ҵ�
	task* taskArr = new task[taskNum];
	//������ ��� task �ʱ�ȭ
	for (int i = 0; i < taskNum; i++) {
		//task�� pid�� 1���� ������� ����
		taskArr[i].pid = i + 1;
		//task�� type�� 0~4�� ���������� ����
		taskArr[i].type = rand() % 5;
		//���� task�� type�� disk�� ��� diskController�� �Ҵ�
		if (taskArr[i].type == DISK) {
			diskController.assignTask(taskArr[i]);
		}
		//���� task�� type�� printer�� ��� printerController�� �Ҵ�
		else if (taskArr[i].type == PRINTER) {
			printerController.assignTask(taskArr[i]);
		}
		//���� task�� type�� monitor�� ��� monitorController�� �Ҵ�
		else if (taskArr[i].type == MONITOR) {
			monitorController.assignTask(taskArr[i]);
		}
		//���� task�� type�� mouse�� ��� mouseController�� �Ҵ�
		else if (taskArr[i].type == MOUSE) {
			mouseController.assignTask(taskArr[i]);
		}
		//���� task�� type�� keyboard�� ��� keyboardController�� �Ҵ�
		else if (taskArr[i].type == KEYBOARD) {
			keyboardController.assignTask(taskArr[i]);
		}
	}
	//IDEController���� �Ҵ�� task ���
	diskController.print();
	printerController.print();
	monitorController.print();
	mouseController.print();
	keyboardController.print();
	//�Ҵ�� task���� ó���ϱ� ���� thread ����
	thread diskThread(&IDEController::processTask, &diskController, ref(DMA));
	thread printerThread(&IDEController::processTask, &printerController, ref(DMA));
	thread monitorThread(&IDEController::processTask, &monitorController, ref(DMA));
	thread mouseThread(&IDEController::processTask, &mouseController, ref(DMA));
	thread keyboardThread(&IDEController::processTask, &keyboardController, ref(DMA));
	//thread���� ����Ǳ⸦ ��ٸ�
	diskThread.join();
	printerThread.join();
	monitorThread.join();
	mouseThread.join();
	keyboardThread.join();
	//thread�� ��� ����Ǹ� DMAController�� memoryBuffer�� ���
	DMA.print();
	return 0;
}