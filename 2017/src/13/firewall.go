package main

import (
	"bufio"
	"fmt"
	"regexp"
	"os"
	"strconv"
)

type layer struct {
	Pos int 
	Len int 
	Dir int 
}

func (l *layer) update() {
	if l.Pos == 0 {
		l.Dir = 1
	} else if l.Pos == l.Len - 1 {
		l.Dir = -1
	}

	l.Pos += l.Dir
}

func parse(filename string) (map[int]layer, int) {
	firewall := make(map[int]layer, 0)
	regex, _ := regexp.Compile("([0-9]+): (.*)")
	
	// Open file
	file, err := os.Open(filename)
	reader := bufio.NewReader(file)
	var line []byte

	// Process line by line
	count := 0
	max_layer := 0
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

		layer_nb, _ := strconv.Atoi(match[1])
		layer_length, _ := strconv.Atoi(match[2])
		firewall[layer_nb] = layer{0, layer_length, 1}
		if max_layer < layer_nb {
			max_layer = layer_nb
		}
	}
	return firewall, max_layer
}

func main() {
	firewall, max_layer := parse("input.txt")
	mypos := - 1
	sev := 0
	for i := 0 ; i <= max_layer ; i++ {
		mypos = i
		if l, ok := firewall[mypos] ; ok {
			if l.Pos == 0 {
				fmt.Println("Caught", mypos)
				sev+= mypos * l.Len
			}
		}
		for k,v := range firewall {
			v.update()
			firewall[k] = v
		}
	}
	fmt.Println(sev)
}
