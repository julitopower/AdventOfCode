package main

import (
	"encoding/hex"
	"fmt"
)

// Slices are passeb by value, but they are effectively a sort of
// pointer to the actual underlying array, so modifications through
// the slice are actually reflected outside the function
func reverse(init int, end int, arr []byte) {
	size := len(arr)
	for {
		if init >= end {
			break
		}
		aux := arr[init%size]
		arr[init%size] = arr[end%size]
		arr[end%size] = aux
		init++
		end--
	}
}

func knot_hash(in string) string {
	// Define a salt
	salt := []byte{17, 31, 73, 47, 23}

	// Trainsform input into []byte
	ascii := make([]byte, len(in)+len(salt))
	for i, c := range []byte(in) {
		ascii[i] = c
	}

	// Append salt
	for i := 0; i < len(salt); i++ {
		ascii[i+len(in)] = salt[i]
	}

	// Generate initial sequence
	chain := make([]byte, 256)
	for i := 0; i <= 255; i++ {
		chain[i] = byte(i)
	}

	// Execute knots 64 times
	step := 0
	init := 0
	for i := 0; i < 64; i++ {
		for _, v := range ascii {
			reverse(init, init+int(v)-1, chain)
			init = init + int(v) + step
			step++
		}
	}

	// Xor 16 numbers together
	out := make([]byte, 16)
	for i := 0; i < 16; i++ {
		ret := byte(0)
		for j := 0; j < 16; j++ {
			ret ^= chain[(i*16)+j]
		}
		out[i] = ret
	}

	return hex.EncodeToString(out)
}

func main() {
	str := "94,84,0,79,2,27,81,1,123,93,218,23,103,255,254,243"
	fmt.Println(knot_hash(str))
}
