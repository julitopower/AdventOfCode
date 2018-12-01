package main

import (
	"fmt"
	"math"
)

func index(nb int) (int, int) {
	dim := 1
	max := 0
	min := 0
	row, col := 0, 0
	dir := 0
	for i := 0 ; i < nb - 1 ; i++ {
		fmt.Printf("%d(%d, %d) dir %d: %d, %d -> ", i + 1, min, max, dir, row, col)
		if row == min && col == max {
			dim = dim + 2
			min--
			max++
		} else if dir == 0 && col == max {
			dir = 1
		} else if row == 0 && col == max {
			dir = 1
		}  else if row == max && col == max {
			dir = 2
		} else if row == max && col == min {
			dir = 3
		} else if row == min && col == min {
			dir = 0
		}

		switch dir {
		case 0: col++
		case 1: row++
		case 2: col--
		case 3: row--
		}
		fmt.Println(row, col)		
	}
	return row, col
}

func main() {
	row, col := index(361527)
	fmt.Println(math.Abs(float64(row)) + math.Abs(float64(col)))
}
