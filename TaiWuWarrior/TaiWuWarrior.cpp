// TaiWuWarrior.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "TaiWuInfo.h"

bool isLockDay = false;
bool isLockWuxing = false;
DWORD WINAPI showUI(LPVOID lpParameter);
DWORD WINAPI lockDayFunc(LPVOID lpParameter);
DWORD WINAPI lockWuXingFunc(LPVOID lpParameter);
HANDLE hThread = NULL;
HANDLE lockDayThread = NULL;
HANDLE lockWuxingThread = NULL;
TaiWuInfo twInfo((TCHAR*)(TEXT("The Scroll Of Taiwu Alpha V1.0.exe")));


int main()
{
	hThread = CreateThread(NULL, 0, showUI, 0, 0, NULL);

	DWORD exitCode = 0;

	while (GetExitCodeProcess(twInfo.hProcess, &exitCode) && exitCode == STILL_ACTIVE)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			isLockDay = !isLockDay;
			ResumeThread(hThread);

			if (isLockDay)
			{
				lockDayThread = CreateThread(NULL, 0, lockDayFunc, 0, 0, NULL);
			}
			else
			{
				TerminateThread(lockDayThread, 0);
			}
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			twInfo.AddExp(100);
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			twInfo.AddCuipo(50);
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{

			twInfo.AddQinyin(50);
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			twInfo.AddHuti(50);
		}

		if (GetAsyncKeyState(VK_F6) & 1)
		{
			twInfo.AddQiqiao(50);
		}

		if (GetAsyncKeyState(VK_F7) & 1)
		{
			isLockWuxing = !isLockWuxing;
			ResumeThread(hThread);

			if (isLockWuxing)
			{
				lockWuxingThread = CreateThread(NULL, 0, lockWuXingFunc, 0, 0, NULL);
			}
			else
			{
				TerminateThread(lockWuxingThread, 0);
			}
		}

	}

	CloseHandle(hThread);

	getchar();
	
}

DWORD WINAPI showUI(LPVOID lpParameter) {
	while (true)
	{
		system("cls");
		printf("\n-------------------------太吾勇士--------------------------\n");
		printf("-------------------Athor:absolutelycold--------------------\n");
		printf("-----------获得最新版:github.com/absolutelycold------------\n\n\n");
		if (isLockDay)
		{
			printf("                F1:锁定天数:> ON <\n\n");
		}
		else {
			printf("                F1:锁定天数:> OFF <\n\n");
		}

		printf("                F2:添加100历练\n\n");

		printf("                F3:添加50催破\n\n");

		printf("                F4:添加50轻灵\n\n");

		printf("                F5:添加50护体\n\n");

		printf("                F6:添加50奇窍\n\n");

		if (isLockWuxing)
		{
			printf("                F7:锁定学习悟性(在学习界面开启):> ON <\n\n");
			
		}
		else
		{
			printf("                F7:锁定学习悟性(在学习界面开启):> OFF <\n\n");
		}
		printf("\n-----------------------------------------------------------\n\n");
		SuspendThread(hThread);
	}
}

DWORD WINAPI lockDayFunc(LPVOID lpParameter) {
	while (true)
	{
		if (!(twInfo.writeDay(30))) {
			TerminateThread(lockDayThread, 0);
		}
		Sleep(100);
	}
}

DWORD WINAPI lockWuXingFunc(LPVOID lpParameter) {
	while (true)
	{
		if (!(twInfo.writeWuxing(999)))
		{
			TerminateThread(lockWuxingThread, 0);
		}
		Sleep(100);
	}
}
