package main

import (
	"fmt"
	"math"
)

const PI = 3.141592653589793

func input(xMin *float64, xMax *float64, step *float64) bool {
	// ввод данных
	fmt.Println("Введите Xнач, Xкон, шаг dx")

	isDone := true

	_, err := fmt.Scan(xMin, xMax, step)
	if err != nil || *step <= 0 {
		isDone = false
	}

	return isDone
}

// Функция вычисления
func funcCalc(xMin float64, xMax float64, step float64) {

	var y float64

	fmt.Printf("%5s%20s\n", "X", "Y")
	fmt.Printf("%s\n", "-------------------------------")

	for xMin <= xMax {

		// Левая ветвь (-5,-4): y = -sqrt(-x - 4) - 1
		if xMin < -4 {
			y = -math.Sqrt(-xMin-4) - 1
		}

		// Средняя волна: y = -sin(pi * x / 4)
		if xMin >= -4 && xMin <= 4 {
			y = -math.Sin(PI * xMin / 4)
		}

		// Правая ветвь (4,5): y = sqrt(x - 4) + 1
		if xMin > 4 {
			y = math.Sqrt(xMin-4) + 1
		}

		if math.Abs(y) < 1e-10 {
			y = 0.0
		}

		fmt.Printf("%9.4f%20.4f\n", xMin, y)

		xMin += step
	}

	fmt.Printf("%s\n", "-------------------------------")
}

func main() {

	var xMin, xMax, step float64

	if input(&xMin, &xMax, &step) {
		funcCalc(xMin, xMax, step)
	} else {
		fmt.Println("Введите корректные значения")
	}
}