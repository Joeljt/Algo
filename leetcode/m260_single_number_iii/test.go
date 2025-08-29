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
		{[]int{1, 2, 1, 3, 2, 5}, []int{5, 3}},
		{[]int{-1, 0}, []int{0, -1}},
		{[]int{0, 1}, []int{0, 1}},
	}
	for _, test := range tests {
		arr := make([]int, len(test.nums))
		copy(arr, test.nums)
		result := singleNumber(arr)
		if !reflect.DeepEqual(result, test.expected) {
			fmt.Printf("[FAIL] m260_single_number_iii: expected %v, got %v\n", test.expected, result)
			return
		}
	}

	fmt.Println("[PASS] m260_single_number_iii")
}
