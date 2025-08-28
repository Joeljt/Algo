package main

import (
	"fmt"
)

func equalSlice(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

func main() {
	fmt.Print("e26_remove_duplicates_from_sorted_array", " => ")

	tests := []struct {
		in  []int
		out []int
		n   int
	}{
		{in: []int{1, 1, 2}, out: []int{1, 2}, n: 2},
		{in: []int{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, out: []int{0, 1, 2, 3, 4}, n: 5},
		{in: []int{1}, out: []int{1}, n: 1},
	}

	ok := true
	for _, tc := range tests {
		arr := make([]int, len(tc.in))
		copy(arr, tc.in)
		k := removeDuplicates(arr)
		if k != tc.n || !equalSlice(arr[:k], tc.out) {
			ok = false
			break
		}
	}

	if ok {
		fmt.Println("[PASS]")
	} else {
		fmt.Println("[FAIL]")
	}
}
