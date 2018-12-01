package main

import (
	"fmt"
	"strconv"
)

func find_max(arr []int) (int, int) {
	max := 0
	max_idx := 0
	for i, v := range arr {
		if v > max {
			max = v
			max_idx = i
		}
	}
	return max_idx, max
}

func tostring(arr []int) string {
	str := ""
	for _, v := range arr {
		str += " " + strconv.Itoa(v)
	}
	return str
}

func main() {
	input := []int{2,8,8,5,4,2,3,1,5,5,1,2,15,13,5,14}
	size := len(input)

	configurations := make(map[string]int)
	configurations[tostring(input)] = 1
	for {
		idx, elem := find_max(input)
		input[idx] = 0
		for i := 0 ; i < elem ; i++ {
			idx = (idx + 1) % size
			input[idx]++
		}
		conf := tostring(input)

		if _, ok := configurations[conf] ; ok {
			fmt.Println(len(configurations))
			fmt.Println(conf)
			break
		} else {
			configurations[conf] = 1
		}
	}
}
