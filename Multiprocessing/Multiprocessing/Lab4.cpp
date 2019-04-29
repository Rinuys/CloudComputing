#include<iostream>
#include<ctime>
#include<cstdio>
#include<Windows.h>

using namespace std;

volatile bool flag;
int token;

int acc = 0;

DWORD addr;
HANDLE hd_th1, hd_th2;

DWORD WINAPI hd_th1_(LPVOID lpVoid) {
	printf("thread1 진입\n");
	int get_token;
	printf("thread1 대기\n");
	while (flag != true);
	get_token = token;
	printf("get_token = %d\n",get_token);
	printf("thread1 끝\n");
	return 0;
}
DWORD WINAPI hd_th2_(LPVOID lpVoid) {
	printf("thread2 진입\n");
	token = 123;
	printf("token = %d\n",token);
	flag = true;
	printf("thread2 끝\n");
	return 0;
}

void createThread1(HANDLE &hd_th, int affinity) {
	hd_th = CreateThread(NULL, 0, hd_th1_, (void*)affinity, 0, &addr);
}

void createThread2(HANDLE &hd_th, int affinity) {
	hd_th = CreateThread(NULL, 0, hd_th2_, (void*)affinity, 0, &addr);
}

void waitThread(HANDLE &hd_th) {
	WaitForSingleObject(hd_th, INFINITE);
	CloseHandle(hd_th);
}

int main() {
	
	flag = false;
	
	for (int i = 0; i < 10000; i++) {
		createThread1(hd_th1, 1);
		createThread2(hd_th2, 4);
		waitThread(hd_th1);
		waitThread(hd_th2);
	}
	cout << "-----------프로그램 끝-----------" << endl;
	
	getchar();
}
