#include "stdafx.h"
#include <Windows.h>
#include  <stdio.h>
#include  <conio.h>
#include  <fstream>
#include<iostream>
using namespace std;
#define sleep(n)  Sleep(n*1000)
void ProceducerThread(void * p);
void ConsumerThread(void * p);
// 缓冲区大小为 3 
int in = 0;//记录生产者向缓冲区生产的位置
int out = 0;//记录消费者向缓冲区消费的位置
int things = 0;//记录当前缓冲区的产品总量
struct ThreadInfo {
	int tid;  //线程ID
	char role;  //扮演角色  R or W
	double delay;  //线程延迟
};

HANDLE mutex;// 临界资源
HANDLE Empty;//表示空缓冲区数量
HANDLE Full;//满缓冲区数量

int main(int argc, char ** argv) {
	DWORD n_thread = 0;//线程数目
	DWORD thread_ID;//线程ID
	HANDLE h_thread[20];//线程对象数组
	ThreadInfo thread_info[20];//初始化同步对象
	mutex = CreateMutex(NULL, FALSE, LPCWSTR("mutex"));
	Empty = CreateSemaphore(NULL, 3, 3, LPCWSTR("empty"));
	Full = CreateSemaphore(NULL, 0, 3, LPCWSTR("full"));//初始化
	ifstream inFile;
	inFile.open("test2.txt");
	if (!inFile) {
		printf("error in open file !\n");
		return -1;
	}

	while (inFile) {
		inFile >> thread_info[n_thread].tid;
		inFile >> thread_info[n_thread].role;
		inFile >> thread_info[n_thread].delay;
		inFile.get();
		n_thread++;
	}//读取

	for (int i = 0; i< n_thread; i++) {
		if (thread_info[i].role == 'X' || thread_info[i].role == 'x')
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ConsumerThread), &thread_info[i], 0, &thread_ID);
		else
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ProceducerThread), &thread_info[i], 0, &thread_ID);
	}

	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);//等待所有线程结束
	printf("所有操作均已完成 !\n");
	return 0;
}

void ProceducerThread(void * p) {
	double m_delay;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_id = ((ThreadInfo*)(p))->tid;

	sleep(m_delay); //延迟等待
	printf("生产进程 %d 发送生产请求 ! \n", m_id);
	//等待资源
	DWORD wait_for_empty = WaitForSingleObject(Empty, -1);//申请空缓冲区访问
	DWORD wait_for_mutex = WaitForSingleObject(mutex, -1);//申请互斥量访问
	in = (in + 1) % 4;//记录生产位置
	things++;//记录产品余量
	printf("生产进程 %d 向缓冲区 %d 生产,本次生产结束  缓冲区有 %d 个资源\n", m_id, in,things);
	ReleaseMutex(mutex);//释放互斥访问量
	ReleaseSemaphore(Full,1,NULL);//释放满缓冲区数量
}
void ConsumerThread(void *p) {
	double m_delay;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_id = ((ThreadInfo*)(p))->tid;

	sleep(m_delay); //延迟等待
	printf(" 消费进程 %d 发送消费请求 ! \n", m_id);
	DWORD wait_for_full = WaitForSingleObject(Full, -1);//申请对满缓冲区的访问
	DWORD wait_for_mutex = WaitForSingleObject(mutex, -1);//申请互斥量访问
	out = (out + 1) % 4;//记录消费位置
	things--;//记录产品余量
	printf("消费进程 %d 向缓冲区 %d 消费,本次消费结束 缓冲区有 %d 个资源\n",m_id,out,things);
	ReleaseMutex(mutex);//释放互斥访问量
	ReleaseSemaphore(Empty, 1, NULL);//释放空缓冲区数量


}






