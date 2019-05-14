#pragma once
//struct task
struct task
{
	int pid; //task 고유의 id값
	int type; //task의 타입, DISK(0),PRINTER(1),MONITOR(2),MOUSE(3),KEYBOARD(4)의 값을 가짐.
};