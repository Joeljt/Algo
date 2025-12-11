package e283movezeros

import (
	"reflect"
	"testing"
)

func TestMoveZeroes(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected []int
	}{
		{
			name:     "Example 1",
			input:    []int{0, 1, 0, 3, 12},
			expected: []int{1, 3, 12, 0, 0},
		},
		{
			name:     "Example 2",
			input:    []int{0},
			expected: []int{0},
		},
		{
			name:     "Example 3",
			input:    []int{0, 0, 1},
			expected: []int{1, 0, 0},
		},
		{
			name:     "No zeros",
			input:    []int{1, 2, 3},
			expected: []int{1, 2, 3},
		},
		{
			name:     "All zeros",
			input:    []int{0, 0, 0},
			expected: []int{0, 0, 0},
		},
		{
			name:     "Zeros at the end",
			input:    []int{1, 2, 3, 0, 0},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Zeros at the beginning",
			input:    []int{0, 0, 1, 2, 3},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Zeros in the middle",
			input:    []int{1, 0, 2, 0, 3},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Empty array",
			input:    []int{},
			expected: []int{},
		},
		{
			name:     "Single non-zero",
			input:    []int{1},
			expected: []int{1},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// Make a copy of input to avoid modifying the original test case
			nums := make([]int, len(tt.input))
			copy(nums, tt.input)

			MoveZeroes(nums)

			if !reflect.DeepEqual(nums, tt.expected) {
				t.Errorf("MoveZeroes() = %v, want %v", nums, tt.expected)
			}
		})
	}
}

func TestMoveZeroesSwap(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected []int
	}{
		{
			name:     "Example 1",
			input:    []int{0, 1, 0, 3, 12},
			expected: []int{1, 3, 12, 0, 0},
		},
		{
			name:     "Example 2",
			input:    []int{0},
			expected: []int{0},
		},
		{
			name:     "Example 3",
			input:    []int{0, 0, 1},
			expected: []int{1, 0, 0},
		},
		{
			name:     "No zeros",
			input:    []int{1, 2, 3},
			expected: []int{1, 2, 3},
		},
		{
			name:     "All zeros",
			input:    []int{0, 0, 0},
			expected: []int{0, 0, 0},
		},
		{
			name:     "Zeros at the end",
			input:    []int{1, 2, 3, 0, 0},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Zeros at the beginning",
			input:    []int{0, 0, 1, 2, 3},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Zeros in the middle",
			input:    []int{1, 0, 2, 0, 3},
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "Empty array",
			input:    []int{},
			expected: []int{},
		},
		{
			name:     "Single non-zero",
			input:    []int{1},
			expected: []int{1},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// Make a copy of input to avoid modifying the original test case
			nums := make([]int, len(tt.input))
			copy(nums, tt.input)

			MoveZeroesSwap(nums)

			if !reflect.DeepEqual(nums, tt.expected) {
				t.Errorf("MoveZeroesSwap() = %v, want %v", nums, tt.expected)
			}
		})
	}
}

// Benchmark tests
func BenchmarkMoveZeroes(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		if i%3 == 0 {
			nums[i] = 0
		} else {
			nums[i] = i
		}
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		MoveZeroes(testNums)
	}
}

func BenchmarkMoveZeroesSwap(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		if i%3 == 0 {
			nums[i] = 0
		} else {
			nums[i] = i
		}
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		MoveZeroesSwap(testNums)
	}
}
