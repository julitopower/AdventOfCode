package main

import (
	"fmt"
)

// Slices are passeb by value, but they are effectively a sort of
// pointer to the actual underlying array, so modifications through
// the slice are actually reflected outside the function
func reverse(init int, end int, arr []int) {
	size := len(arr)
	for {
		if init >= end {
			break
		}
		aux := arr[init % size]
		arr[init % size] = arr[end % size]
		arr[end % size] = aux
		init++
		end--
	}
}

func main() {
	input := [...]int{94,84,0,79,2,27,81,1,123,93,218,23,103,255,254,243}

	var chain []int = make([]int, 256)
	for i := 0 ; i <= 255 ; i++ {
		chain[i] = i
	}

	step := 0
	init := 0
	for _, v := range input {
		fmt.Println(v)
		reverse(init, init + v - 1, chain)
		fmt.Println(chain)
		init = init + v + step
		step++
	}

	fmt.Println(chain[0] * chain[1])
}
