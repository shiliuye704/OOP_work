#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    double a, b, c;

public:
    void Init(double x, double y, double z) {
        a = x;
        b = y;
        c = z;
    }

    void setSideA(double x) { a = x; }
    void setSideB(double y) { b = y; }
    void setSideC(double z) { c = z; }

    double getSideA() { return a; }
    double getSideB() { return b; }
    double getSideC() { return c; }

    bool isTriangle() {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    double perimeter() {
        if (!isTriangle()) return 0;
        return a + b + c;
    }

    double area() {
        if (!isTriangle()) return 0;

        double p = perimeter() / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    int typeTriangle() {
        if (!isTriangle()) return 0;

        double x = a, y = b, z = c;

        if (x > y && x > z) swap(x, z);
        if (y > z) swap(y, z);

        double x2 = x * x;
        double y2 = y * y;
        double z2 = z * z;

        if (fabs(x2 + y2 - z2) < 1e-6) return 2;       
        else if (x2 + y2 > z2) return 1;              
        else return 3;                                 
    }
};

int main() {
    Triangle t;
    double a, b, c;

    cout << "请输入三角形三条边：";
    cin >> a >> b >> c;

    t.Init(a, b, c);

    if (!t.isTriangle()) {
        cout << "无法构成三角形！" << endl;
        return 0;
    }

    cout << "周长： " << t.perimeter() << endl;
    cout << "面积： " << t.area() << endl;

    int tp = t.typeTriangle();
    if (tp == 1) cout << "类型：锐角三角形" << endl;
    else if (tp == 2) cout << "类型：直角三角形" << endl;
    else if (tp == 3) cout << "类型：钝角三角形" << endl;

    return 0;
}
