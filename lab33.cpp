#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// НОД (алгоритм Евклида)
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int powerA, baseB;
    cin >> powerA >> baseB;

    if (baseB == 1) { // при b == 1 ряд расходится
        cout << "infinity" << endl;
        return 0;
    }

    // вычисляем рекурсивно
    double currentTerm = 1.0 / baseB;  // первый член: n = 1, 1^a / b^1
    double seriesSum = currentTerm;


    for (int n = 2; n <= 1000000; ++n) { // Считаем ряд до сходимости или лимита итераций
        currentTerm *= pow((double)n / (n - 1), powerA) / baseB;
        seriesSum += currentTerm;

        if (currentTerm < 1e-15) break; // если вклад слишком мал = ряд сошёлся
    }
    // метод перебора знаменателей (поиск дроби приблежающей sum)
    long long bestNumerator = 0;
    long long bestDenominator = 1;
    double bestError = seriesSum;

    for (long long denominator = 1; denominator <= 1000000; ++denominator) {
        long long numerator = llround(seriesSum * denominator);

        double approx = (double)numerator / denominator;
        double error = fabs(seriesSum - approx);

        if (error < bestError) {
            bestError = error;
            bestNumerator = numerator;
            bestDenominator = denominator;

            // ранний выход при высокой точности
            if (error < 1e-12) break;
        }
    }

    // сокращаем дробь через НОД
    long long divisor = gcd(llabs(bestNumerator), bestDenominator);
    bestNumerator /= divisor;
    bestDenominator /= divisor;

    cout << bestNumerator << "/" << bestDenominator << endl;

    return 0;
}
