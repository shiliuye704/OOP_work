#include <iostream>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

public:
    void Init(int y, int m, int d) {
        year = y;
        month = m;
        day = d;
    }

    void setYear(int y) { year = y; }
    void setMonth(int m) { month = m; }
    void setDay(int d) { day = d; }

    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }

    void display() {
        cout << "当前日期为："
             << year << "年" << month << "月" << day << "日" << endl;
    }

    int calWeekday() {
        int y = year, m = month, d = day;
        if (m == 1 || m == 2) { m += 12; y -= 1; }
        return (d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1) % 7;
    }
};

int main() {
    Date dt;
    int y, m, d;

    cout << "请输入年份：";
    cin >> y;
    cout << "请输入月份：";
    cin >> m;
    cout << "请输入日期：";
    cin >> d;

    dt.Init(y, m, d);

    dt.display();

    int w = dt.calWeekday();
    cout << "星期数(0=周日,6=周六)： " << w << endl;

    return 0;
}
