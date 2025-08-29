package main

import "fmt"

func main() {
	tests := []struct {
		s        string
		expected bool
	}{
		{s: "13579", expected: false},
		{s: "1397", expected: true},
		{s: "1357902", expected: false},
		{s: "13979317", expected: true},
	}
	for _, test := range tests {
		result := isBalanced(test.s)
		if result != test.expected {
			fmt.Printf("[FAIL] e3340_check_balanced_string: expected %v, got %v\n", test.expected, result)
			return
		}
	}

	fmt.Println("[PASS] e3340_check_balanced_string")
}
