#include "stdafx.h"
#include <Windows.h>
#include  <stdio.h>
#include  <conio.h>
#include  <fstream>
#include<iostream>
using namespace std;
#define sleep(n)  Sleep(n*1000)
void WriterThread(void * p);
void ReaderThread(void * p);
struct ThreadInfo {
	int tid;  //线程ID
	char role;  //扮演角色  R or W
	double delay;  //线程延迟
	double persist;  //线程读写操作持续时间
};

int ReadCount = 0;//读者数
int WriteCount = 0;//写者数
HANDLE Rmutex;// 局部临界资源(读者）
HANDLE Wmutex;// 局部临界资源（写者）
CRITICAL_SECTION RW_mutex; //全局临界资源
CRITICAL_SECTION fileSrc;

int main(int argc, char ** argv) {
	DWORD n_thread = 0;//线程数目
	DWORD thread_ID;//线程ID
	HANDLE h_thread[20];//线程对象数组
	ThreadInfo thread_info[20];//初始化同步对象
	Rmutex = CreateMutex(NULL, FALSE, LPCWSTR("mutex_for_readcount"));
	Wmutex = CreateMutex(NULL, FALSE, LPCWSTR("mutex_for_writecount"));
	InitializeCriticalSection(&RW_mutex);
	InitializeCriticalSection(&fileSrc);//初始化临界区
	ifstream inFile;
	inFile.open("test.txt");
	if (!inFile) {
		printf("error in open file !\n");
		return -1;
	}

	while (inFile) {
		inFile >> thread_info[n_thread].tid;
		inFile >> thread_info[n_thread].role;
		inFile >> thread_info[n_thread].delay;
		inFile >> thread_info[n_thread].persist;
		inFile.get();
		n_thread++;
	}


	for (int i = 0; i< n_thread; i++) {
		if (thread_info[i].role == 'R' || thread_info[i].role == 'r')
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ReaderThread), &thread_info[i], 0, &thread_ID);
		else
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(WriterThread), &thread_info[i], 0, &thread_ID);
	}

	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);//等待所有线程结束
	printf("所有读写操作均已完成 !\n");
	return 0;
}

void WriterThread(void * p) {
	double m_delay;
	double m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;

	sleep(m_delay); //延迟等待
	printf("写进程 %d 发送写请求 ! \n", m_id);
	//等待资源
	DWORD wait_for_mutex = WaitForSingleObject(Wmutex, -1);//申请写者计数器
	WriteCount++;
	if (WriteCount == 1) EnterCriticalSection(&RW_mutex);//如果此为第一个写进程，申请优先权限
	ReleaseMutex(Wmutex);//释放写者计数器资源
	EnterCriticalSection(&fileSrc); //申请文件资源
	//写操作开始
	printf("写进程 %d 开始写文件 !\n", m_id);
	sleep(m_persist);//写操作进行
	printf("写进程 %d 结束写文件 !\n", m_id);
	LeaveCriticalSection(&fileSrc);
	wait_for_mutex = WaitForSingleObject(Wmutex, -1);//申请写者计数器
	WriteCount--;
	if (WriteCount == 0) LeaveCriticalSection(&RW_mutex);//释放访问优先级
	ReleaseMutex(Wmutex);//释放写者计数器资源
}
void ReaderThread(void *p) {
	double m_delay;
	double  m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo *)(p))->delay;
	m_persist = ((ThreadInfo *)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;

	sleep(m_delay); //延迟等待
	printf(" 读进程 %d 发送读取请求 ! \n", m_id);
	EnterCriticalSection(&RW_mutex);//申请读取权限
	DWORD wait_for_mutex = WaitForSingleObject(Rmutex, -1);//等待互反信号里，保证对readcount的莫斥访问
	ReadCount++;
	if (ReadCount == 1) EnterCriticalSection(&fileSrc); //若第一个读进程，则申请文件资源
	ReleaseMutex(Rmutex);
	LeaveCriticalSection(&RW_mutex);
	//执行读操作
	printf("读进程 %d 开始读取文件 ! \n", m_id);
	sleep(m_persist);
	printf("读进程 %d 读完文件 ! \n", m_id);
	//释放互斥信号量
	wait_for_mutex = WaitForSingleObject(Rmutex, -1);
	ReadCount--;
	if (ReadCount == 0)
		LeaveCriticalSection(&fileSrc); //ReleaseMut ex (RV_ mutex):
	ReleaseMutex(Rmutex);

}
