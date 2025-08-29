package main

import "fmt"

func main() {
	tests := []struct {
		nums     []int
		expected int
	}{
		{[]int{2, 2, 1}, 1},
		{[]int{4, 1, 2, 1, 2}, 4},
		{[]int{1}, 1},
		{[]int{-1, -1, 2}, 2},
	}

	for _, test := range tests {
		result := singleNumber(test.nums)
		if result != test.expected {
			fmt.Printf("[FAIL] e136_single_number: expected %d, got %d\n", test.expected, result)
			return
		}
	}

	fmt.Println("[PASS] e136_single_number")
}
