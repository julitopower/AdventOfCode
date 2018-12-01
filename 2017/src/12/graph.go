package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strings"
)

func parse(filename string) map[string][]string {
	m := make(map[string][]string)
	regex, _ := regexp.Compile("([0-9]+) <-> (.*)")
	// Opem file
	file, err := os.Open(filename)
	reader := bufio.NewReader(file)
	var line []byte

	// Process line by line
	count := 0
	for {
		line, _, err = reader.ReadLine()
		if err != nil {
			break
		}
		match := regex.FindStringSubmatch(string(line))
		if len(match) == 0 {
			continue
		} else {
			count++
		}

		key := match[1]
		if _, ok := m[key]; !ok {
			m[key] = make([]string, 0)
		}

		list := match[2]
		elements := strings.Split(list, ", ")
		for _, element := range elements {
			m[key] = append(m[key], element)
		}

	}
	return m
}

func main() {
	m := parse("input.txt")
	set := make(map[string]int)
	q := make([]string, 0)
	q = append(q, "0")
	for len(q) > 0 {
		curr := q[0]
		q = q[1:]
		set[curr] = 0
		children := m[curr]
		for _, child := range children {
			if _, ok := set[child]; !ok {
				q = append(q, child)
			}
		}
	}

	fmt.Println(len(set))
}
