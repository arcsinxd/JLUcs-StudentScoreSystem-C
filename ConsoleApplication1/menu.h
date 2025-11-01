#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable: 4996)
#pragma warning(disable: 6386)

#include <graphics.h>  
#include <conio.h>  
#include <iostream>
#include<stdio.h>
#include<Windows.h>
#include<tchar.h>
extern"C"
{
#include"file.h"
}
#include<mmsystem.h>//包含多媒体设备接口头文件,一定放在graphics.h下面


#pragma comment(lib,"winmm.lib")//加载静态库
//释放内存
void free_stdlist(struct Student_Information* head);
void free_tchlist(struct Teacher_Information* head);
void free_mnglist(struct Manager_Information* head);
//创建信息链表
struct Student_Information* creat_stdlist();
struct Teacher_Information* creat_tchlist();
struct Manager_Information* creat_mnglist();
//链表寻找学号对应信息
struct Student_Information* find_s_num(int s_num);
struct Teacher_Information* find_t_num(int t_num);
//隐藏密码
void hide(int lenth);
void hide1(int lenth);
//将修改后链表写入文件
void preserve(Student_Information* p);
void tpreserve(struct Teacher_Information* p);
//登录界面
int student_login();
int teacher_login();
int manager_login();
//密码修改
void stdre(int s_num);
void tchre(int t_num);
void mngre();

//管理员注册
void mngregister(FILE* fp);
//检查管理员是否第一次登录
void check();
//解冻
void unfreeze();

void tch_menu();
void mng_menu();



int menu();

#endif