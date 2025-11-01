#ifndef FILE_H
#define FILE_H
#include "struct.h"
//链表存文件
void savefile_s(struct Student_Information* head);
void savefile_g(struct Grade* head);

//读入文件并创建链表（学生信息）
struct Student_Information* create_linklist_s();
//读入文件并创建链表（成绩情况）
struct Grade* create_linklist_g();

//链表排序
struct Grade* BubbleSort_term(struct Grade* head);
struct Student_Information* BubbleSort_gpa(struct Student_Information* head);
//按学号查找
void find_node_s_num(struct Grade* head, int a);
//按姓名查找
void find_node_s_name(struct Grade* g_head, struct Student_Information* s_head, char a[]);
//按专业查找
void find_node_major(struct Grade* g_head, struct Student_Information* s_head, char a[]);
//按学期查询
void find_node_term(struct Grade* head, int a);
//显示某指定科目最高成绩、最低成绩、平均成绩以及及格率、优秀率计算
void statistics(struct Grade* head, int term, int s_class, char subject_name[], int t_num);
//限制读入八位数字
void scannum8(int* num);
// 限制读入1-8单个数字
void scannum(int* num);
//删除对应学号的成绩记录
struct Grade* delete_g_snum(struct Grade* head, int delete_s_num);
//删除对应姓名的成绩记录
struct Grade* delete_g_sname(struct Grade* head, struct Student_Information* s_head, char delete_sname[]);
//删除对应专业的成绩记录
struct Grade* delete_g_major(struct Grade* head, struct Student_Information* s_head, char delete_major[]);
//根据学号更改成绩
struct Grade* change_node_snum(struct Grade* head, int change_s_num);
//根据姓名更改成绩
struct Grade* change_node_sname(struct Grade* head, struct Student_Information* s_head, char change_sname[]);
#endif