package main

import (
	"fmt"
	"io/ioutil"
)

func readline(s []byte, offset int) (string, int)  {
	for i := offset ; i < len(s) ; i++ {
		if s[i] == '\n' {
			return string(s[offset:i]), i + 1
		}
	}
	return string(s[offset:]), len(s)
}

func readwords(s string) []string {
	words := make([]string, 0)
	start, offset := 0, 0
	inword := true
	for {
		if offset >= len(s) || s[offset] == ' ' {
			if inword == true {
				inword = false
				word := string(s[start:offset])
				words = append(words, word)
			}
			if offset >= len(s) {
				break
			}
		} else if inword == false {
			start = offset
			inword = true
		}
		offset++
	}
	return words
}

func has_repeated_word(words []string) bool {
	x := make(map[string]int)
	for _, word := range words {
		_, ok := x[word]
		if !ok {
			x[word] = 1
			continue
		}
		return true
	}
	return false
}

func main() {	
	f, _ := ioutil.ReadFile("input.txt")
	line, offset := "", 0
	accum := 0
	for {
		line, offset = readline(f, offset)
		row := readwords(line)
		if !has_repeated_word(row) {
			accum++
		}
		if offset == len(f) {
			break
		}		
	}
	fmt.Println(accum)
}
