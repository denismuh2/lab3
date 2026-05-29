#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

bool input(double& xMin, double& xMax, double& step);
void func(double xMin, double xMax, double step);

const double PI = 3.141592653589793;

int main() {

    double xMin, xMax, step;

    if (input(xMin, xMax, step)) {
        func(xMin, xMax, step);
    }
    else {
        cout << "Введите корректные значения" << endl;
    }

    return 0;
}

// ввод данных
bool input(double& xMin, double& xMax, double& step) {

    cout << "Введите Xнач, Xкон, шаг dx" << endl;

    bool isDone = true;

    if (!(cin >> xMin >> xMax >> step) || step <= 0) {
        isDone = false;
    }

    return isDone;
}

// Функция вычисления
void func(double xMin, double xMax, double step) {

    double y;

    cout << setw(5) << "X" << right << setw(20) << "Y" << endl;
    cout << setfill('-') << setw(31) << "" << setfill(' ') << endl;

    while (xMin <= xMax) {

        // Левая ветвь (-5,-4): y = -sqrt(-x - 4) - 1
        if (xMin < -4) {
            y = -sqrt(-xMin - 4) - 1;
        }

        // Средняя волна: y = -sin(pi * x / 4)
        if (xMin >= -4 && xMin <= 4) {
            y = -sin(PI * xMin / 4);
        }

        // Правая ветвь (4,5): y = sqrt(x - 4) + 1
        if (xMin > 4) {
            y = sqrt(xMin - 4) + 1;
        }
        if (fabs(y) < 1e-10) {
            y = 0.0;
        }

        cout << fixed << setprecision(4);

        cout << setw(9) << xMin;
        cout << right << setw(20) << y << endl;

        xMin += step;
    }

    cout << setfill('-') << setw(31) << "" << setfill(' ') << endl;
}
