#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<cstdlib>

#define NUMBEROFSTRINGS 100000000					// 문자열의 개수
#define NUMBEROFCHARS 10							// 문자의 개수

using namespace std;

string *st = new string[NUMBEROFSTRINGS];							// 정렬할 문자열 배열
char inputfile[20] = "input.txt";

void createStrings() {								// 문자열 생성
	for (int i = 0; i < NUMBEROFSTRINGS; i++) {
		string temp="";
		for (int j = 0; j < NUMBEROFCHARS; j++) {
			int r = rand() % 36;					// 숫자 + 문자 = 36자
			char c;
			if (r < 10) c = r + '0';				// 숫자(10자)
			else		c = r - 10 + 'A';			// 문자(26자)
			temp.push_back(c);
		}
		st[i] = temp;
	}
}

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

void loadStrings() {
	FILE *fp = fopen(inputfile, "r");
	for (int i = 0; i < NUMBEROFSTRINGS; i++) 
		fscanf(fp, "%s", st[i]);
	
	fclose(fp);
}

void printStrings(int num) {						// 문자열 배열 출력
	for (int i = 0; i < num; i++) 
		cout << st[i] << endl;
}

int main() {
	/*srand(time(0));
	createStrings();
	saveStrings();*/

	loadStrings();

	printStrings(5);
	sort(st, &st[NUMBEROFSTRINGS]);
	cout << "HelloWorld!" << endl;
	printStrings(5);

	getchar();

	return 0;
}