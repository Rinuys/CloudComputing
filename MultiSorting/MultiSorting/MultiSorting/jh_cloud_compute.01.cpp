/*
클라우드컴퓨팅 첫코딩.
현재 퀵소트에 에러가 있는 것으로 추측됨.
1. cc_data.txt 데이터 10개만 스레드 2개로 해보면 데이터 틀림
2. 읽으면서 바로 퀵소트 시작하는 부분이 필요
3. 모두 퀵소트 시작하면 메인스레드가 정렬된 부분을 보고 머지 및 출력 수행.
*/

#include <cstdio>
#include <cstdlib>
#include <thread>

#define THREAD_SIZE 7
#define DATA_SIZE 100000000

using namespace std;

long *arr;

long flush_pointer[THREAD_SIZE];
long finish_length[THREAD_SIZE];
long start_value[THREAD_SIZE];
long end_value[THREAD_SIZE];

void myqsort(int id);
void myqsubsort(int id, long start, long end);

void load(){
	FILE *rf = fopen("cc_data.txt","rt");
	for(long i=0;i<DATA_SIZE;i++){
		char buffer[14];
		fread(buffer,sizeof(char),11,rf);
		if(buffer[10]=='\r')
			fgetc(rf);
            
		long cal=0l;
		for(int c=0;c<10;c++)
            cal = (cal << 6) + buffer[c] - '0';
        arr[i] = cal;
	}
	fclose(rf);
}

void saving(){
	FILE *wf = fopen("output.txt","wt");
	long total_finish=0;
	while(total_finish<DATA_SIZE){
        bool pass=false; // 정렬이 일부 안됬을때 continue;
        int min_thread=-1;
        long min_value=4e18l;
        for(int i=0;i<THREAD_SIZE;i++){
            if(flush_pointer[i] > end_value[i])
                continue;
            if(flush_pointer[i] > finish_length[i]){
                pass=true;
                break;
            }

            long value=arr[flush_pointer[i]];
            if(min_thread==-1 ||  min_value>value){
                min_thread=i;
                min_value=value;
            }
        }
        if(min_thread==-1 || pass==true)
            continue;
            
        char buffer[12];
        buffer[10]='\r', buffer[11]='\n';
        for(int i=9;i>=0;i--){
            buffer[i] = (min_value & 63) + '0';
            min_value = min_value >> 6;
        }
        fwrite(buffer, sizeof(char), 12, wf);
        total_finish+=1;
        flush_pointer[min_thread]+=1;
	}
	fclose(wf);
}

int main(){
	thread pool[THREAD_SIZE];
    arr = new long[DATA_SIZE];
	
	load();

	long diff = DATA_SIZE / THREAD_SIZE;
	
	for(int i=0;i<THREAD_SIZE-1;i++){
		long start=diff*i, end=diff*(i+1)-1;
		flush_pointer[i]=start;
		finish_length[i]= start;
        start_value[i] = start;
		end_value[i] = end;
		pool[i] = thread(myqsort, i);
	}
	
	long start=diff*(THREAD_SIZE-1), end=DATA_SIZE-1;
	flush_pointer[THREAD_SIZE-1] = start;
	finish_length[THREAD_SIZE-1] = start;
    start_value[THREAD_SIZE-1]  = start;
	end_value[THREAD_SIZE-1] = end;
	pool[THREAD_SIZE-1] = thread(myqsort, THREAD_SIZE-1);
	
	saving();


    for(int t=0;t<THREAD_SIZE;t++)
        pool[t].join();

    delete[] arr;
	return 0;
}

void myqsort(int id){
    long start=start_value[id], end=end_value[id];
    myqsubsort(id,start,end);
    finish_length[id]=end;    
}

void myqsubsort(int id, long start, long end){
    long pivot=arr[start];
    long front=start+1, back=end;
    long swap;

    if(start>=end)
        return;
    if(start+1==end){
        if(arr[start]>arr[end]){
            swap=arr[start];
            arr[start]=arr[end];
            arr[end]=swap;
        }
        return;
    }

    while(front<back-1){
        while(front < back-1 && arr[back]>=pivot) back--;
        while(front < back-1 && arr[front]<=pivot) front++;
        if (arr[front]>=pivot && arr[back]<=pivot){
            swap = arr[front];
            arr[front]=arr[back];
            arr[back]=swap;
        }
    }
	long point=front;
	if(arr[front]>pivot)
		point=front-1;
	else if(arr[back]<pivot)
		point=back;
	else
		point=front;
	swap = arr[start];
	arr[start]=arr[point];
	arr[point]=swap;
    myqsubsort(id, start, point-1);
    myqsubsort(id, point+1,end);
    finish_length[id]=end;
}
