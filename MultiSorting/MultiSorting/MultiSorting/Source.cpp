#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<cstdlib>

#define NUMBEROFSTRINGS 100000000					// ���ڿ��� ����
#define NUMBEROFCHARS 10							// ������ ����

using namespace std;

string *st = new string[NUMBEROFSTRINGS];							// ������ ���ڿ� �迭
char inputfile[20] = "input.txt";

void createStrings() {								// ���ڿ� ����
	for (int i = 0; i < NUMBEROFSTRINGS; i++) {
		string temp="";
		for (int j = 0; j < NUMBEROFCHARS; j++) {
			int r = rand() % 36;					// ���� + ���� = 36��
			char c;
			if (r < 10) c = r + '0';				// ����(10��)
			else		c = r - 10 + 'A';			// ����(26��)
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

void printStrings(int num) {						// ���ڿ� �迭 ���
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