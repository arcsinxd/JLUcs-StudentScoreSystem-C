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


#pragma comment(lib,"winmm.lib")//加载静态库
//释放内存
void free_stdlist(struct Student_Information* head)
{
    struct Student_Information* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
void free_tchlist(struct Teacher_Information* head)
{
    struct Teacher_Information* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
void free_mnglist(struct Manager_Information* head)
{
    struct Manager_Information* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
//创建信息链表
struct Student_Information* creat_stdlist()//创建学生信息链表
{
    struct Student_Information* head = NULL;
    FILE* fp = fopen("student_info.txt", "r");
    if (fp == NULL)
    {
        printf("打开失败\n");
        return NULL;
    }

    struct Student_Information* p = NULL;
    while (!feof(fp))
    {
        struct Student_Information* q = (struct Student_Information*)malloc(sizeof(struct Student_Information));
        fscanf(fp, "%s %d %s %s %s %s %d %d %d %f %f", q->student_name, &q->s_num, q->password, q->ID, q->college, q->major, &q->s_class, &q->year, &q->change, &q->total_gpa, &q->total_credit);
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            p = q;
        }
        else
        {
            p->next = q;
            p = q;
        }
    }

    fclose(fp);
    return head;
}
struct Teacher_Information* creat_tchlist()//创建教师信息链表
{
    struct Teacher_Information* head = NULL;
    FILE* fp = fopen("teacher_info.txt", "r");
    if (fp == NULL)
    {
        printf("打开失败\n");
        return NULL;
    }

    struct Teacher_Information* p = NULL;
    while (!feof(fp))
    {
        struct Teacher_Information* q = (struct Teacher_Information*)malloc(sizeof(struct Teacher_Information));
        fscanf(fp, "%s %d %s %s %s %d", q->teacher_name, &q->t_num, q->ID, q->password, q->college, &q->flag);
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            p = q;
        }
        else
        {
            p->next = q;
            p = q;
        }
    }

    fclose(fp);
    return head;
}
struct Manager_Information* creat_mnglist()
{
    struct Manager_Information* head = NULL;
    FILE* fp = fopen("manager_info.txt", "r");
    if (fp == NULL)
    {
        printf("打开失败\n");
        return NULL;
    }

    struct Manager_Information* p = NULL;
    while (!feof(fp))
    {
        struct Manager_Information* q = (struct Manager_Information*)malloc(sizeof(struct Manager_Information));
        fscanf(fp, "%s", q->password);
        q->next = NULL;
        if (head == NULL)
        {
            head = q;
            p = q;
        }
        else
        {
            p->next = q;
            p = q;
        }
    }

    fclose(fp);
    return head;
}

//链表寻找学号对应信息
struct Student_Information* find_s_num(int s_num)
{
    struct Student_Information* head = creat_stdlist();
    struct Student_Information* p = head;
    while (p != NULL)
    {
         if (p->s_num== s_num)
         {
             return p;
         }
         p = p->next;
    }
    setlinecolor(RGB(1, 130, 198));//框
    setfillcolor(RGB(1, 130, 198));//底
    fillrectangle(0, 600, 1000, 650);
    Sleep(300);
    settextstyle(50, 0, _T("楷体"));
    outtextxy(400, 600, _T("用户未找到！"));
    free_stdlist(head);
    return NULL;
}
struct Teacher_Information* find_t_num(int t_num)
{
    struct Teacher_Information* head = creat_tchlist();
    struct Teacher_Information* p = head;
    while (p != NULL)
    {
        if (p->t_num == t_num)
        {
            return p;
        }
        p = p->next;
    }
    setlinecolor(RGB(1, 130, 198));//框
    setfillcolor(RGB(1, 130, 198));//底
    fillrectangle(0, 600, 1000, 650);
    Sleep(300);
    settextstyle(50, 0, _T("楷体"));
    outtextxy(400, 600, _T("用户未找到！"));
    free_tchlist(head);
    return NULL;
}

//隐藏密码
void hide(int lenth)
{
    int x = 390;
    settextstyle(50, 0, _T("楷体"));
    for (int i = 0; i < lenth; i++)
    {
        
        outtextxy(x, 350, '*');
        x = x + 30;
    }
}
void hide1(int lenth)
{
    int x = 390;
    settextstyle(50, 0, _T("楷体"));
    for (int i = 0; i < lenth; i++)
    {

        outtextxy(x, 250, '*');
        x = x + 30;
    }
}
//将修改链表密码并写入文件
void preserve(Student_Information* p)//学生
{
    Student_Information* head = creat_stdlist();
    Student_Information* tmp = head;

    while (tmp != NULL)
    {
        if (tmp->s_num == p->s_num)
        {
            strcpy(tmp->password, p->password);
            break;
        }
        tmp = tmp->next;
    }

    FILE* fp = fopen("student_info.txt", "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    Student_Information* q = head;
    while (q != NULL)
    {
        fprintf(fp, "%s %d %s %s %s %s %d %d %d %f %f\n", q->student_name, q->s_num, q->password, q->ID, q->college, q->major, q->s_class, q->year, q->change, q->total_gpa, q->total_credit);
        q = q->next;
    }

    fclose(fp);
    free_stdlist(head);
}
void tpreserve(struct Teacher_Information* p)//教师
{
    struct Teacher_Information* head = creat_tchlist();
    struct Teacher_Information* tmp = head;

    while (tmp != NULL)
    {
        if (tmp->t_num == p->t_num)
        {
            strcpy(tmp->password, p->password);
            tmp->flag = p->flag;
            break;
        }
        tmp = tmp->next;
    }

    FILE* fp = fopen("teacher_info.txt", "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    struct Teacher_Information* q = head;
    while (q != NULL)
    {
        fprintf(fp, "%s %d %s %s %s %d", q->teacher_name, q->t_num, q->password, q->ID, q->college, q->flag);
        q = q->next;
    }

    fclose(fp);
    free_tchlist(head);
}
//管理员注册
void mngregister(FILE* fp)
{
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);
    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字

    //打字

    settextstyle(35, 0, _T("楷体"));
    outtextxy(95, 150, _T("检测到您第一次使用本系统，已为您跳转至注册界面！"));

    // 画按钮
    setlinecolor(BLACK);//黑框
    setfillcolor(WHITE);//白底
    fillrectangle(380, 250, 800, 300);
    settextstyle(50, 0, _T("楷体"));
    outtextxy(35, 250, _T("设置教务密码："));
    fillrectangle(380, 350, 800, 400);
    outtextxy(35, 350, _T("确认教务密码："));


    struct Manager_Information p;
stdchange1:wchar_t c[50];
    char password_n[50];
    InputBox(c, 50, L"请设置教务处管理密码：", L"设置教务处密码");
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(380, 350, 800, 400);
    int lenth = wcstombs(password_n, c, 128);
    hide1(lenth);

    wchar_t d[50];
    char password_n1[50];
    InputBox(d, 50, L"请确认密码", L"设置教务处密码");
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(380, 350, 800, 400);
    int lenth1 = wcstombs(password_n1, d, 128);
    hide(lenth1);

    if (strcmp(password_n, password_n1) == 0)
    {
        strcpy(p.password, password_n);
        fprintf(fp, "%s", p.password);
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);
        outtextxy(400, 600, _T("设置成功！"));
        Sleep(1500);
        fclose(fp);
        return;
    }
    else
    {
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);
        Sleep(300);
        outtextxy(300, 600, _T("两次输入不一致！请重新输入！"));

        goto stdchange1;
    }
}
//检查管理员是否第一次登录
void check()
{

    FILE* fp;
    fp = fopen("manager_info.txt", "r+");
    if (fp == NULL) 
    {
        closegraph();
        printf("无法打开文件\n");
        exit(0);
    }

    int first = fgetc(fp);
    

    if (first == EOF) 
    {
        cleardevice();
        mngregister(fp);
        fclose(fp);
        return;
    }
    else //不是第一次登录
    {
        fclose(fp);
        return;
    }
}
//解冻
void unfreeze()
{
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);
    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字
    //打字
    outtextxy(5, 250, _T("请输入教师工号："));
    // 画按钮
    setlinecolor(WHITE);
    setfillcolor(RGB(201, 80, 80));
    fillrectangle(380, 450, 700, 550);
    settextstyle(100, 0, _T("楷体"));
    outtextxy(440, 450, _T("解冻"));


    setlinecolor(BLACK);//黑框
    setfillcolor(WHITE);//白底
    fillrectangle(380, 250, 800, 300);

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 550, 900, 590);
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 550, _T("返回菜单"));

    MOUSEMSG msg;
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int t_num;

    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                //输入工号
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 250 && msg.y <= 300)
                {
                    if (flag1 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 250, 800, 300);
                        flag1 = 0;
                    }
                    wchar_t a[6];
                    InputBox(a, 6, L"请输入教师工号", L"教师工号输入");
                    settextstyle(50, 0, _T("楷体"));
                    outtextxy(390, 250, a);
                    flag1++;

                    t_num = _wtoi(a);
                    continue;
                }
                //返回菜单
                if (msg.x >= 750 && msg.x <= 950 && msg.y >= 550 && msg.y <= 590)
                {
                    menu();
                }
                //解冻
                if ((flag1 == 1) && msg.x >= 380 && msg.x <= 700 && msg.y >= 450 && msg.y <= 550)
                {
                    FILE* fp = NULL;
                    fp = fopen("teacher_info.txt", "r+");
                    if (fp == NULL)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(400, 600, _T("文件不存在！"));
                        return;
                    }
                    struct Teacher_Information* p;
                    p = find_t_num(t_num);
                    if (p == NULL)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(400, 600, _T(" 用户不存在！"));
                        continue;
                    }
                    if (p!=NULL&&p->flag >= 5)
                    {
                        p->flag = 0;
                        tpreserve(p);
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(400, 600, _T("账号已解冻"));
                        continue;
                    }
                    else
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(350, 600, _T("该账号并未冻结"));
                        continue;
                    }
                }
            }
        }
    }
}

//登录界面
int student_login()
{
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);



    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字

    //打字
    outtextxy(255, 250, _T("学号："));
    outtextxy(255, 350, _T("密码："));
    settextstyle(30, 0, _T("楷体"));
    outtextxy(185, 400, _T("(初始密码为0000)"));

    // 画按钮
    setlinecolor(WHITE);
    setfillcolor(RGB(201, 80, 80));
    fillrectangle(380, 450, 700, 550);
    settextstyle(100, 0, _T("楷体"));
    outtextxy(440, 450, _T("登录"));
    

    setlinecolor(BLACK);//黑框
    setfillcolor(WHITE);//白底
    fillrectangle(380, 250, 800, 300);
    fillrectangle(380, 350, 800, 400);

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 550, 900, 590);
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 550, _T("返回菜单"));


    MOUSEMSG msg;
    int flag=0;
    int flag1 = 0;
    int flag2 = 0;
    int s_num;
    char password[50];
    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                //输入学号
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 250 && msg.y <= 300)
                {
                    if (flag1 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 250, 800, 300);
                        flag1 = 0;
                    }
                    wchar_t a[9];
                    InputBox(a, 9, L"请输入学号", L"学号输入");
                    settextstyle(50, 0, _T("楷体"));
                    outtextxy(390, 250, a);
                    flag1++;

                    s_num = _wtoi(a);
                    continue;
                }
                //输入密码
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 350 && msg.y <= 400)
                {
                    if (flag2 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 350, 800, 400);
                        flag2 = 0;
                    }
                    wchar_t b[50];
                    
                    InputBox(b, 50, L"请输入密码", L"密码输入");
                    settextstyle(50, 0, _T("楷体"));


                    int lenth = wcstombs(password, b, 512);
                    hide(lenth);
                    flag2++;


                    continue;
                }
                //返回上一级
                if (msg.x >= 750 && msg.x <= 950 && msg.y >= 550 && msg.y <= 610)
                {
                    menu();
                }
                //登录
                if ((flag1 == 1) && (flag2 == 1) && msg.x >= 380 && msg.x <= 700 && msg.y >= 450 && msg.y <= 550)
                {
                    FILE* fp = NULL;
                    fp = fopen("student_info.txt", "r+");
                    if (fp == NULL)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);//清
                        Sleep(300);
                        outtextxy(400, 600, _T("文件不存在！"));
                        Sleep(2000);
                        exit(0);
                    }
                    struct Student_Information* p;
                    p=find_s_num(s_num);
                    if ((p!=NULL)&&(strcmp(p->password,password)==0))
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(400, 600, _T("登录成功"));

                        if (strcmp(p->password, "0000") == 0)
                        {
                            stdchange1:wchar_t c[50];
                            char password_n[50];
                            InputBox(c, 50, L"检测到您的密码为初始密码！请输入新密码", L"请修改初始密码");
                            setlinecolor(BLACK);
                            setfillcolor(WHITE);
                            fillrectangle(380, 350, 800, 400);
                            int lenth = wcstombs(password_n,c, 128);
                            hide(lenth);

                            if (strcmp(password_n, p->password)==0)
                            {
                                setlinecolor(RGB(1,130,198));//框
                                setfillcolor(RGB(1, 130, 198));//底
                                fillrectangle(0, 600, 1000, 650);
                                Sleep(300);
                                outtextxy(300, 600, _T("与原密码一致！请重新输入！"));
                                goto stdchange1;
                            }
                            else
                            {
                                wchar_t d[50];
                                char password_n1[50];
                                InputBox(d, 50, L"请再次输入新密码", L"请修改初始密码");
                                setlinecolor(BLACK);
                                setfillcolor(WHITE);
                                fillrectangle(380, 350, 800, 400);
                                int lenth1 =wcstombs(password_n1, d, 128);
                                hide(lenth1);
                                if (strcmp(password_n, password_n1) == 0)
                                {
                                    strcpy(p->password, password_n);
                                    setlinecolor(RGB(1, 130, 198));//框
                                    setfillcolor(RGB(1, 130, 198));//底
                                    fillrectangle(0, 600, 1000, 650);
                                    Sleep(300);
                                    outtextxy(300, 600, _T("修改成功！为您自动登录！"));
                                    preserve(p);
                                    Sleep(2000);
                                    return 1;
                                }
                                else
                                {
                                    setlinecolor(RGB(1, 130, 198));//框
                                    setfillcolor(RGB(1, 130, 198));//底
                                    fillrectangle(0, 600, 1000, 650);
                                    Sleep(300);
                                    outtextxy(300, 600, _T("两次输入不一致！请重新输入！"));
                                    
                                    goto stdchange1;
                                }
                                
                            }
                        }
                        Sleep(2000);
                        return 1;
                    }
                    else//密码不对
                    {
                        if (p != NULL)
                        {
                            setlinecolor(RGB(1, 130, 198));//框
                            setfillcolor(RGB(1, 130, 198));//底
                            fillrectangle(0, 600, 1000, 650);
                            Sleep(300);
                            settextstyle(50, 0, _T("楷体"));
                            outtextxy(400, 600, _T("密码错误！"));
                            setlinecolor(WHITE);
                            setfillcolor(WHITE);
                            fillrectangle(750, 480, 900, 530);
                            settextstyle(35, 0, _T("楷体"));
                            outtextxy(755, 490, _T("找回密码"));
                            flag++;
                            continue;

                        }
                        
                    }
                    fclose(fp);
                }
                //密码不对后找回密码
                if ((flag!=0)&&(flag1 == 1) && (flag2 == 1) && msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                {
                    cleardevice();
                    putimage(0, 0, &background);
                    stdre(s_num);
                }
            }

        }
    }
}
int teacher_login()
{
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);



    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字

    //打字
    outtextxy(255, 250, _T("工号："));
    outtextxy(255, 350, _T("密码："));
    settextstyle(30, 0, _T("楷体"));
    outtextxy(185, 400, _T("(初始密码为0000)"));

    // 画按钮
    setlinecolor(WHITE);
    setfillcolor(RGB(201, 80, 80));
    fillrectangle(380, 450, 700, 550);
    settextstyle(100, 0, _T("楷体"));
    outtextxy(440, 450, _T("登录"));


    setlinecolor(BLACK);//黑框
    setfillcolor(WHITE);//白底
    fillrectangle(380, 250, 800, 300);//上方白框
    fillrectangle(380, 350, 800, 400);//下方白框

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 550, 900, 590);
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 550, _T("返回菜单"));

    MOUSEMSG msg;
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int t_num;
    char password[50];
    
    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                //输入工号
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 250 && msg.y <= 300)
                {
                    if (flag1 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 250, 800, 300);
                        flag1 = 0;
                    }
                    wchar_t a[6];
                    InputBox(a, 6, L"请输入工号", L"工号输入");
                    settextstyle(50, 0, _T("楷体"));
                    outtextxy(390, 250, a);
                    flag1++;

                    t_num = _wtoi(a);
                    continue;
                }
                //输入密码
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 350 && msg.y <= 400)
                {
                    if (flag2 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 350, 800, 400);
                        flag2 = 0;
                    }
                    wchar_t b[50];

                    InputBox(b, 50, L"请输入密码", L"密码输入");
                    settextstyle(50, 0, _T("楷体"));


                    int lenth = wcstombs(password, b, 512);
                    hide(lenth);
                    flag2++;


                    continue;
                }
                //返回菜单
                if (msg.x >= 750 && msg.x <= 950 && msg.y >= 550 && msg.y <= 590)
                {
                    menu();
                }
                //登录
                if ((flag1 == 1) && (flag2 == 1) && msg.x >= 380 && msg.x <= 700 && msg.y >= 450 && msg.y <= 550)
                {
                    FILE* fp = NULL;
                    fp = fopen("teacher_info.txt", "r+");
                    if (fp == NULL)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);//清
                        Sleep(300);
                        outtextxy(400, 600, _T("文件不存在！"));
                        Sleep(2000);
                        exit(0);
                    }
                    struct Teacher_Information* p;
                    p = find_t_num(t_num);
                    if ((p!=NULL)&&p->flag >= 5)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);//清
                        Sleep(300);
                        setfillcolor(RGB(1, 130, 198));
                        fillrectangle(750, 480, 900, 530);//覆盖修改密码按钮
                        settextstyle(50, 0, _T("楷体"));
                        outtextxy(200, 600, _T("账号已冻结！请联系教务处解冻！"));
                        continue;
                    }
                    if ((p != NULL) && (strcmp(p->password, password) == 0))
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        outtextxy(400, 600, _T("登录成功"));


                        if (strcmp(p->password, "0000") == 0)
                        {
                        tchchange1:wchar_t c[50];
                            char password_n[50];
                            InputBox(c, 50, L"检测到您的密码为初始密码！请输入新密码", L"请修改初始密码");
                            setlinecolor(BLACK);
                            setfillcolor(WHITE);
                            fillrectangle(380, 350, 800, 400);
                            int lenth = wcstombs(password_n, c, 128);
                            hide(lenth);

                            if (strcmp(password_n, p->password) == 0)
                            {
                                setlinecolor(RGB(1, 130, 198));//框
                                setfillcolor(RGB(1, 130, 198));//底
                                fillrectangle(0, 600, 1000, 650);
                                Sleep(300);
                                outtextxy(300, 600, _T("与原密码一致！请重新输入！"));
                                goto tchchange1;
                            }
                            else
                            {
                                wchar_t d[50];
                                char password_n1[50];
                                InputBox(d, 50, L"请再次输入新密码", L"请修改初始密码");
                                setlinecolor(BLACK);
                                setfillcolor(WHITE);
                                fillrectangle(380, 350, 800, 400);
                                int lenth1 = wcstombs(password_n1, d, 128);
                                hide(lenth1);
                                if (strcmp(password_n, password_n1) == 0)
                                {
                                    strcpy(p->password, password_n);
                                    setlinecolor(RGB(1, 130, 198));//框
                                    setfillcolor(RGB(1, 130, 198));//底
                                    fillrectangle(0, 600, 1000, 650);
                                    Sleep(300);
                                    outtextxy(300, 600, _T("修改成功！为您自动登录！"));
                                    tpreserve(p);
                                    Sleep(2000);
                                    return 1;//跳转到教师端
                                }
                                else
                                {
                                    setlinecolor(RGB(1, 130, 198));//框
                                    setfillcolor(RGB(1, 130, 198));//底
                                    fillrectangle(0, 600, 1000, 650);
                                    Sleep(300);
                                    outtextxy(300, 600, _T("两次输入不一致！请重新输入！"));

                                    goto tchchange1;
                                }

                            }
                        }
                        Sleep(2000);
                        return 1;
                    }
                    else//密码不对
                    {
                        if (p != NULL)
                        {
                            setlinecolor(RGB(1, 130, 198));//框
                            setfillcolor(RGB(1, 130, 198));//底
                            fillrectangle(0, 600, 1000, 650);
                            Sleep(300);
                            settextstyle(50, 0, _T("楷体"));
                            outtextxy(400, 600, _T("密码错误！"));
                            setlinecolor(WHITE);
                            setfillcolor(WHITE);
                            fillrectangle(750, 480, 900, 530);
                            settextstyle(35, 0, _T("楷体"));
                            outtextxy(755, 490, _T("找回密码"));
                            flag++;
                            p->flag = flag;
                            tpreserve(p);
                            continue;
                        }

                    }
                    fclose(fp);
                }
                if ((flag != 0 && flag<5) && (flag1 == 1) && (flag2 == 1) && msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                {
                    cleardevice();
                    putimage(0, 0, &background);
                    tchre(t_num);
                }
            }

        }
    }
}
int manager_login()
{
    cleardevice();
    IMAGE background;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);



    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字
    // 画按钮
    setlinecolor(WHITE);
    setfillcolor(RGB(201, 80, 80));
    fillrectangle(380, 450, 700, 550);
    settextstyle(100, 0, _T("楷体"));
    outtextxy(440, 450, _T("登录"));

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 480, 900, 530);
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 490, _T("修改密码"));

    setlinecolor(BLACK);//黑框
    setfillcolor(WHITE);//白底
    fillrectangle(380, 350, 800, 400);//下方白框
    settextstyle(50, 0, _T("楷体"));
    outtextxy(155, 350, _T("教务密码："));

    MOUSEMSG msg;
    int flag2 = 0;
    char password[50];

    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                //输入密码
                if (msg.x >= 380 && msg.x <= 800 && msg.y >= 350 && msg.y <= 400)
                {
                    if (flag2 == 1)
                    {
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillrectangle(380, 350, 800, 400);
                        flag2 = 0;
                    }
                    wchar_t b[50];

                    InputBox(b, 50, L"请输入密码", L"密码输入");
                    settextstyle(50, 0, _T("楷体"));


                    int lenth = wcstombs(password, b, 512);
                    hide(lenth);
                    flag2++;


                    continue;
                }

                //登录
                if ((flag2 == 1) && msg.x >= 380 && msg.x <= 700 && msg.y >= 450 && msg.y <= 550)
                {
                    FILE* fp = NULL;
                    fp = fopen("manager_info.txt", "r");
                    if (fp == NULL)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);//清
                        Sleep(300);
                        outtextxy(400, 600, _T("文件不存在！"));
                        Sleep(2000);
                        exit(0);
                    }
                    struct Manager_Information p;
                    fscanf(fp, "%s", p.password);
                    if (strcmp(password, p.password) == 0)
                    {
                        setlinecolor(RGB(1, 130, 198));//框
                        setfillcolor(RGB(1, 130, 198));//底
                        fillrectangle(0, 600, 1000, 650);
                        Sleep(300);
                        settextstyle(50, 0, _T("楷体"));
                        outtextxy(400, 600, _T("登录成功！"));
                        fclose(fp);
                        Sleep(1000);
                        return 1;
                    }
                    else//密码错误
                    {
                        if (p.password != 0)
                        {
                            setlinecolor(RGB(1, 130, 198));//框
                            setfillcolor(RGB(1, 130, 198));//底
                            fillrectangle(0, 600, 1000, 650);
                            Sleep(300);
                            settextstyle(50, 0, _T("楷体"));
                            outtextxy(200, 600, _T("密码错误！请输入正确的密码"));
                            continue;

                        }
                    }
                }
                //修改密码
                if (msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                {
                    cleardevice();
                    putimage(0, 0, &background);
                    
                    mngre();
                    return 1;
                }
            }
        }
    }
}

void stdre(int s_num)
{
    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字


    outtextxy(255, 250, _T("姓名："));
    outtextxy(155, 350, _T("身份证号："));
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(380, 250, 800, 300);//姓名
    fillrectangle(380, 350, 800, 400);//身份证号

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 480, 950, 530);//返回上一级
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 490, _T("返回上一级"));

    Student_Information* p = find_s_num(s_num);
    wchar_t a[50];
    wchar_t b[50];
    char name[50];
    char ID[50];
pri:InputBox(a, 50, L"请输入姓名", L"找回密码");
    setlocale(LC_ALL, "");     //转中文
    wcstombs(name, a, 512);
    setlocale(LC_ALL, "C");     //默认
    setlinecolor(BLACK);
    setfillcolor(WHITE);//覆盖旧输出
    fillrectangle(380, 250, 800, 300);//姓名
    outtextxy(390, 250, a);
    setlinecolor(RGB(1, 130, 198));//框
    setfillcolor(RGB(1, 130, 198));//底
    fillrectangle(0, 600, 1000, 650);//遮盖底部


    if (strcmp(p->student_name, name) != 0)
    {
        
        Sleep(300);
        outtextxy(400, 600, _T("姓名与学号不符！"));


        //setlinecolor(WHITE);
        //setfillcolor(WHITE);
        //fillrectangle(750, 480, 950, 530);//返回上一级
        //settextstyle(35, 0, _T("楷体"));
        //outtextxy(755, 490, _T("返回上一级"));

        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    //输入姓名
                    if (msg.x >= 380 && msg.x <= 800 && msg.y >= 250 && msg.y <= 300)
                    {
                        goto pri;
                    }
                    //返回上一级
                    if (msg.x >= 750 && msg.x <= 980 && msg.y >= 480 && msg.y <= 530)
                    {
                        student_login();
                    }
                }
            }
        }
    }
    pri1:InputBox(b, 50, L"请输入身份证号", L"找回密码");
    wcstombs(ID, b, 512);
    setlinecolor(BLACK);
    setfillcolor(WHITE);//覆盖旧输出
    fillrectangle(380, 350, 800, 400);
    outtextxy(390, 350, b);
    if (strcmp(p->ID, ID) == 0)
    {
        wchar_t c[50];
        mbstowcs(c, p->password, 256);
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);//遮盖底部
        Sleep(300);
        outtextxy(400, 600, _T("匹配成功！您的密码为："));
        outtextxy(400, 650, c);
        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                    {
                        student_login();
                    }
                }
            }
        }
    }
    if (strcmp(p->ID, ID) != 0)
    {
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);
        Sleep(300);
        outtextxy(400, 600, _T("身份证号输入错误！"));
        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    //输入身份证号
                    if (msg.x >= 380 && msg.x <= 800 && msg.y >= 350 && msg.y <= 400)
                    {
                        goto pri1;
                    }
                    if (msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                    {
                        student_login();
                    }
                }
            }
        }
    }
}
void tchre(int t_num)
{
    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字


    outtextxy(255, 250, _T("姓名："));
    outtextxy(155, 350, _T("身份证号："));
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(380, 250, 800, 300);//姓名
    fillrectangle(380, 350, 800, 400);//身份证号

    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle(750, 480, 950, 530);//返回上一级
    settextstyle(35, 0, _T("楷体"));
    outtextxy(755, 490, _T("返回上一级"));

    struct Teacher_Information* p = find_t_num(t_num);
    wchar_t a[50];
    wchar_t b[50];
    char name[50];
    char ID[50];
pri:InputBox(a, 50, L"请输入姓名", L"找回密码");
    setlocale(LC_ALL, "");     //转中文
    wcstombs(name, a, 512);
    setlocale(LC_ALL, "C");     //默认
    setlinecolor(BLACK);
    setfillcolor(WHITE);//覆盖旧输出
    fillrectangle(380, 250, 800, 300);//姓名
    outtextxy(390, 250, a);
    setlinecolor(RGB(1, 130, 198));//框
    setfillcolor(RGB(1, 130, 198));//底
    fillrectangle(0, 600, 1000, 650);//遮盖底部

    if (strcmp(p->teacher_name, name) != 0)
    {
        
        Sleep(500);
        outtextxy(400, 600, _T("姓名与工号不符！"));

        //setlinecolor(BLACK);
        //setfillcolor(WHITE);
        //fillrectangle(750, 480, 980, 530);//返回上一级
        //settextstyle(35, 0, _T("楷体"));
        //outtextxy(755, 490, _T("返回上一级"));
        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    //输入姓名
                    if (msg.x >= 380 && msg.x <= 800 && msg.y >= 250 && msg.y <= 300)
                    {
                        goto pri;
                    }
                    //返回上一级
                    if (msg.x >= 750 && msg.x <= 980 && msg.y >= 480 && msg.y <= 530)
                    {
                        teacher_login();
                    }
                }
            }
        }
    }
pri1:InputBox(b, 50, L"请输入身份证号", L"找回密码");
    wcstombs(ID, b, 512);

    setfillcolor(WHITE);//覆盖旧输出
    setlinecolor(BLACK);
    fillrectangle(380, 350, 800, 400);
    outtextxy(390, 350, b);
    if (strcmp(p->ID, ID) == 0)
    {
        wchar_t c[50];
        mbstowcs(c, p->password, 256);
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);//遮盖底部
        Sleep(300);
        outtextxy(400, 600, _T("匹配成功！您的密码为："));
        outtextxy(400, 650, c);
        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                    {
                        teacher_login();
                    }
                }
            }
        }
    }
    if (strcmp(p->ID, ID) != 0)
    {
        setlinecolor(RGB(1, 130, 198));//框
        setfillcolor(RGB(1, 130, 198));//底
        fillrectangle(0, 600, 1000, 650);
        Sleep(300);
        outtextxy(400, 600, _T("身份证号输入错误！"));
        MOUSEMSG msg;
        while (1)
        {
            if (MouseHit())
            {
                msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    //输入身份证号
                    if (msg.x >= 380 && msg.x <= 800 && msg.y >= 350 && msg.y <= 400)
                    {
                        goto pri1;
                    }
                    //返回上一级
                    if (msg.x >= 750 && msg.x <= 900 && msg.y >= 480 && msg.y <= 530)
                    {
                        teacher_login();
                    }
                }
            }
        }
    }
}
void mngre()
{
    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字


    outtextxy(55, 250, _T("请输入新密码："));
    outtextxy(155, 350, _T("确认密码："));
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(380, 250, 800, 300);//上方白框
    fillrectangle(380, 350, 800, 400);//下方白框


    FILE* fp;
    fp = fopen("manager_info.txt", "r");
    if (fp == NULL)
    {
        closegraph();
        printf("无法打开文件\n");
        exit(0); // 返回错误代码
    }
    struct Manager_Information p;
    fscanf(fp, "%s", p.password);
    fclose(fp);

    stdchange1:wchar_t c[50];
        char password_n[50];
        InputBox(c, 50, L"请输入新密码：", L"修改密码");
        setlinecolor(BLACK);
        setfillcolor(WHITE);
        fillrectangle(380, 350, 800, 400);
        int lenth = wcstombs(password_n, c, 128);
        hide1(lenth);

        if (strcmp(password_n, p.password) == 0)
        {
            setlinecolor(RGB(1, 130, 198));//框
            setfillcolor(RGB(1, 130, 198));//底
            fillrectangle(0, 600, 1000, 650);
            Sleep(300);
            outtextxy(300, 600, _T("与原密码一致！请重新输入！"));
            goto stdchange1;
        }
        else
        {
            wchar_t d[50];
            char password_n1[50];
            InputBox(d, 50, L"请再次输入新密码", L"修改密码");
            setlinecolor(BLACK);
            setfillcolor(WHITE);
            fillrectangle(380, 350, 800, 400);
            int lenth1 = wcstombs(password_n1, d, 128);
            hide(lenth1);

            if (strcmp(password_n, password_n1) == 0)
            {
                strcpy(p.password, password_n);
                FILE* fp1;
                fp1= fopen("manager_info.txt", "w");
                fprintf(fp1, "%s", p.password);
                setlinecolor(RGB(1, 130, 198));//框
                setfillcolor(RGB(1, 130, 198));//底
                fillrectangle(0, 600, 1000, 650);
                outtextxy(300, 600, _T("修改成功！为您自动登录！"));
                Sleep(2000);
                fclose(fp1);
                return;
            }
            else
            {
                setlinecolor(RGB(1, 130, 198));//框
                setfillcolor(RGB(1, 130, 198));//底
                fillrectangle(0, 600, 1000, 650);
                Sleep(300);
                outtextxy(300, 600, _T("两次输入不一致！请重新输入！"));

                goto stdchange1;
            }

        }
    
}

void tch_menu()
{
    cleardevice();

    //输出图片
    IMAGE background;//定义一个(变量)对象
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);

    // 画按钮
    setlinecolor(BLACK);
    setfillcolor(RGB(204, 229, 255));
    fillrectangle(200, 50, 450, 150);
    fillrectangle(200, 200, 450, 300);
    fillrectangle(200, 350, 450, 450);
    fillrectangle(200, 500, 450, 600);

    fillrectangle(650, 50, 900, 150);
    fillrectangle(650, 200, 900, 300);
    fillrectangle(650, 350, 900, 450);
    fillrectangle(650, 500, 900, 600);

    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字
    settextstyle(40, 0, _T("楷体"));

    outtextxy(205, 80, _T("录入学生成绩"));
    outtextxy(205, 230, _T("显示学生成绩"));
    outtextxy(205, 380, _T("增加学生成绩"));
    outtextxy(205, 530, _T("删除学生成绩"));

    outtextxy(655, 80, _T("修改学生成绩"));
    outtextxy(655, 230, _T("查询学生成绩"));
    outtextxy(700, 360, _T("查询学生"));
    outtextxy(700, 400, _T("绩点排名"));
    outtextxy(700, 530, _T("退出系统"));
    MOUSEMSG msg;
    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 50 && msg.y <= 150)
                {
                    //录入学生成绩
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 200 && msg.y <= 300)
                {
                    //显示学生成绩
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 350 && msg.y <= 450)
                {
                    //增加学生成绩 
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 500 && msg.y <= 600)
                {
                    //删除学生成绩
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 50 && msg.y <= 150)
                {
                    //修改学生成绩
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 200 && msg.y <= 300)
                {
                    //查询某学生成绩
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 350 && msg.y <= 450)
                {
                    //查询学生绩点排名
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 500 && msg.y <= 600)
                {
                    menu();
                    //退出系统
                }
            }
        }
    }
}
void mng_menu()
{
    cleardevice();

    //输出图片
    IMAGE background;//定义一个(变量)对象
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    putimage(0, 0, &background);

    // 画按钮
    setlinecolor(BLACK);
    setfillcolor(RGB(204, 229, 255));
    fillrectangle(200, 50, 450, 150);
    fillrectangle(200, 150, 450, 250);
    fillrectangle(200, 250, 450, 350);
    fillrectangle(200, 350, 450, 450);
    fillrectangle(200, 450, 450, 550);
    fillrectangle(200, 550, 450, 650);

    fillrectangle(650, 50, 900, 150);
    fillrectangle(650, 150, 900, 250);
    fillrectangle(650, 250, 900, 350);
    fillrectangle(650, 350, 900, 450);
    fillrectangle(650, 450, 900, 550);
    fillrectangle(650, 550, 900, 650);

    //设置文字样式
    settextstyle(50, 0, _T("楷体"));//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);//黑字
    settextstyle(40, 0, _T("楷体"));
    outtextxy(205, 80, _T("添加学生信息"));

    outtextxy(245, 160, _T("显示所有"));
    outtextxy(245,200, _T("学生信息"));

    outtextxy(245, 275, _T("添加课程"));

    outtextxy(245, 360, _T("显示所有"));
    outtextxy(245, 400, _T("课程信息"));

    outtextxy(205, 480, _T("添加老师信息"));
    outtextxy(205, 580, _T("显示老师信息"));

    outtextxy(700, 80, _T("解冻账号"));
    outtextxy(700, 180, _T("查询成绩"));
    outtextxy(700, 280, _T("删除成绩"));
    outtextxy(700, 380, _T("更改成绩"));
    outtextxy(700, 480, _T("成绩统计"));
    outtextxy(655, 580, _T("退出教务系统"));
    MOUSEMSG msg;
    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 50 && msg.y <= 150)
                {
                    //添加学生信息
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 150 && msg.y <= 250)
                {
                    //显示所有学生信息
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 250 && msg.y <= 350)
                {
                    //添加课程
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 350 && msg.y <= 450)
                {
                    //显示所有课程信息
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 450 && msg.y <= 550)
                {
                    //添加老师信息
                }
                if (msg.x >= 200 && msg.x <= 450 && msg.y >= 550 && msg.y <= 650)
                {
                    //显示老师信息
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 50 && msg.y <= 150)
                {
                    unfreeze();
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 150 && msg.y <= 250)
                {
                    //查询成绩
                    
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 250 && msg.y <= 350)
                {
                    //删除成绩
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 350 && msg.y <= 450)
                {
                    
                    //更改成绩
                    
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 450 && msg.y <= 550)
                {
                    //成绩统计
                }
                if (msg.x >= 650 && msg.x <= 900 && msg.y >= 550 && msg.y <= 650)
                {
                    menu();
                }
            }
        }
    }
}


int menu()
{
    cleardevice();

    //输出图片
    IMAGE background;//定义一个(变量)对象
    IMAGE student;
    IMAGE teacher;
    IMAGE eas;
    loadimage(&background, _T("./jd-xq.jpg"), 1080, 722);
    loadimage(&student, _T("./student.png"), 190, 190);
    loadimage(&teacher, _T("./teacher.png"), 190, 190);
    loadimage(&eas, _T("./eas.png"), 190, 190);
    putimage(0, 0, &background);
    putimage(100, 520, &student);
    putimage(450, 520, &teacher);
    putimage(800, 520, &eas);

    MOUSEMSG msg;
    while (1)
    {
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (msg.x >= 100 && msg.x <= 290 && msg.y >= 520 && msg.y <= 710)
                {
                    student_login();
                    return 1;//跳转到学生端
                }
                if (msg.x >= 450 && msg.x <= 640 && msg.y >= 520 && msg.y <= 710)
                {
                    teacher_login();
                    tch_menu();
                    
                    return 2;
                    //跳转到教师端
                }
                if (msg.x >= 800 && msg.x <= 990 && msg.y >= 520 && msg.y <= 710)
                {
                    

                    check();//第一次登入->执行注册 不是第一次登录->直接返回
                    int i=manager_login();
                    
                    //跳转到教务端
                    return 3;
                }

            }
        }
    }
    
}

