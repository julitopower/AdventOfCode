package main

import (
	"fmt"
)

type Generator struct {
	Value  int
	Factor int
}

func (g *Generator) generate() int {
	next := g.Value * g.Factor
	next = next % 2147483647
	g.Value = next
	return next
}

func main() {
	a := Generator{883, 16807}
	b := Generator{879, 48271}
	count := 0
	for i := 0; i < 40000000; i++ {
		na := a.generate()
		nb := b.generate()
		if (na & 0x0000ffff) == (nb & 0x0000ffff) {
			count++
		}
	}

	fmt.Println(count)
}
