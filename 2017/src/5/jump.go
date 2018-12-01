package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
)

func readline(s []byte, offset int) (string, int)  {
	for i := offset ; i < len(s) ; i++ {
		if s[i] == '\n' {
			return string(s[offset:i]), i + 1
		}
	}
	return string(s[offset:]), len(s)
}

func main() {
	f, _ := ioutil.ReadFile("input.txt")
	line, offset := "", 0
	jumps := make([]int, 0)
	for {
		line, offset = readline(f, offset)
		num, _ := strconv.Atoi(line)
		jumps = append(jumps, num)
		if offset == len(f) {
			break
		}		
	}

	max := len(jumps)
	i := 0
	counter := 0
	for {
		counter++
		dest := i + jumps[i]
		if dest < 0 || dest >= max {
			break
		}
		jumps[i]++
		i = dest
	}

	fmt.Println(counter)
}


