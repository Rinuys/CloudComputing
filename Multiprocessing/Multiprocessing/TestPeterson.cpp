#include<iostream>
#include<ctime>
#include<cstdio>
#include<Windows.h>
/*
#define _ITERNUM 25000000LL
#define AVGITER 10

using namespace std;

bool flag[2];
int turn;

int acc = 0;

DWORD addr;
HANDLE hd_th1, hd_th2, hd_th3, hd_th4,
hd_th5, hd_th6, hd_th7, hd_th8,
hd_th9, hd_th10, hd_th11, hd_th12;

DWORD WINAPI Bignumber(LPVOID lpVoid) {
	SetThreadAffinityMask(GetCurrentThread(), (int)lpVoid);
	if ((int)lpVoid == 1) {
		flag[0] = true;
		turn = 1;
		while (flag[1] && turn == 1) ;
	}
	else {
		flag[1] = true;
		turn = 0;
		while (flag[0] && turn == 0) ;
	}
	for (long long int i = 0; i < _ITERNUM; i++) acc += 2;
	if ((int)lpVoid == 1) flag[0] = false;
	else flag[1] = false;
	return 0;
}

void createThread(HANDLE &hd_th, int affinity) {
	hd_th = CreateThread(NULL, 0, Bignumber, (void*)affinity, 0, &addr);
}

void waitThread(HANDLE &hd_th) {
	WaitForSingleObject(hd_th, INFINITE);
	CloseHandle(hd_th);
}

int main() {
	clock_t avg = 0;
	flag[0] = false;
	flag[1] = true;
	turn = 0;
	long long int bignum_avg = 0;
	for (int i = 0; i < AVGITER; i++) {
		acc = 0;
		DWORD start = GetTickCount();
		createThread(hd_th1, 1);
		createThread(hd_th2, 4);
		//createThread(hd_th3, 2);
		//createThread(hd_th4, 8);
		//createThread(hd_th5, 1);
		//createThread(hd_th6, 4);
		//createThread(hd_th7, 2);
		//createThread(hd_th8, 8);
		createThread(hd_th9, 32);
		createThread(hd_th10, 128);
		createThread(hd_th11, 512);
		createThread(hd_th12, 2048);
		waitThread(hd_th1);
		waitThread(hd_th2);
		//waitThread(hd_th3);
		//waitThread(hd_th4);
		//waitThread(hd_th5);
		//waitThread(hd_th6);
		//waitThread(hd_th7);
		//waitThread(hd_th8);
		waitThread(hd_th9);
		waitThread(hd_th10);
		waitThread(hd_th11);
		waitThread(hd_th12);
		DWORD end = GetTickCount();
		avg += ((int)end - (int)start);
		bignum_avg += acc;
		printf("Bignum : %d, ½Ã°£ : %dms\n", acc, ((int)end - (int)start));
		printf("%d%% ¿Ï·á\n", (i + 1) * 10);
	}
	avg /= AVGITER;
	bignum_avg /= AVGITER;
	printf("Æò±ÕBignum : %lld, Æò±Õ½Ã°£ : %dms\n", bignum_avg, avg);
}
*/