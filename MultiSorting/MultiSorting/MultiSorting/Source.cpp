#include<iostream>
#include<string>
#include<algorithm>
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

void saveStrings() {
	FILE *fp = fopen(inputfile,"w+");
	for (int j = 0; j < NUMBEROFSTRINGS / 10 ; j++) {
		fprintf(fp, "%s", st[j*10]);
		for (int i = 1; i < 10; i++) {
			fprintf(fp, " %s", st[j * 10 + i]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void strabcpy(char* destination, char* source, int source_start) {
	for (int i = 0; i < NUMBEROFCHARS; i++) {
		destination[i] = source[source_start + i];
	}
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
	char *buff = st2;
	int a = 0;
	while (a = fread(buff, sizeof(char), 1100000001, fp))
		buff += a;
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

int greater(int index1, int index2) {
	for (int i = 0; i < 10; i++) {
		if (st2[index1 + i] == st2[index2 + i])
			continue;
		else if (st2[index1 + i] < st2[index2 + i])
			return index2;
		else
			return index1;
	}
	return index1;
}

void swap(int index1, int index2) {
	char ch[11];
	memcpy(ch,st2+index1,10);
	memcpy(st2 + index1, st2 + index2, 10);
	memcpy(st2 + index2, ch, 10);
}

void quicksort() {

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
	time_t end = clock();
	printf("loading time : %dms\n", (int)(end - start));
	
	printStrings(5);
	/*printStrings(5);
	sort(st, &st[NUMBEROFSTRINGS]);
	cout << "HelloWorld!" << endl;
	printStrings(5);*/

	getchar();

	return 0;
}