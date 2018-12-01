package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func accumulate() {
	f, _ := os.Open("input")
	defer f.Close()

	scanner := bufio.NewScanner(f)
	var total int64 = 0
	for scanner.Scan() {
		value, _ := strconv.ParseInt(scanner.Text(), 10, 64)
		total += value
	}
	fmt.Println(total)
}

func findDuplicateFrequency() {
	set := make(map[int64]bool)

	var total int64 = 0
	set[total] = true
	for found := false; found == false; {
		f, _ := os.Open("input")
		scanner := bufio.NewScanner(f)
		for scanner.Scan() {
			value, err := strconv.ParseInt(scanner.Text(), 10, 64)
			if err != nil {
				// End of file potentially
				break
			}
			total += value

			if _, ok := set[total]; ok {
				found = true
				fmt.Println(total)
				break
			}
			set[total] = true

		}

		f.Close()
	}
}

func main() {
	accumulate()
	findDuplicateFrequency()
}
