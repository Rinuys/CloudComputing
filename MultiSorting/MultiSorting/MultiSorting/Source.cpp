#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<thread>

#define THREAD_SIZE 4							// 쓰레드의 개수
#define NUMBEROFDATA 100000000					// 문자열의 개수
#define NUMBEROFCHARS 10						// 문자의 개수
#define MAXSTACKSIZE 100000						// Stack의 최대 크기
#define WORDSIZE 11								// Word의 크기(문자의 개수 + 1)
#define THRESHOLD 30							// 삽입정렬을 실행할 원소의 개수의 경계값

using namespace std;

typedef struct stack {
	int arr[MAXSTACKSIZE];
	int top=0;
};

char inputfile[20] = "input.txt";
char outputfile[20] = "output.txt";
char *st;
char *buff;

int start_value[THREAD_SIZE];
int end_value[THREAD_SIZE];

thread sort_pool[THREAD_SIZE];
thread merge_pool[THREAD_SIZE];
int merge_pool_cnt;
thread temp_pool[THREAD_SIZE];

void saveData() {
	FILE *fp = fopen(outputfile, "w");
	_fwrite_nolock(st, sizeof(char), NUMBEROFDATA * WORDSIZE - 1, fp);
	fclose(fp);
}

void loadData() {
	FILE *fp = fopen(inputfile, "r");
	_fread_nolock(st, sizeof(char), NUMBEROFDATA * WORDSIZE - 1, fp);
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

void small_sort_insert(int start, int end) {
	int i, j;
	char t[WORDSIZE];
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

int partition(int start, int end, int &lp) {
	if (!cmp(start, end)) _swap(start, end);
	int j = start + WORDSIZE;
	int g = end - WORDSIZE, k = start + WORDSIZE, p = start, q = end;
	while (k <= g) {
		if (!cmp(p, k)) {
			_swap(k, j);
			j += WORDSIZE;
		}
		else if (cmp(q, k)) {
			while (!cmp(g, q) && k < g) g -= WORDSIZE;
			_swap(k, g);
			g -= WORDSIZE;
			if (!cmp(p, k)) {
				_swap(k, j);
				j += WORDSIZE;
			}
		}
		k += WORDSIZE;
	}
	j -= WORDSIZE;
	g += WORDSIZE;
	_swap(start, j);
	_swap(end, g);
	lp = j;
	return g;
}

void quick_sort(int start, int end){
	stack start_stack, end_stack;
	push(start_stack, start);
	push(end_stack, end);
	while (start_stack.top != 0) {
		start = pop(start_stack);
		end = pop(end_stack);
		if (end - start <= THRESHOLD * WORDSIZE) {
			small_sort_insert(start, end);
			continue;
		}
		int lp, rp;
		if (start < end) rp = partition(start, end, lp);
		push(start_stack, rp + WORDSIZE);
		push(end_stack, end);
		push(start_stack, lp + WORDSIZE);
		push(end_stack, rp - WORDSIZE);
		push(start_stack, start);
		push(end_stack, lp - WORDSIZE);
	}
}

void merge(int s1, int e1, int s2, int e2) {
	int start1 = start_value[s1], end1 = end_value[e1]
		, start2 = start_value[s2], end2 = end_value[e2];
	
	int buff_cnt = start1;
	int left = start1;
	int right = start2;
	int real_end = end2 + WORDSIZE;
	while (left != start2 && right != real_end) {
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
		while (right != real_end) {
			memcpy(buff + buff_cnt, st + right, NUMBEROFCHARS);
			right += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
	}
	else if (right == real_end) {
		while (left != start2) {
			memcpy(buff + buff_cnt, st + left, NUMBEROFCHARS);
			left += WORDSIZE;
			buff_cnt += WORDSIZE;
		}
	}
	memcpy(st + start1, buff + start1, real_end - start1);
}

void prepare() {
	int temp = NUMBEROFDATA * WORDSIZE - 1;
	for (int i = WORDSIZE - 1; i < temp; i += WORDSIZE) st[i] = ' ';
	for (int i = WORDSIZE * 10 - 1; i < temp; i += WORDSIZE * 10) st[i] = '\n';
}

void divide_merge(){
	int mul = 2;
	int mul1 = 1;
	while (THREAD_SIZE / mul1 != 1) {
		int i;
		for (i = 0; i < THREAD_SIZE; i += mul) {
			if (i + mul1 != THREAD_SIZE) {
				merge_pool[merge_pool_cnt++] = thread(merge, i, i, i + mul1, i + mul1);
				end_value[i] = end_value[i + mul1];
			}
			else break;
		}
		for (int j = 0; j < merge_pool_cnt; j++) merge_pool[j].join();
		merge_pool_cnt = 0;

		// 홀수개일때
		/*if ((THREAD_SIZE / mul) % 2 == 1) {
			merge(start_value[i - mul], end_value[i - mul], start_value[i], end_value[i]);
		}*/

		mul1 *= 2;
		mul *= 2;
	}
}

int main() {
	st = (char*)malloc(sizeof(char) * (NUMBEROFDATA * WORDSIZE - 1));
	buff = (char*)malloc(sizeof(char) * (NUMBEROFDATA * WORDSIZE - 1));
	int diff = NUMBEROFDATA / THREAD_SIZE;

	time_t begin = clock();
	time_t _load, _sort, _merge, _prep, _save;

	// Load
	printf("Loading Data...\n");
	loadData();
	//printData(10);
	_load = clock() - begin;
	cout << "Loading time : " << ((double)_load / CLOCKS_PER_SEC) << "s" << endl;

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
	_sort = clock() - begin - _load;
	cout << "Sorting time : " << ((double)_sort / CLOCKS_PER_SEC) << "s" << endl;

	// Merge(홀수개일때 안 잡음)
	printf("Merging Data...\n");
	divide_merge();
	//printData(10);
	_merge = clock() - begin - _load - _sort;
	cout << "Merging time : " << ((double)_merge / CLOCKS_PER_SEC) << "s" << endl;

	// Prepare
	printf("Preparing Data...\n");
	prepare();
	_prep = clock() - begin - _load - _sort - _merge;
	cout << "Preparing time : " << ((double)_prep / CLOCKS_PER_SEC) << "s" << endl;

	// save
	printf("Saving Data...\n");
	saveData();
	_save = clock() - begin - _load - _sort - _merge - _prep;
	cout << "Saving time : " << ((double)_save / CLOCKS_PER_SEC) << "s" << endl;

	cout << "Total time : " << ((double)(clock() - begin) / CLOCKS_PER_SEC) << "s" << endl;
	free(st);
	free(buff);
	return 0;
}