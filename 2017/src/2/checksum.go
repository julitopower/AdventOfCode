package main

import (
	"fmt"
	"io/ioutil"
	"sort"
	"strconv"
)

func readline(s []byte, offset int) (string, int) {
	for i := offset; i < len(s); i++ {
		if s[i] == '\n' {
			return string(s[offset:i]), i + 1
		}
	}
	return string(s[offset:]), len(s)
}

func readnumbers(s string) []int {
	numbers := make([]int, 0)
	start, offset := 0, 0
	innumber := true
	for {
		if offset >= len(s) || s[offset] == ' ' {
			if innumber == true {
				innumber = false
				nb, _ := strconv.Atoi(string(s[start:offset]))
				numbers = append(numbers, nb)
			}
			if offset >= len(s) {
				break
			}
		} else if innumber == false {
			start = offset
			innumber = true
		}
		offset++
	}
	return numbers
}

func main() {
	f, _ := ioutil.ReadFile("input.txt")
	line, offset := "", 0
	accum := 0
	for {
		line, offset = readline(f, offset)
		row := readnumbers(line)
		sort.Ints(row)
		accum += row[len(row)-1] - row[0]
		fmt.Println(row, offset)
		if offset == len(f) {
			break
		}
	}
	fmt.Println(accum)

}
