#ifndef STRUCT_H
#define STRUCT_H

#include<stdbool.h>
struct Grade//成绩情况
{
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
	struct Grade* next;
};

struct course
{
	char subject[100];//学科名称
	int c_num;//课程编号
	float credit;//学分
	struct course *next;
};


struct Student_Information//学生信息
{
	char student_name[24];//姓名1
	int s_num;//学号1
	char password[50];
	char ID[30];//身份证号
	char college[50];//学院1
	char major[50];//专业1
	int s_class;//班级
	int year;//年级1
	int change;//是否转专业（0为不转，1为转）1
	float total_gpa;
	float total_credit;
	struct Student_Information* next;
};




struct Teacher_Information//教师信息
{
	char teacher_name[24];//教师名字
	int t_num;//教师编号
	char password[50];//密码
	char ID[30];//身份证号
	char college[50];//学院
	struct Teacher_Information* next;
	int flag;//最大输入次数
}; 

struct Manager_Information
{
	char password[50];
	struct Manager_Information* next;
};

#endif
