#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Сначала делим и получаем целое число - количество раз, которое необходимо вычесть из x.
// Затем вычитаем это число раз из х и проверяем меньше или равно данное число, чем pi/2.
// Если да, то все оставляем как есть, иначе отнимаем еще pi и увеличиваем число вычитаний.
// Если число вычитаний четное, то знак плюс, иначе минус.
double findInterval(double x) {
    const double pi = 3.14159265;

    int count_subtraction = x / pi;

    x -= pi * count_subtraction;

    if (x > pi / 2) {
        x -= pi;
        count_subtraction++;
    }

    if (x < -pi / 2) {
        x += pi;
        count_subtraction++;
    }

    return x * pow(-1, count_subtraction);
}

// Считаем в вечном цикле ряд по общей формуле, до того момента, пока не увидим,
// что с каждым шагом мы прибавляем число меньше, чем наша точность.
void findSin(double x, double accuracy) {
    double result = 0;
    int counter_accuracy = 0;
    double factorial = 1;

    for (int i = 0;; i++) {
        if (i != 0) {
            factorial *= ((2 * i) + 1) * (2 * i);
        }

        double previous_result = result;
        double current_result = ((pow(-1, i) * pow(x, 2 * i + 1)) / factorial) + result;

        if (abs(current_result - previous_result) <= accuracy && counter_accuracy == 0) {
            cout << setprecision(-log10(accuracy)) << result << endl << "1";
            return;
        }

        if (abs(current_result - previous_result) <= accuracy) {
            break;
        }

        result = current_result;
        counter_accuracy++;
    }

    cout << setprecision(-log10(accuracy)) << result << endl << counter_accuracy;
}

int main() {
    double accuracy, x;

    cin >> x;
    cin >> accuracy;

    findSin(findInterval(x), accuracy);
}