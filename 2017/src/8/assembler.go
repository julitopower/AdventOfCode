package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func something(filename string) {
	// Define and compile regex
	regex, _ := regexp.Compile("([a-z]+) (dec|inc) ([-]?[0-9]+) if ([a-z]+) ([<=>!]+) ([-]?[0-9]+)")

	// Opem file
	file, err := os.Open(filename)
	reader := bufio.NewReader(file)
	var line []byte

	// Process line by line
	m := make(map[string]int)
	count := 0
	for {
		line, _, err = reader.ReadLine()
		if err != nil {
			break
		}		
		match := regex.FindStringSubmatch(string(line))
		
		// regiter
		if len(match)== 0 {
			continue
		} else {
			count++
		}

		target_reg := match[1]
		if _, ok := m[target_reg] ; !ok {
			m[target_reg] = 0
		}		
		op := match[2]
		op_val, _ := strconv.Atoi(match[3])		
		comp_reg := match[4]
		comp_op := match[5]
		comp_val, _ := strconv.Atoi(match[6])

		// Evaluate if conditions
		// determin lhs value
		comp_reg_val := 0
		if v, ok := m[comp_reg]; ok {
			comp_reg_val = v
		}

		comp := false
		switch (comp_op) {
		case "<": comp = comp_reg_val < comp_val
		case ">": comp = comp_reg_val > comp_val
		case "<=": comp = comp_reg_val <= comp_val
		case ">=": comp = comp_reg_val >= comp_val			
		case "==": comp = comp_reg_val == comp_val
		case "!=": comp = comp_reg_val != comp_val							
		}

		if comp == true {
			if op == "inc" {
				m[target_reg] += op_val
			} else {
				m[target_reg] -= op_val
			}
		}
	}

	max := 0
	for k := range m {
		max = m[k]
	}

	for _,v := range m {
		if v > max {
			max = v
		}
		
	}
	fmt.Println(m)
	fmt.Println(max)
}

func main() {
	fmt.Println("Hey")
	something("input.txt")
}
