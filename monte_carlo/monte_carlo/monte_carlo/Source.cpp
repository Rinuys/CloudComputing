#include<iostream>
#include<cstdlib>
#include<ctime>

#define MAXLOOP 100000

using namespace std;

int main() {
	srand((unsigned int)time(0));
	double a, b;
	int count = 0;
	int line = 0;
	double *result = (double*)malloc(sizeof(double) * MAXLOOP);
	printf("Calculating...\n");
	for (int i = 0; i < MAXLOOP; i++) {
		a = (double)rand() / RAND_MAX;
		b = (double)rand() / RAND_MAX;
		if (a * a + b * b <= 1.0) count++;
		result[i] = count / (double)i * 4.0;
		if (result[i] >= 3.1415 && result[i] < 3.1416) {
			printf("%d ", i);
			line++;
			if (line % 10 == 0) printf("\n");
		}
	}
	return 0;
}