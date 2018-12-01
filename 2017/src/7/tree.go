package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// We need a routine to parse the input into the
// representation
func parse(filename string) map[string][]string {
	file, err := os.Open(filename)
	reader := bufio.NewReader(file)
	
	m := make(map[string][]string)
	var line []byte;

	for {
		line, _, err = reader.ReadLine()
		if err != nil {
			break
		}
		
		tokens := strings.Split(string(line), "->")
		// Parent is completely clean here
		parent := strings.Split(tokens[0], " ")[0]

		if len(tokens) > 1 {
			// Each child has an extra space prefix
			children := strings.Split(tokens[1], ",")
			for i, child := range children {
				children[i] = child[1:]
			}
			m[parent] = children
		} else {
			m[parent] = nil
		}
		
	}
	return m
}

// Then the routine that simply looks for the root node,
// which is the node that doesn't appear as the child of
// any other node
func find_root(tree map[string][]string) string {
	// Map of nodes that are child of some other node
	children := make(map[string]int)
	// Map of nodes seen so far
	nodes := make(map[string]int)
	// iterate through the tree
	for k, v := range tree {
		if _, ok := children[k]; !ok {
			nodes[k] = 1

		}
		for _, c := range v {
			children[c] = 1
			if _, ok := nodes[c]; ok {
				delete(nodes, c)

			}

		}

	}

	// At this point nodes only have one child
	k := "x"
	for k = range nodes {
		fmt.Println("I'm hee")

	}
	return k

}

func main() {
	print(find_root(parse("input.txt")))
}
