#include<iostream>
#include<ctime>
#include<Windows.h>
#include<cstdio>
#include<ctime>
#define ITERNUM 6250000
using namespace std;

int acc = 0;
DWORD addr;
HANDLE hd_th1, hd_th2, hd_th3, hd_th4,
	   hd_th5, hd_th6, hd_th7, hd_th8;

DWORD WINAPI Bignumber(LPVOID lpVoid) {
	for (int i = 0; i < ITERNUM; i++) acc += 2;
	return 0;
}

void createThread(HANDLE &hd_th) {
	hd_th = CreateThread(NULL, 0, Bignumber, NULL, 0, &addr);	
}

void waitThread(HANDLE &hd_th) {
	WaitForSingleObject(hd_th, INFINITE);
	CloseHandle(hd_th);
}

int main() {
	clock_t avg = 0;
	long long int bignum_avg = 0;
	for (int i = 0; i < 100; i++) {
		acc = 0;
		clock_t start = clock();
		createThread(hd_th1);
		createThread(hd_th2);
		createThread(hd_th3);
		createThread(hd_th4);
		createThread(hd_th5);
		createThread(hd_th6);
		createThread(hd_th7);
		createThread(hd_th8);
		waitThread(hd_th1);
		waitThread(hd_th2);
		waitThread(hd_th3);
		waitThread(hd_th4);
		waitThread(hd_th5);
		waitThread(hd_th6);
		waitThread(hd_th7);
		waitThread(hd_th8);
		clock_t end = clock();
		avg += (end - start);
		bignum_avg += acc;
		if ((i + 1) % 10 == 0) printf("%d%% ¿Ï·á\n",i+1);
	}
	avg /= 100;
	bignum_avg /= 100;
	printf("Æò±ÕBignum : %lld, Æò±Õ½Ã°£ : %dms\n",bignum_avg,avg);
}
