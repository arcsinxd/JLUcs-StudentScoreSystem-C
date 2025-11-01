#define _CRT_SECURE_NO_WARNINGS
#define use_CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#pragma warning(disable: 0631)

#include<time.h>
#include"resource.h"

#include <graphics.h>  
#include <conio.h>  
#include <iostream>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<mmsystem.h>
#include<tchar.h>
#include<thread>
#include<string.h>
#include <locale.h>
#include"menu.h"
#include"struct.h"
extern"C"
{
#include"file.h"
}

#include<mmsystem.h>//包含多媒体设备接口头文件,一定放在graphics.h下面

#include"menu.h"

#pragma comment(lib,"winmm.lib")//加载静态库
int main()
{


	PlaySound(L"kn.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//getchar();
	initgraph(1080, 722, SHOWCONSOLE);
	setbkcolor(WHITE);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, _T("学生成绩管理系统"));
	int i=menu();
	switch (i)
	{
		case 1:
			//学生端登录完毕 转入学生端
			break;
		case 2:
			//教师端登录完毕 转入教师端
			tch_menu();
			break;
		case 3:
			//教务端登录完毕 转入教务端
			mng_menu();
			break;
	}

	return 0;
}