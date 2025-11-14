/*************************************************
** 功能 : 模拟校园一卡通消费管理系统
** 作者 : Qingke Zhang
** 版本 : 2025-11-6
/**************************************************/
#include <iostream>
#include <stdexcept>
#include "operations.h"
using namespace std;

/*----------------------------------*
            主函数
*-----------------------------------*/
int main()
{
    try
    {
        cout << "==== 校园卡管理系统(Campus Card System) ====" << endl;

        int n;
        Card* users;

        //录入账号信息(卡号,姓名,余额)
        char choice;
        cout << "是否从文件导入数据？(y/n)：";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            string filename = "cards.txt";
            n = countLines(filename);  // 自动统计学生数量
            cout << "检测到文件中共有 " << n << " 位学生记录。" << endl;
            users = createCards(n);
            inputCards(users, n, filename);  // 从文件中读取账户信息
        }
        else
        {
            cout << "请输入学生数量：";
            if (!(cin >> n) || n <= 0)
            {
                cerr << "输入无效，必须为整数！" << endl;
                return 1;
            }

            // 创建校园卡账户(n个学生)
            users = createCards(n);

            inputCards(users, n);              // 键盘录入方式
        }


        // 模拟业务操作
        deposit(users[0], 100.0, 0.0);
        spend(users[0], 8.5, "食堂午餐");

        // 常引用与指针访问
        showBalance(users[0]);
        viewStudentID(&users[0]);

        // 强制类型转换演示
        cout << "余额换算（分）：" << toCent(users[0].balance) << endl;

        // 输出账户报表
        printReport(users, n);

        // 释放内存
        destroyCards(users);
    }
    catch (const exception& e)
    {
        cerr << "程序运行时发生异常：" << e.what() << endl;
    }


    system("pause");
    return 0;
}
