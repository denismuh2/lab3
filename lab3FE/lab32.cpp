#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// прототипы функций
void printTable(vector<unsigned long long> primes,vector<bool> results,vector<int> rejectedCounts);

int millerTest(unsigned long long n, vector<int> factorsQ, int iterations);

bool generatePrimeCandidate(int bitLength,int accuracy,unsigned long long& prime,int& rejectedCount,const vector<int>& smallPrimes);

unsigned long long modPow(unsigned long long base,unsigned long long exp,unsigned long long mod);

void sievePrimes(vector<int>& primes);

int bitLength(unsigned long long x);

unsigned long long buildNumber(int bits,vector<int> primes,vector<pair<int, int>>& factorization);

int main() {
    srand(time(NULL));

    vector<int> primes;
    sievePrimes(primes); // генерируем простые числа до 1000

    int bitSize, accuracy;


    if (cin >> bitSize && bitSize > 0 && cin >> accuracy && accuracy > 0) {

        vector<unsigned long long> generatedPrimes; // сгенерированные числа
        vector<bool> correctness;                   // результат теста простоты
        vector<int> rejectedStats;                  // число отклонённых попыток

        for (int i = 0; i < 10; ++i) { // генерируем 10 простых чисел заданной битности
            unsigned long long primeCandidate;
            int rejectedAttempts;

            // попытка генерации простого числа
            bool isPrime = generatePrimeCandidate(bitSize,accuracy,primeCandidate,rejectedAttempts,primes);

            generatedPrimes.push_back(primeCandidate);
            correctness.push_back(isPrime);
            rejectedStats.push_back(rejectedAttempts);
        }
        printTable(generatedPrimes, correctness, rejectedStats);
    }
    else {
        cout << "Введите корректное значение битов и параметр точности";
    }
    return 0;
}

// Решето Эратосфена: генерирует простые числа до 1000
void sievePrimes(vector<int>& primes) {
    vector<bool> isPrime(1001, true);

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= 1000; ++i) { // отметка составных чисел
        if (isPrime[i]) {
            for (int j = i * i; j <= 1000; j += i)
                isPrime[j] = false;
        }
    }
    for (int i = 2; i <= 1000; ++i) { // сохраняем простые числа (кроме 2)
        if (isPrime[i] && i != 2) {
            primes.push_back(i);
        }
    }
}

// вычисляет длину числа в битах
int bitLength(unsigned long long x) {
    int len = 0;
    while (x > 0) {
        ++len;
        x >>= 1; // сдвиг вправо = деление на 2
    }
    return len;
}

// быстрое возведение в степень по модулю
unsigned long long modPow(unsigned long long base,unsigned long long exp,unsigned long long mod) {
    base %= mod;
    unsigned long long result = 1;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;

        exp /= 2;
    }
    return result;
}

// строит число заданной битности как произведение простых степеней
unsigned long long buildNumber(int bits,vector<int> primes,vector<pair<int, int>>& factorization) {
    unsigned long long m;
    vector<int> used;
    bool success = false;

    while (!success) { //пока не получим число нужной битности
        m = 1;
        used.clear();
        factorization.clear();

        bool canContinue = true;

        while (bitLength(m) < bits - 1 && canContinue) { // строим число как произведение случайных простых степеней

            if (used.size() == primes.size()) {
                canContinue = false;
                break;
            }
            int prime;
            bool found = false;

            while (!found && used.size() < primes.size()) { // выбираем случайный простой множитель, который ещё не использовался
                int idx = rand() % primes.size();
                prime = primes[idx];

                bool alreadyUsed = false;
                for (int p : used)
                    if (p == prime) alreadyUsed = true;

                if (!alreadyUsed) {
                    used.push_back(prime);
                    found = true;
                }
            }
            int power = (rand() % 3) + 1;

            unsigned long long multiplier = 1;
            for (int i = 0; i < power; ++i)
                multiplier *= prime;

            if (bitLength(m * multiplier) <= bits - 1) {
                m *= multiplier;
                factorization.push_back({prime, power});
            }
        }
        if (bitLength(m) == bits - 1) // если достигли нужной битности
            success = true;
    }
    return m;
}

// тест Миллера (вероятностная проверка простоты)
int millerTest(unsigned long long n, vector<int> factorsQ, int t) {
    if (n < 2) return 1;
    if (n == 2) return 2;

    unsigned long long nMinus1 = n - 1;

    vector<unsigned long long> witnesses; // основания теста
    vector<unsigned long long> used;

    // выбираем случайные "свидетели"
    for (int i = 0; i < t; ++i) {
        unsigned long long a;

        while (true) {
            a = 2 + (rand() % (n - 2));

            bool exists = false;
            for (auto u : used)
                if (u == a) exists = true;

            if (!exists) break;
        }
        used.push_back(a);
        witnesses.push_back(a);
    }
    // тест Ферма
    for (auto a : witnesses)
        if (modPow(a, nMinus1, n) != 1)
            return 1;

    for (int q : factorsQ) { // дополнительная проверка по разложению
        unsigned long long exp = nMinus1 / q;

        bool allEqualOne = true;

        for (auto a : witnesses) {
            if (modPow(a, exp, n) != 1) {
                allEqualOne = false;
                break;
            }
        }
        if (allEqualOne)
            return 1;
    }

    return 2; // число прошло тест
}


// генерация простого числа заданной битности
bool generatePrimeCandidate(int bits,int t,unsigned long long& prime,int& rejected,const vector<int>& smallPrimes) {
    rejected = 0;

    vector<pair<int, int>> factorization;

    while (true) {
        // строим число m и преобразуем в n = 2m + 1
        unsigned long long m = buildNumber(bits, smallPrimes, factorization);
        unsigned long long n = 2 * m + 1;

        // проверка битности
        if (bitLength(n) != bits) {
            rejected++;
            continue;
        }
        vector<int> Q = {2};
        for (auto& p : factorization)
            Q.push_back(p.first);

        if (millerTest(n, Q, t) != 2) { // основной тест Миллера
            rejected++;
            continue;
        }

        if (millerTest(n, Q, 2) == 2) { // финальная проверка с меньшим числом итераций
            prime = n;
            return true;
        }
        rejected++;
    }
}

// вывод таблицы результатов
void printTable(vector<unsigned long long> primes,
                vector<bool> results,
                vector<int> rejectedCounts) {

    cout << setw(20) << "№";

    for (int i = 0; i < 10; ++i)
        cout << setw(10) << i + 1;

    cout << "\n";

    cout << setw(20) << "Prime";
    for (auto p : primes)
        cout << setw(10) << p;

    cout << "\n";

    cout << setw(20) << "Result";
    for (auto r : results)
        cout << setw(10) << (r ? "true" : "false");

    cout << "\n";

    cout << setw(20) << "Rejected";
    for (auto r : rejectedCounts)
        cout << setw(10) << r;

    cout << "\n";
}
