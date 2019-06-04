//#include<iostream>
//#include<string>
//#include<ctime>
//#include<cstdlib>
//#include<thread>
//
//#define thread_size 12
//#define numberofdata 100000000					// 문자열의 개수
//#define numberofchars 10							// 문자의 개수
//#define maxstacksize 100000
//#define wordsize 11
//
//using namespace std;
//
//typedef struct word {
//	char ch[10];
//	char temp;
//};
//
//typedef struct stack {
//	int arr[maxstacksize];
//	int top = 0;
//};
//
//char **st;			// 정렬할 문자열 배열
//char inputfile[20] = "input.txt";
//char outputfile[20] = "output.txt";
//char *st2;
//
//int flush_pointer[thread_size];
//int finish_length[thread_size];
//int start_value[thread_size];
//int end_value[thread_size];
//
//thread sort_pool[thread_size];
//thread merge_pool[thread_size];
//int merge_pool_cnt;
//
//void createstrings() {								// 문자열 생성
//	for (int i = 0; i < numberofdata; i++) {
//		string temp="";
//		for (int j = 0; j < numberofchars; j++) {
//			int r = rand() % 36;					// 숫자 + 문자 = 36자
//			char c;
//			if (r < 10) c = r + '0';				// 숫자(10자)
//			else		c = r - 10 + 'a';			// 문자(26자)
//			temp.push_back(c);
//		}
//		st[i] = temp;
//	}
//}
//
//void savedata() {
//	file *fp = fopen(inputfile,"w+");
//	for (int j = 0; j < numberofdata / 10 ; j++) {
//		fprintf(fp, "%s", st[j*10]);
//		for (int i = 1; i < 10; i++) 
//			fprintf(fp, " %s", st[j * 10 + i]);
//		fprintf(fp, "\n");
//	}
//	fclose(fp);
//}
//
//int main() {
//	st = (char**)malloc(sizeof(char*) * numberofdata);
//	for (int i = 0; i < numberofdata; i++)
//		st[i] = (char*)malloc(sizeof(char) * (numberofchars + 1));
//	//st = (char*)malloc(sizeof(char) * ((numberofdata * 11) + 1));
//
//	srand(time(0));
//	createstrings();
//	savedata();
//
//	return 0;
//}