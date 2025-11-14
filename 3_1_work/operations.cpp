/************************************************************
 * 文件名称：card_operations.cpp
 * 文件说明：校园一卡通系统功能模块实现文件
 * 模块功能：实现账户管理、动态内存、异常处理、报表输出等逻辑
 ************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

 // 文件输入流头文件
#include <fstream> 

#include "operations.h"

using namespace std;

//============================================================
//                全局常量定义
//============================================================


const double FEE_RATE = 0.02;          // 充值手续费率
const double WARNING_BALANCE = 10.0;   // 低余额警戒值


//============================================================
//             命名空间：用于输出辅助
//============================================================
namespace card
{
    // 打印分隔线
    void printLine(char c = '-', int len = 60)
    {
        for (int i = 0; i < len; ++i)
        {
            cout << c;
        }
        cout << endl;
    }

    // 打印标题
    void title(const string& s)
    {
        cout << "\n==== " << s << " ====\n";
    }
}

//============================================================
//                模块一：动态内存管理
//============================================================
Card* createCards(int n)
{
    try
    {
        return new Card[n];
    }
    catch (const bad_alloc& e)
    {
        cerr << "内存分配失败：" << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void destroyCards(Card* p)
{
    if (p != nullptr)
        delete[] p;
}

//============================================================
//             模块二：账户信息录入（含输入异常处理）
//============================================================
//方式一:手动录入学生校园卡信息
void inputCards(Card* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << "请输入学号、姓名和初始余额：";
        try
        {
            cin >> arr[i].id >> arr[i].name >> arr[i].balance;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("输入格式错误，请输入正确的数据类型。");
            }

            if (arr[i].balance < 0)
            {
                throw invalid_argument("初始余额不能为负数！");
            }

            arr[i].transactions = 0;
        }
        catch (const exception& e)
        {
            cout << "输入异常：" << e.what() << endl;
            i--;  // 重新输入当前账户
        }
    }
}

//方式二:从文件读取学生校园卡信息(#include <fstream>带上文件输入流头文件)
void  inputCards(Card* arr, int n, const string& filename)
{
    //1. 通过文件输入流ifstream打开名为"filename"的文件
    ifstream fin(filename);//fin对象定向到filename
    if (!fin.is_open())
    {
        throw runtime_error("无法打开文件：" + filename);
    }

    // 2. 读取学生卡信息
    int count = 0;
    while (count < n && fin >> arr[count].id >> arr[count].name >> arr[count].balance)
    {
        if (arr[count].balance < 0)
        {
            throw invalid_argument("文件中存在非法余额（负数）数据！");
        }
        arr[count].transactions = 0;
        count++;
    }

    //检查录入数据是否完整(n个学生)
    if (count < n)
    {
        throw invalid_argument("文件数据不足，无法完成账户录入。");
    }

    fin.close();
    cout << "已成功从文件读取 " << count << " 条校园卡信息。" << endl;
}

//辅助函数:读取文件的行数(学生的数量)
int countLines(const string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw runtime_error("无法打开文件：" + filename);
    }

    int count = 0;
    string line;

    // 逐行读取
    while (getline(fin, line))
    {
        // 去除空白行判断
        if (!line.empty() && line.find_first_not_of(" \t\r\n") != string::npos)
        {
            count++;
        }
    }

    fin.close();
    return count;
}

//============================================================
//                模块三：账户业务操作
//============================================================

// 充值函数（默认形参函数定义,声明带数值,定义无需带形参值）
void deposit(Card& c, double amount, double fee)
{
    //c.balance += amount * (1.0 - fee);
    //c.transactions++;
    if (amount < 0)
    {
        throw invalid_argument("充值金额不能为负数！");
    }
    if (fee < 0 || fee >= 1)
    {
        throw invalid_argument("手续费率必须在0~1之间！");
    }

    c.balance += amount * (1.0 - fee);
    c.transactions++;
}

// 消费函数（带异常处理）
bool spend(Card& c, double cost, const string& item)
{
    cout << "消费项目：" << item << endl;

    try
    {
        if (cost < 0)
        {
            throw invalid_argument("消费金额不能为负数！");
        }

        if (c.balance < cost)
        {
            throw runtime_error("余额不足，消费失败！");
        }
        c.balance -= cost;
        c.transactions++;

        return true;
    }
    catch (const exception& e)
    {
        cout << "异常提示：" << e.what() << endl;
        return false;
    }
}

//============================================================
//                 模块四：账户访问操作
//============================================================

// 使用常引用显示账户余额
void showBalance(const Card& c)
{
    cout << c.name << " 当前余额为：" << c.balance << endl;
}

// 使用指向常量的指针访问账户ID
void viewStudentID(const Card* p)
{
    cout << "账户ID为：" << p->id << endl;
}

//============================================================
//                模块五：工具与输出
//============================================================

// 强制类型转换（元→分）
int toCent(double amount)
{
    return static_cast<int>(amount * 100);
}

// 报表输出
void printReport(const Card* arr, int n)
{
    //1. 按需导入命名空间里的函数
    using card::printLine;
    printLine('=');//调用带有默认参数值的函数

    //2. 按照指定格式输出"表头"的信息
    cout << left << setw(8) << "ID"
        << setw(12) << "Name"
        << right << setw(14) << "Balance"
        << setw(14) << "Transactions" << endl;

    printLine('-');

    cout.setf(ios::fixed);//设置浮点数输出格式为定点格式
    cout << setprecision(2);//将小数点后保留2位

    //3. 按照指定格式输出"表中"学生卡信息
    for (int i = 0; i < n; ++i)
    {
        cout << left << setw(8) << arr[i].id
            << setw(12) << arr[i].name
            << right << setw(14) << arr[i].balance
            << setw(14) << arr[i].transactions << endl;
    }
    printLine('=');
}
