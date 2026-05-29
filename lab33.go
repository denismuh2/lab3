package main

import (
	"fmt"
	"math"
)

// НОД (алгоритм Евклида)
func gcd(a int64, b int64) int64 {
	if b == 0 {
		return a
	}
	return gcd(b, a%b)
}

func main() {
	var powerA, baseB int

	fmt.Scan(&powerA, &baseB)

	if baseB == 1 { // при b == 1 ряд расходится
		fmt.Println("infinity")
		return
	}

	// вычисляем рекурсивно
	currentTerm := 1.0 / float64(baseB) // первый член: n = 1, 1^a / b^1
	seriesSum := currentTerm

	for n := 2; n <= 1000000; n++ { // Считаем ряд до сходимости или лимита итераций
		currentTerm *= math.Pow(float64(n)/float64(n-1), float64(powerA)) / float64(baseB)
		seriesSum += currentTerm

		if currentTerm < 1e-15 { // если вклад слишком мал = ряд сошёлся
			break
		}
	}

	// метод перебора знаменателей (поиск дроби приблежающей sum)
	var bestNumerator int64 = 0
	var bestDenominator int64 = 1
	bestError := seriesSum

	for denominator := int64(1); denominator <= 1000000; denominator++ {
		numerator := int64(math.Round(seriesSum * float64(denominator)))

		approx := float64(numerator) / float64(denominator)
		error := math.Abs(seriesSum - approx)

		if error < bestError {
			bestError = error
			bestNumerator = numerator
			bestDenominator = denominator

			// ранний выход при высокой точности
			if error < 1e-12 {
				break
			}
		}
	}

	// сокращаем дробь через НОД
	divisor := gcd(int64(math.Abs(float64(bestNumerator))), bestDenominator)
	bestNumerator /= divisor
	bestDenominator /= divisor

	fmt.Printf("%d/%d\n", bestNumerator, bestDenominator)
}