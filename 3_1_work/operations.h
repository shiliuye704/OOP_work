#pragma once
/************************************************************
 * 文件名称：operations.h
 * 文件说明：校园一卡通系统功能模块头文件
 * 模块作用：声明账户操作、输入输出、异常处理等函数接口
 ************************************************************/

#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

#include <string>
using namespace std;

//============================================================
//              学生卡账户结构体定义(重要)
//============================================================
struct Card
{
	int    id;            // 学号
	string name;          // 姓名
	double balance;       // 当前余额
	int    transactions;  // 交易次数
};
//============================================================
//             校园卡功能模块声明
//============================================================

// 动态内存管理模块
Card* createCards(int n);             // 动态创建账户数组
void  destroyCards(Card* p);          // 释放账户数组内存

// 账户信息输入模块(集体录入卡号信息)

void  inputCards(Card* arr, int n);// 方式一：键盘输入（原版）
void  inputCards(Card* arr, int n, const string& filename);// 方式二：从文本文件读取（重载）
int countLines(const string& filename);//统计文件的行数

// 账户业务操作模块(存钱,消费)
void  deposit(Card& c, double amount, double fee = 0.02);   // 充值
bool  spend(Card& c, double cost, const string& item);      // 消费（含异常处理）

// 数据访问模块
void  showBalance(const Card& c);     // 使用常引用显示余额
void  viewStudentID(const Card* p);   // 使用指向常量的指针访问学号

// 工具功能模块
int   toCent(double amount);          // 强制类型转换：元→分
void  printReport(const Card* arr, int n);  // 报表输出

#endif
