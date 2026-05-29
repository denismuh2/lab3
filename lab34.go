package main

import (
	"fmt"
)

// сколько элементов взять (1..m), чтобы сумма взятых элементов была максимальной, нельзя повторять прошлый ход
func chooseBestMove(arr []int, currentPos int, n int, maxTake int, previousTake int) int {

	bestSum := -1 << 31
	bestTake := 1
	currentSum := 0

	// пробуем взять от 1 до m элементов
	for takeCount := 1; takeCount <= maxTake && currentPos+takeCount <= n; takeCount++ {

		currentSum += arr[currentPos+takeCount-1]

		if takeCount == previousTake { // нельзя повторять прошлый ход
			continue
		}

		if currentSum > bestSum { // выбираем вариант с максимальной суммой
			bestSum = currentSum
			bestTake = takeCount
		}
	}

	return bestTake
}

func main() {

	var n, m int

	fmt.Print("Введите n и m: ")
	fmt.Scan(&n, &m)

	arr := make([]int, n)

	fmt.Print("Введите элементы массива: ")
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	pavelScore := 0 // очки Павла
	vikaScore := 0

	lastPavelMove := 0 // сколько брал Павел в прошлый ход
	lastVikaMove := 0

	position := 0

	isPavelTurn := true // чей сейчас ход

	for position < n {

		if isPavelTurn {

			// выбираем лучший ход для Павла
			take := chooseBestMove(arr, position, n, m, lastPavelMove)

			sum := 0

			// считаем сумму реально взятых элементов
			for i := 0; i < take; i++ {
				sum += arr[position+i]
			}

			fmt.Printf("Павел берет %d чисел. Сумма = %d\n", take, sum)

			pavelScore += sum
			lastPavelMove = take // запоминаем ход
			position += take
		} else {

			// выбираем лучший ход для Вики
			take := chooseBestMove(arr, position, n, m, lastVikaMove)

			sum := 0

			for i := 0; i < take; i++ {
				sum += arr[position+i]
			}

			fmt.Printf("Вика берет %d чисел. Сумма = %d\n", take, sum)

			vikaScore += sum
			lastVikaMove = take

			position += take
		}

		isPavelTurn = !isPavelTurn // смена игрока
	}

	fmt.Println()
	fmt.Printf("Очки Павла: %d\n", pavelScore)
	fmt.Printf("Очки Вики: %d\n", vikaScore)
	fmt.Println()

	// вывод победителя
	if pavelScore > vikaScore {
		fmt.Println("Ответ: 1")
	} else {
		fmt.Println("Ответ: 0")
	}
}
