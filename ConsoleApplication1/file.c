#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include"struct.h"
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"file.h"

//链表存文件
void savefile_s(struct Student_Information* head)
{
	FILE* fp = fopen("student_info.txt", "r+");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return;
	}

	struct Student_Information* q = head;
	while (q != NULL)
	{
		fprintf(fp, "%s %d %s %s %s %s %d %d %d %f %f\n", q->student_name, q->s_num, q->password, q->ID, q->college, q->major, q->s_class, q->year, q->change, q->total_gpa, q->total_credit);
		q = q->next;
	}
	fclose(fp);
	//释放链表内存
	struct Student_Information* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
void savefile_g(struct Grade* head)
{
	FILE* fp = fopen("grade_info.txt", "r+");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return;
	}

	struct Grade* q = head;
	while (q != NULL)
	{
		fprintf(fp, "%s %d %d %f %f %f %d %d %d %d\n", q->subject, q->c_num, q->term, q->grade1, q->grade2, q->credit, q->selective, q->s_num, q->t_num, q->s_class);
		q = q->next;
	}
	fclose(fp);
	//释放链表内存
	struct Grade* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
//读入文件并创建链表（学生信息）
struct Student_Information* create_linklist_s()
{
	struct Student_Information* head = NULL;
	FILE* fp = fopen("student_info.txt", "r");
	struct Student_Information* p = head;
	if (fp  == NULL)
	{
		printf("打开失败\n");
		return NULL;
	}
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
//读入文件并创建链表（成绩情况）
struct Grade* create_linklist_g()
{
	struct Grade* head = (struct Grade*)malloc(sizeof(struct Grade));
	FILE* fp;
	struct Grade* p = head;
	if ((fp = fopen("grade_info.txt", "r")) == NULL)
	{
		printf("打开失败\n");
		return NULL;
	}
	while (1)
	{
		struct Grade* q;
		q=(struct Grade*)malloc(sizeof(struct Grade));
		if (q == NULL) // 检查内存分配是否成功  
		{
			perror("内存分配失败");
			fclose(fp);
			// 释放已分配的内存（如果有的话）  
			while (head != NULL)
			{
				struct Grade* temp = head;
				head = head->next;
				free(temp);
			}
			return NULL;
		}
		int nRead = fscanf(fp, "%99s%d%d%f%f%f%d%d%d%d",q->subject,&q->c_num,&q->term,&q->grade1,&q->grade2,&q->credit,&q->selective,&q->s_num,&q->t_num,&q->s_class );
		if (nRead != 10) // 检查是否成功读取了所有字段  
		{
			if (feof(fp)) // 如果到达文件末尾，则退出循环  
				break;
			else // 否则，读取失败，释放q的内存并打印错误  
			{
				free(q);
				printf("读取文件时发生错误\n");
				break;
			}
		}
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


//链表排序
struct Grade* BubbleSort_term(struct Grade* head)
{
	int swapped;
	struct Grade* p;
	struct Grade* q;
	struct Grade* tmp;
	do {
		swapped = 0; // 用于标记是否发生了交换  
		p = head; 

		// 内层循环控制每一趟排序的过程  
		while (p != NULL && p->next != NULL) {
			q = p->next; 

			
			if (p->term > q->term) {
				tmp = p->next; 
				p->next = q->next; 
				q->next = p;  
				if (p == head) 
				{
					// 如果 p 是头节点，更新头节点  
					head = q;
				}
				else 
				{
					// 否则找到 p 的前一个节点，更新它的 next 指针  
					while (tmp != q) {
						tmp = tmp->next;
					}
					tmp->next = q;
				}
				swapped = 1; // 标记发生了交换  
			}
			else 
			{
				p = p->next; // 如果没有交换，继续向后遍历  
			}
		}
	} while (swapped); // 如果在内层循环中没有发生交换，则排序完成  


	
	return head;
}
struct Student_Information* BubbleSort_gpa(struct Student_Information* head)//将传入参数改为链表头指针
{
	int swapped;
	struct Student_Information* p;
	struct Student_Information* q;
	struct Student_Information* tmp;
	do {
		swapped = 0; // 用于标记是否发生了交换  
		p = head; // 从头节点开始  

		// 内层循环控制每一趟排序的过程  
		while (p != NULL && p->next != NULL) {
			q = p->next; // q 指向 p 的下一个节点  

			// 如果前一个节点的 term 大于后一个节点的 term，则交换它们  
			if (p->total_gpa > q->total_gpa) {
				tmp = p->next; // 保存 p 的下一个节点  
				p->next = q->next; // p 跳过 q 指向 q 的下一个节点  
				q->next = p; // q 指向 p，完成交换  
				if (p == head) {
					// 如果 p 是头节点，更新头节点  
					head = q;
				}
				else {
					// 否则找到 p 的前一个节点，更新它的 next 指针  
					while (tmp != q) {
						tmp = tmp->next;
					}
					tmp->next = q;
				}
				swapped = 1; // 标记发生了交换  
			}
			else {
				p = p->next; // 如果没有交换，继续向后遍历  
			}
		}
	} while (swapped); // 如果在内层循环中没有发生交换，则排序完成  

}
//按学号查找
void find_node_s_num(struct Grade* head,int a)
{
	
	struct Grade* p= head;
	struct Grade* head_small;
	struct Grade* tail_small ;
	head_small = tail_small = NULL;

	while (p!=NULL)
	{
		if (p->s_num== a)
		{
			
			//所有学号符合要求的新建链表 排序后输出
			struct Grade* q = (struct Grade*)malloc(sizeof(struct Grade));

			strcpy(q->subject, p->subject);
			q->c_num = p->c_num;
			q->term = p->term;
			q->grade1 = p->grade1;
			q->grade2 = p->grade2;
			q->credit = p->credit;
			q->selective = p->selective;
			q->s_num=a;
			q->t_num =p->t_num;
			q->s_class = p->s_class;
			q->next = NULL;

			if (head_small == NULL)
			{
				head_small = tail_small = q;
			}
			else
			{
				tail_small->next = q;
				tail_small = q;
			}
			
			//新建链表函数
		}
		p = p->next;

	}
	struct Grade* g;
	g=BubbleSort_term(head_small);
	//链表输出
	if (g != NULL)
	{
		while (g != NULL)
		{
			printf("科目名称：%s\n课程编号：%d\n学期：%d\n分数（百分制）：%.1f\n绩点：%.2f\n学分：%.1f\n课程性质：%d\n学号：%d\n教师号：%d\n班级：%d\n\n", g->subject, g->c_num, g->term, g->grade1, g->grade2, g->credit, g->selective, g->s_num, g->t_num, g->s_class);
			g = g->next;
		}

	}
	else
	{
		printf(" 未找到符合条件的信息\n");
	}
	
}

//按姓名查找
void find_node_s_name(struct Grade* g_head, struct Student_Information* s_head, char a[])
{
	int flag = 0;
	struct Student_Information* p = s_head;
	while (p!=NULL)
	{
		if ((strcmp(p->student_name, a)) == 0)
		{
			find_node_s_num(g_head, p->s_num);
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf(" 未找到符合条件的信息\n");
	}
	return;
}

//按专业查找
void find_node_major(struct Grade* g_head, struct Student_Information* s_head, char a[])
{
	int flag = 0;
	struct Student_Information* p = s_head;
	while (p != NULL)
	{
		if (strcmp(p->major, a) == 0)
		{
			flag++;
			find_node_s_num(g_head, p->s_num);
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf(" 未找到符合条件的信息\n");
	}
	return;
}

//按学期查询
void find_node_term(struct Grade* head, int a)
{

	struct Grade* p = head;
	struct Grade* head_small;
	struct Grade* tail_small;
	head_small = tail_small = NULL;

	while (p != NULL)
	{
		if (p->term== a)
		{

			//所有学期符合要求的新建链表 排序后输出
			struct Grade* q = (struct Grade*)malloc(sizeof(struct Grade));

			q->credit = p->credit;
			q->c_num = p->c_num;
			q->grade1 = p->grade1;
			q->grade2 = p->grade2;
			q->selective = p->selective;
			strcpy(q->subject, p->subject);
			q->s_num=p->s_num;
			q->term = a;
			q->t_num = p->t_num;
			q->s_class = p->s_class;
			q->next = NULL;

			if (head_small == NULL)
			{
				head_small = tail_small = q;
			}
			else
			{
				tail_small->next = q;
				tail_small = q;
			}

			//新建链表函数 返回头指针head1
		}
		p = p->next;

	}
	struct Grade* g;
	g = BubbleSort_term(head_small);
	//链表输出
	if (g != NULL)
	{
		while (g != NULL)
		{
			printf("科目名称：%s\n课程编号：%d\n学期：%d\n分数（百分制）：%f\n绩点：%f\n学分：%f\n课程性质：%d\n学号：%d\n教师号：%d\n班级：%d\n\n", g->subject, g->c_num, g->term, g->grade1, g->grade2, g->credit, g->selective, g->s_num, g->t_num, g->s_class);
			g = g->next;
		}

	}
	else
	{
		printf(" 未找到符合条件的信息\n");
	}
	
}

//显示某指定科目最高成绩、最低成绩、平均成绩以及及格率、优秀率计算
void statistics(struct Grade* head,int term,int s_class,char subject_name[], int t_num)
{
	struct Grade* p = head;
	float pass_percentage=0;
	float pass_person = 0;
	float great_percentage = 0;
	float great_person = 0;
	float max_grade1 = 0;
	float min_grade1 = 100;
	float sum_grade1 = 0;
	float average_grade = 0;
	int total_person = 0;
	while (p!=NULL)
	{
		if ((p->term == term) && (p->s_class == s_class) 
			&& (strcmp(p->subject, subject_name) == 0) && p->t_num==t_num)
		{
			if (p->grade1 >= 60)
			{
				pass_person++;
			}
			if (p->grade1 >= 85)
			{
				great_person++;
			}
			if (p->grade1 > max_grade1)
			{
				max_grade1 = p->grade1;
			}
			if (p->grade1 < min_grade1)
			{
				min_grade1 = p->grade1;
			}
			sum_grade1 = sum_grade1 + p->grade1;
			total_person++;
		}
		p = p->next;
		
	}
	pass_percentage = pass_person / total_person;
	great_percentage = great_person /total_person;
	average_grade = sum_grade1 / total_person;
	printf("最高成绩为：%f", max_grade1);
	printf("最低成绩为：%f", min_grade1);
	printf("平均成绩为：%2f", average_grade);
	printf("优秀率为：%4f", great_percentage);
	printf("及格率为：%4f", pass_percentage);
}

//限制读入八位数字
void scannum8(int* num) {
	fflush(stdin);
	char ch;
	int i = 0;
	int t;
	int Num = 0;
	int flag = 0;
	ch = getchar();
	if (ch == '\n') {
		printf("\n错误：过早输入回车！（格式为八位数字，例：21230102）\n");
		printf("\t\t按任意键重新输入！\n");
		_getch();
		scannum8(num);
		return;
	}
	while (ch != '\n') {
		i++;
		if (i <= 8) {
			if (ch >= '0' && ch <= '9') {
				t = ch - '0';
				switch (i) {
				case 1: t = t * 10000000; break;
				case 2: t = t * 1000000; break;
				case 3: t = t * 100000; break;
				case 4: t = t * 10000; break;
				case 5: t = t * 1000; break;
				case 6: t = t * 100; break;
				case 7: t = t * 10; break;
				default:
					break;
				}
				Num = Num + t;
			}
			else {
				printf("\n错误：请勿输入非法字符！（格式为八位数字，例：21230101）\n");
				printf("\t\t按任意键重新输入！\n");
				_getch();
				scannum8(num);
				return;
			}
		}
		ch = getchar();
	}
	if (i < 8) {
		printf("\n错误：输入过短！（格式为八位数字，例：21230101）\n");
		printf("\t\t按任意键重新输入！\n");
		_getch();
		scannum8(num);
		return;
	}
	if (i > 8) {
		printf("\n错误：输入过长！（格式为八位数字，例：21230101）\n");
		printf("\t\t按任意键重新输入！\n");
		_getch();
		scannum8(num);
		return;
	}

	*num = Num;
	fflush(stdin);
	return;
}

// 限制读入1-8的单个数字
void scannum(int* num) {
	fflush(stdin);
	char ch;
	int i = 0;
	int t;
	int Num = 0;
	int flag = 0;
	ch = getchar();
	if (ch == '\n') {
		printf("\t\t错误：过早输入回车！（格式为1-8的单个数字，例：2）\n");
		printf("\t\t按任意键重新输入！\n");
		_getch();
		scannum(num);
		return;
	}
	while (ch != '\n') {
		i++;
		if (i <= 1) {
			if (ch >= '0' && ch <= '8') {
				t = ch - '0';
				Num = Num + t;
			}
			else {
				printf("\t\t错误：请勿输入非法字符！（格式为1-8的单个数字，例：2）\n");
				printf("\t\t按任意键重新输入！\n");
				_getch();
				scannum(num);
				return;
			}
		}
		ch = getchar();
	}
	if (i > 1) {
		printf("\t\t错误：输入过长！（格式为1-8的单个数字，例：2）\n");
		printf("\t\t按任意键重新输入！\n");
		_getch();
		scannum(num);
		return;
	}

	*num = Num;
	fflush(stdin);
	return;
}


//删除对应学号的成绩记录
struct Grade* delete_g_snum(struct Grade* head, int delete_s_num)
{
	
	struct Grade* p = head;//遍历指针
	struct Grade* q = NULL;//p前指针，防止要删除的节点为尾节点
	// 处理头节点需要被删除的情况  
	while (p != NULL && p->s_num == delete_s_num)
	{
		struct Grade* temp = p;
		head = p->next;
		free(temp);
		printf("删除成功\n");
		p = head;

		if (head == NULL) break;
		// 否则继续查找下一个可能的头节点需要删除的情况  
	}

	// 遍历剩余的链表节点  
	q = head;
	while (q != NULL)
	{
		p = q->next;  // 移至下一个节点  
		while (p != NULL && p->s_num == delete_s_num)
		{
			struct Grade* temp = p;
			q->next = p->next;
			free(temp);
			printf("删除成功\n");
			p = q->next;  // 更新p为q的下一个节点  
		}
		if (p == NULL) break;  // 如果已经到链表末尾，则退出循环  
		q = p;  // 否则，更新q为当前节点p  
	}

	return head;
}
//删除对应学号的学生信息
struct Student_Information* delete_si_snum(struct Student_Information* head, int delete_s_num)
{
	struct Student_Information* p = head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if (p->s_num == delete_s_num)
		{
			if (p->next == NULL)
			{
				q->next = NULL;
				printf("删除成功\n");
				return head;
			}
			else
			{
				q->next = p->next;
				printf("删除成功\n");
				return head;
			}
		}
	}
	printf("未找到符合条件的成绩记录");
	return head;
}

//删除对应姓名的成绩记录
struct Grade* delete_g_sname(struct Grade* head,struct Student_Information*s_head,char delete_sname[])
{
	struct Student_Information* p = s_head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if (p!=NULL&&(strcmp(q->student_name, delete_sname))==0)
		{
			delete_g_snum(head,q->s_num);
		}
	}
	return head;
	
}
//删除对应姓名的学生信息
struct Student_Information* delete_si_sname(struct Grade* head, struct Student_Information* s_head, char delete_sname[])
{
	struct Student_Information* p = s_head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if ((strcmp(p->student_name, delete_sname)) == 0)
		{
			delete_si_snum(s_head, p->s_num);
		}
	}
	return s_head;

}

//删除对应专业的成绩记录
struct Grade* delete_g_major(struct Grade* head, struct Student_Information* s_head, char delete_major[])
{
	struct Student_Information* p = s_head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if ((strcmp(p->major, delete_major))==0)
		{
			delete_g_snum(head, p->s_num);
		}
	}
	return head;

}
//删除对应专业的学生信息
struct Grade* delete_si_major(struct Grade* head, struct Student_Information* s_head, char delete_major[])
{
	struct Student_Information* p = s_head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if ((strcmp(p->major, delete_major)) == 0)
		{
			delete_si_snum(head, p->s_num);
		}
	}
	return head;

}

//根据学号更改成绩
struct Grade* change_node_snum(struct Grade* head, int change_s_num)
{
	struct Grade* p = head;//遍历指针
	while (p != NULL)
	{

		if (p->s_num == change_s_num)
		{
			printf("科目名称：%s\n课程编号：%d\n学期：%d\n分数（百分制）：%f\n绩点：%f\n学分：%f\n课程性质：%d\n学号：%d\n教师号：%d\n班级：%d\n", p->subject, p->c_num, p->term, p->grade1, p->grade2, p->credit, p->selective, p->s_num, p->t_num, p->s_class);
			int i;
			char subject[100];//科目名称(考试科目)
			int c_num;//课程编号
			int term;//学期
			float grade1;//分数（百分制）
			float grade2;//绩点（4分制）
			float credit;//学分
			int selective;//（0为必选，1为选修，2为限选）
			int s_num;//学号
			int t_num;//教师号
			int s_class;//班级
			printf("要修改的内容为：1.科目名称 2.课程编号 3.学期 4.分数 5.绩点 6.学分 7.课程性质 8.学号 9.教师号 10.班级\n");
			fflush(stdin);
			char choice1;
			char choice2;
			char choice3;
			choice3 = '\n';
			while ((choice1 = getchar()) == '\n' || choice1 == EOF);
			while ((choice2 = getchar()) != '\n' && choice2 != EOF)
			{
				choice3 = choice2;
			}
			printf("this choice is%c%c\n", choice1, choice3);
			switch (choice1)
			{
			case '1':
				switch (choice3)
				{
				case '\n':
					printf("请输入新的数据");
					scanf("%s", subject);
					strcpy(p->subject, subject);
					return head;
				case '0':
					printf("请输入新的数据");
					scanf("%d", &s_class);
					p->s_class = s_class;
					return head;
				default:
					printf("无效选择\n");
				}
			case'2':
				printf("请输入新的数据");
				scanf("%d", &c_num);
				p->c_num = c_num;
				return head;
			case '3':
				printf("请输入新的数据");
				scannum(&term);
				p->term = term;
				return head;
			case '4':
				printf("请输入新的数据");
				scanf("%f", &grade1);
				p->grade1 = grade1;
				return head;
			case '5':
				printf("请输入新的数据");
				scanf("%f", &grade2);
				p->grade2 = grade2;
				return head;
			case '6':
				printf("请输入新的数据");
				scanf("%f", &credit);
				p->credit = credit;
				return head;
			case '7':
				printf("请输入新的数据");
				scanf("%d", &selective);
				p->selective = selective;
				return head;
			case '8':
				printf("请输入新的数据");
				scanf("%d", &s_num);
				p->s_num = s_num;
				return head;
			case '9':
				printf("请输入新的数据");
				scanf("%d", &t_num);
				p->t_num = t_num;
				return head;
			default:
				printf("无效选择\n");
			}


		}
		p = p->next;
	}
	printf("未找到符合条件的成绩记录");
	return head;
}
//根据姓名更改成绩
struct Grade* change_node_sname(struct Grade* head, struct Student_Information* s_head, char change_sname[])
{
	struct Student_Information* p = s_head;//遍历指针
	struct Student_Information* q = NULL;//p前指针，防止要删除的节点为尾节点
	while (p != NULL)
	{
		q = p;
		p = p->next;
		if ((strcmp(p->student_name, change_sname))==0)
		{
			change_node_snum(head, p->s_num);
		}
	}
	return head;
}
