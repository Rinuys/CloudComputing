#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<thread>

#define THREAD_SIZE 4							// �������� ����
#define NUMBEROFDATA 100000000					// ���ڿ��� ����
#define NUMBEROFCHARS 10						// ������ ����
#define MAXSTACKSIZE 100000						// Stack�� �ִ� ũ��
#define WORDSIZE 11								// Word�� ũ��(������ ���� + 1)
#define THRESHOLD 30							// ���������� ������ ������ ������ ��谪

using namespace std;

typedef struct word {
	char ch[NUMBEROFCHARS];
	char temp;
};

typedef struct stack {
	int arr[MAXSTACKSIZE];
	int top=0;
};

char inputfile[20] = "input.txt";
char outputfile[20] = "output.txt";
char *st;

int start_value[THREAD_SIZE];
int end_value[THREAD_SIZE];

thread sort_pool[THREAD_SIZE];
thread merge_pool[THREAD_SIZE];
int merge_pool_cnt;

void saveData() {
	FILE *fp = fopen(outputfile, "w+");
	fwrite(st, sizeof(char), NUMBEROFDATA*WORDSIZE, fp);
	fprintf(fp, "\n");
	fclose(fp);
}

void loadData() {
	FILE *fp = fopen(inputfile, "r");
	fread(st, sizeof(char), NUMBEROFDATA * WORDSIZE + 1, fp);
	fclose(fp);
}

void printData(int num) {
	for (int i = 0; i < num; i++) {
		char temp[WORDSIZE];
		memcpy(temp, st + WORDSIZE*i, NUMBEROFCHARS);
		temp[NUMBEROFCHARS] = '\0';
		printf("%s\n",temp);
	}
}

bool cmp(int index1, int index2) {
	// st[index1] <= st[index2] : true
	// st[index1] > st[index2] : false
	for (int i = 0; i < NUMBEROFCHARS; i++) {
		if (st[index1 + i] == st[index2 + i]) continue;
		else if (st[index1 + i] < st[index2 + i]) return true;
		else return false;
	}
	return true;
}

bool cmp(int index1, char *_st) {
	// st[index1] <= _st : true
	// st[index1] > _st : false
	for (int i = 0; i < NUMBEROFCHARS; i++) {
		if (st[index1 + i] == _st[i]) continue;
		else if (st[index1 + i] < _st[i]) return true;
		else return false;
	}
	return true;
}

bool cmp(char *_st1, int index2) {
	// _st1 <= st[index2] : true
	// _st1 > st[index2] : false
	for (int i = 0; i < NUMBEROFCHARS; i++) {
		if (_st1[i] == st[index2 + i]) continue;
		else if (_st1[i] < st[index2 + i]) return true;
		else return false;
	}
	return true;
}

void _swap(int index1, int index2) {
	char ch[WORDSIZE];
	memcpy(ch, st + index1, NUMBEROFCHARS);
	memcpy(st + index1, st + index2, NUMBEROFCHARS);
	memcpy(st + index2, ch, NUMBEROFCHARS);
}

void small_sort(int start, int end) {
	int i, j;
	char t[WORDSIZE];
	t[NUMBEROFCHARS] = '\0';
	for (i = start + WORDSIZE; i <= end; i+=WORDSIZE) {
		memcpy(t,st+i,NUMBEROFCHARS);
		for (j = i - WORDSIZE; j >= start && !cmp(j,t) ; j-=WORDSIZE) 
			memcpy(st + j + WORDSIZE, st + j, NUMBEROFCHARS);
		memcpy(st + j + WORDSIZE, t, NUMBEROFCHARS);
	}
}

void push(stack &k, int val) {
	k.arr[k.top++] = val;
}

int pop(stack &k) {
	return k.arr[--k.top];
}

void quick_sort(int start, int end) {
	stack start_stack;
	stack end_stack;

	push(start_stack, start);
	push(end_stack, end);

	while (start_stack.top != 0) {
		start = pop(start_stack);
		end = pop(end_stack);

		if (start >= end) continue;		// ���Ұ� 1���� ���

		// ���Ұ� Threshold �� ������ ��� ��������
		if (end - start <= THRESHOLD * WORDSIZE) {
			small_sort(start, end);
			continue;
		}

		int pivot = start;
		int i = pivot + WORDSIZE;		// ���� ��� ���� 
		int j = end;					// ������ ��� ����
		int temp;

		while (i <= j) {				// �����Ͱ� ������������ �ݺ�
			while (i <= end && cmp(i, pivot)) i += WORDSIZE;
			while (j > start && cmp(pivot, j)) j -= WORDSIZE;
			if (i > j) _swap(j, pivot); // ������
			else _swap(i, j);			// i��°�� j��°�� ����
		}

		// ����
		push(start_stack, j + WORDSIZE);
		push(end_stack, end);
		push(start_stack, start);
		push(end_stack, j - WORDSIZE);
	}
}

void merge(int s1, int e1, int s2, int e2) {
	int start1 = start_value[s1], end1 = end_value[e1]
		, start2 = start_value[s2], end2 = end_value[e2];
	char *buff = (char*)malloc(sizeof(char)*(end2 - start1 + WORDSIZE));
	int buff_cnt = 0;
	int left = start1;
	int right = start2;
	while (left != start2 && right != end2 + WORDSIZE) {
		if (cmp(left, right)) {
			memcpy(buff + buff_cnt, st + left, NUMBEROFCHARS);
			left += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
		else {
			memcpy(buff + buff_cnt, st + right, NUMBEROFCHARS);
			right += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
	}
	if (left == start2) {
		while (right != end2 + WORDSIZE) {
			memcpy(buff + buff_cnt, st + right, NUMBEROFCHARS);
			right += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
	}
	else if (right == end2 + WORDSIZE) {
		while (left != start2) {
			memcpy(buff + buff_cnt, st + left, NUMBEROFCHARS);
			left += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
	}
	for (int i = 0; i < buff_cnt - WORDSIZE; i+=WORDSIZE) 
		memcpy(st + start1 + i, buff + i, NUMBEROFCHARS);
	free(buff);
}

int main() {
	st = (char*)malloc(sizeof(char) * ((NUMBEROFDATA * 11) + 1));
	
	int diff = NUMBEROFDATA / THREAD_SIZE;

	time_t start = clock();
	// Load
	printf("Loading Data...\n");
	loadData();
	printData(5);

	// QuickSort
	printf("Sorting Data...\n");
	int s, e;
	for (int i = 0; i < THREAD_SIZE; i++) {
		s = i * diff * WORDSIZE;
		e = (i + 1) * diff * WORDSIZE - WORDSIZE;
		start_value[i] = s;
		end_value[i] = e;
		sort_pool[i] = thread(quick_sort, s, e);
	}
	for (int i = 0; i < THREAD_SIZE; i++) sort_pool[i].join();

	// Merge(Ȧ�����϶� �� ����)
	printf("Merging Data...\n");
	int mul = 2;
	int mul1 = 1;
	while (THREAD_SIZE / mul1 != 1) {
		int i;
		for (i = 0; i < THREAD_SIZE; i += mul) {
			if (i + mul1 != THREAD_SIZE) {
				merge_pool[merge_pool_cnt++] = thread(merge, i, i, i + mul1, i + mul1);
				merge(i, i, i + mul1, i + mul1);
				end_value[i] = end_value[i + mul1];
			}
			else break;
		}
		for (int j = 0; j < merge_pool_cnt; j++) {
			merge_pool[j].join();
		}
		merge_pool_cnt = 0;

		// Ȧ�����϶�
		/*if ((THREAD_SIZE / mul) % 2 == 1) {
			merge(start_value[i - mul], end_value[i - mul], start_value[i], end_value[i]);
		}*/

		mul1 *= 2;
		mul *= 2;
	}
	printData(5);

	// save
	printf("Saving Data...\n");
	saveData();
	time_t end = clock();
	printf("time : %dms\n", (int)(end - start));
	
	return 0;
}