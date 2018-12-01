package main

import (
	"fmt"
	"io/ioutil"
)

func main() {
	input := "input.txt"
	f, _ := ioutil.ReadFile(input)
	acc, curr := 0, 0
	garbage := false
	skip := false
	for _, c := range f {
		if skip {
			skip = false
			continue
		}
		switch c {
		case '!':
			if garbage {
				skip = true
			}
		case '<':
			if !garbage {
				garbage = true
			}
		case '>':
			if garbage {
				garbage = false
			}
		case '{':
			if !garbage {
				curr++
				acc += curr
			}
		case '}':
			if !garbage {
				curr--
			}
		}
	}
	fmt.Println(acc)
}
