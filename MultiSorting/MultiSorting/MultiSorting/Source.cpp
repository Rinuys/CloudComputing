#include<iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<cstdlib>

#define NUMBEROFSTRINGS 10000						// ���ڿ��� ����
#define NUMBEROFCHARS 10							// ������ ����

using namespace std;

string st[NUMBEROFSTRINGS];							// ������ ���ڿ� �迭

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

void printStrings(int num) {						// ���ڿ� �迭 ���
	for (int i = 0; i < num; i++) 
		cout << st[i] << endl;
}

int main() {
	srand(time(0));
	createStrings();

	printStrings(5);
	sort(st, &st[NUMBEROFSTRINGS]);
	cout << "HelloWorld!" << endl;
	printStrings(5);

	return 0;
}