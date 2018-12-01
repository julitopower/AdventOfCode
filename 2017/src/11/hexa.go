package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func expand(m map[string]int, l1 string, l2 string, l3 string) bool {
	n, ok_n := m[l1]
	if !ok_n {
		return false
	}
	delete(m, l1)
	if _, ok := m[l2]; ok {
		m[l2] += n
	} else {
		m[l2] = n
	}
	if _, ok := m[l3]; ok {
		m[l3] += n
	} else {
		m[l3] = n
	}
	return true
}

func reduce(m map[string]int, l1 string, l2 string, l3 string) bool {
	n, ok_n := m[l1]
	s, ok_s := m[l2]
	if !ok_n || !ok_s {
		return false
	}
	diff := n - s
	fmt.Println("Diff between ", l1, " ", l2, " is ", diff)
	if diff > 0 {
		m[l1] = diff
		delete(m, l2)
		m[l3] = s
	} else if diff < 0 {
		delete(m, l1)
		m[l2] = -diff
		m[l3] = n
	} else {
		delete(m, l1)
		delete(m, l2)
		m[l3] = n
	}
	return true
}

func banlance_aux(m map[string]int, l1 string, l2 string) bool {
	n, ok_n := m[l1]
	s, ok_s := m[l2]
	if !ok_n || !ok_s {
		return false
	}
	diff := n - s
	fmt.Println("Diff between ", l1, " ", l2, " is ", diff)
	if diff > 0 {
		m[l1] = diff
		delete(m, l2)
	} else if diff < 0 {
		delete(m, l1)
		m[l2] = -diff
	} else {
		delete(m, l1)
		delete(m, l2)
	}
	return true
}

func banlance(m map[string]int) bool {
	r := false

	r = expand(m, "n", "ne", "nw") || r
	r = expand(m, "s", "se", "sw") || r
	r = banlance_aux(m, "ne", "sw") || r
	r = banlance_aux(m, "nw", "se") || r
	r = reduce(m, "se", "sw", "s") || r
	r = reduce(m, "ne", "nw", "n") || r
	r = banlance_aux(m, "n", "s") || r
	fmt.Println(m)
	return r
}

func main() {
	f, _ := ioutil.ReadFile("input.txt")
	//f := "ne,ne,s,s"
	m := make(map[string]int)
	dir := strings.Split(string(f), ",")
	for _, d := range dir {
		if _, ok := m[d]; ok {
			m[d]++
		} else {
			m[d] = 1
		}
	}

	fmt.Println(m)
	banlance(m)
	fmt.Println(m)

	accum := 0
	for _, v := range m {
		accum += v
	}
	fmt.Println("Steps: ", accum)
}
