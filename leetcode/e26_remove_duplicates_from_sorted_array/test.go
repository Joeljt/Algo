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
	tests := []struct {
		in  []int
		out []int
		n   int
	}{
		{in: []int{1, 1, 2}, out: []int{1, 2}, n: 2},
		{in: []int{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, out: []int{0, 1, 2, 3, 4}, n: 5},
		{in: []int{1}, out: []int{1}, n: 1},
	}

	for _, tc := range tests {
		arr := make([]int, len(tc.in))
		copy(arr, tc.in)
		k := removeDuplicates(arr)
		if k != tc.n || !equalSlice(arr[:k], tc.out) {
			fmt.Println("[FAIL] e26_remove_duplicates_from_sorted_array")
			return
		}
	}

	fmt.Println("[PASS] e26_remove_duplicates_from_sorted_array")
}
