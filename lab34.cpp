#include <iostream>
#include <vector>
#include <climits>

using namespace std;

 //сколько элементов взять (1..m), чтобы сумма взятых элементов была максимальной, нельзя повторять прошлый ход
int chooseBestMove(const vector<int>& arr,int currentPos,int n,int maxTake,int previousTake) {

    int bestSum = INT_MIN;
    int bestTake = 1;
    int currentSum = 0;

    // пробуем взять от 1 до m элементов
    for (int takeCount = 1; takeCount <= maxTake && currentPos + takeCount <= n; takeCount++) {

        currentSum += arr[currentPos + takeCount - 1];

        if (takeCount == previousTake) { // нельзя повторять прошлый ход
            continue;
        }

        if (currentSum > bestSum) { // выбираем вариант с максимальной суммой
            bestSum = currentSum;
            bestTake = takeCount;
        }
    }
    return bestTake;
}

int main() {
    int n, m;

    cout << "Введите n и m: ";
    cin >> n >> m;

    vector<int> arr(n);

    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int pavelScore = 0;   // очки Павла
    int vikaScore = 0;

    int lastPavelMove = 0; // сколько брал Павел в прошлый ход
    int lastVikaMove = 0;

    int position = 0;

    bool isPavelTurn = true; // чей сейчас ход

    while (position < n) {

        if (isPavelTurn) {

            // выбираем лучший ход для Павла
            int take = chooseBestMove(arr, position, n, m, lastPavelMove);

            int sum = 0;

            // считаем сумму реально взятых элементов
            for (int i = 0; i < take; i++) {
                sum += arr[position + i];
            }
            cout << "Павел берет " << take << " чисел. ";
            cout << "Сумма = " << sum << endl;

            pavelScore += sum;
            lastPavelMove = take;  // запоминаем ход
            position += take;
        }
        else {
            // выбираем лучший ход для Вики
            int take = chooseBestMove(arr, position, n, m, lastVikaMove);

            int sum = 0;

            for (int i = 0; i < take; i++) {
                sum += arr[position + i];
            }
            cout << "Вика берет " << take << " чисел. ";
            cout << "Сумма = " << sum << endl;

            vikaScore += sum;
            lastVikaMove = take;

            position += take;
        }
        isPavelTurn = !isPavelTurn;// смена игрока
    }
    cout << endl;
    cout << "Очки Павла: " << pavelScore << endl;
    cout << "Очки Вики: " << vikaScore << endl;
    cout << endl;

    // вывод победителя
    if (pavelScore > vikaScore) {
        cout << "Ответ: 1";
    } else {
        cout << "Ответ: 0";
    }

    return 0;
}
