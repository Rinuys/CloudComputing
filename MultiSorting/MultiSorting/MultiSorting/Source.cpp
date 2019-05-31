#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

#define NUMBEROFSTRINGS 100000000					// 문자열의 개수
#define NUMBEROFCHARS 10							// 문자의 개수

using namespace std;

typedef struct word {
	char ch[10];
	char temp;
};

char **st;			// 정렬할 문자열 배열
char inputfile[20] = "input.txt";
char outputfile[20] = "output.txt";
char *st2;

//void createStrings() {								// 문자열 생성
//	for (int i = 0; i < NUMBEROFSTRINGS; i++) {
//		string temp="";
//		for (int j = 0; j < NUMBEROFCHARS; j++) {
//			int r = rand() % 36;					// 숫자 + 문자 = 36자
//			char c;
//			if (r < 10) c = r + '0';				// 숫자(10자)
//			else		c = r - 10 + 'A';			// 문자(26자)
//			temp.push_back(c);
//		}
//		st[i] = temp;
//	}
//}

//void saveStrings() {
//	FILE *fp = fopen(inputfile,"w+");
//	for (int j = 0; j < NUMBEROFSTRINGS / 10 ; j++) {
//		fprintf(fp, "%s", st[j*10]);
//		for (int i = 1; i < 10; i++) 
//			fprintf(fp, " %s", st[j * 10 + i]);
//		fprintf(fp, "\n");
//	}
//	fclose(fp);
//}

void saveStrings() {
	FILE *fp = fopen(outputfile, "w+");
	fwrite(st2, sizeof(char), NUMBEROFSTRINGS*11, fp);
	fprintf(fp, "\n");
	fclose(fp);
}

void strabcpy(char* destination, char* source, int source_start) {
	for (int i = 0; i < NUMBEROFCHARS; i++) 
		destination[i] = source[source_start + i];
	destination[NUMBEROFCHARS] = NULL;
}

void loadStrings() {
	FILE *fp = fopen(inputfile, "r");
	printf("hoho\n");
	/*int temp = NUMBEROFSTRINGS / NUMBEROFCHARS;
	for (int i = 0; i < temp; i++) {
		char temp_string[110];
		fread(temp_string, sizeof(char), 110, fp);
		for (int j = 0; j < 10; j++) {
			strabcpy(st[i * 10 + j], temp_string, j*11);
		}
	}*/
	/*char buf[10];
	for (int i = 0; i < NUMBEROFSTRINGS; i++) {
		fread(st[i], sizeof(char), 10, fp);
		fread(buf, sizeof(char), 1, fp);
	}*/
	/*while (a = fread(buff, sizeof(char), 1100000001, fp))
		buff += a;*/
	fread(st2, sizeof(char), 1100000001, fp);
	fclose(fp);
}

//void printStrings(int num) {						// 문자열 배열 출력
//	for (int i = 0; i < num; i++) 
//		cout << st[i] << endl;
//}

void printStrings(int num) {
	for (int i = 0; i < num; i++) {
		char temp[11];
		memcpy(temp, st2 + sizeof(word)*i, 10);
		temp[10] = '\0';
		printf("%s\n",temp);
	}
}

bool cmp(int index1, int index2) {
	// st2[index1] <= st2[index2] : true
	// st2[index1] > st2[index2] : false
	for (int i = 0; i < 10; i++) {
		if (st2[index1 + i] == st2[index2 + i]) continue;
		else if (st2[index1 + i] < st2[index2 + i]) return true;
		else return false;
	}
	return true;
}

void _swap(int index1, int index2) {
	char ch[11];
	memcpy(ch, st2 + index1, 10);
	memcpy(st2 + index1, st2 + index2, 10);
	memcpy(st2 + index2, ch, 10);
}

void quick_sort(int start, int end) {
	if (start >= end) return;		// 원소가 1개인 경우

	int pivot = start;
	int i = pivot + sizeof(word);	// 왼쪽 출발 지점 
	int j = end;					// 오른쪽 출발 지점
	int temp;

	while (i <= j) {				// 포인터가 엇갈릴때까지 반복
		while (i <= end && cmp(i,pivot)) i+=sizeof(word);
		while (j > start && cmp(pivot,j)) j-=sizeof(word);
		if (i > j) _swap(j, pivot); // 엇갈림
		else _swap(i, j);			// i번째와 j번째를 스왑
	}

	// 분할 계산
	quick_sort(start, j - sizeof(word));
	quick_sort(j + sizeof(word), end);
}

int main() {
	/*st = (char**)malloc(sizeof(char*) * NUMBEROFSTRINGS);
	for (int i = 0; i < NUMBEROFSTRINGS; i++) 
		st[i] = (char*)malloc(sizeof(char) * (NUMBEROFCHARS + 1));*/
	st2 = (char*)malloc(sizeof(char) * ((NUMBEROFSTRINGS * 11) + 1));
	
	/*srand(time(0));
	createStrings();
	saveStrings();*/

	time_t start = clock();
	loadStrings();
	
	
	printStrings(5);
	quick_sort(0, (NUMBEROFSTRINGS - 1) * 11);
	printStrings(5);

	saveStrings();
	time_t end = clock();
	printf("loading time : %dms\n", (int)(end - start));
	
	/*sort(st, &st[NUMBEROFSTRINGS]);
	cout << "HelloWorld!" << endl;
	printStrings(5);*/

	getchar();

	return 0;
}