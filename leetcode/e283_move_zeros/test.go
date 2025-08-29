package main

import (
	"fmt"
	"reflect"
)

func main() {
	tests := []struct {
		nums     []int
		expected []int
	}{
		{[]int{0, 1, 0, 3, 12}, []int{1, 3, 12, 0, 0}},
		{[]int{0}, []int{0}},
		{[]int{1, 0, 1}, []int{1, 1, 0}},
		{[]int{0, 0, 0}, []int{0, 0, 0}},
		{[]int{1, 2, 3, 4, 5}, []int{1, 2, 3, 4, 5}},
		{[]int{1, 0, 0, 0, 0}, []int{1, 0, 0, 0, 0}},
		{[]int{0, 0, 0, 0, 1}, []int{1, 0, 0, 0, 0}},
	}

	for _, test := range tests {
		arr := make([]int, len(test.nums))
		copy(arr, test.nums)
		moveZeroes(arr)
		if !reflect.DeepEqual(arr, test.expected) {
			fmt.Printf("[FAIL] e283_move_zeros: expected %v, got %v\n", test.expected, arr)
			return
		}
	}

	fmt.Println("[PASS] e283_move_zeros")
}
