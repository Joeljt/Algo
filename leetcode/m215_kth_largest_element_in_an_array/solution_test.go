package m215kthlargestelementinanarray

import (
	"testing"
)

func TestFindKthLargest(t *testing.T) {
	tests := []struct {
		name     string
		nums     []int
		k        int
		expected int
	}{
		{
			name:     "Example 1",
			nums:     []int{3, 2, 1, 5, 6, 4},
			k:        2,
			expected: 5,
		},
		{
			name:     "Example 2",
			nums:     []int{3, 2, 3, 1, 2, 4, 5, 5, 6},
			k:        4,
			expected: 4,
		},
		{
			name:     "Single element",
			nums:     []int{1},
			k:        1,
			expected: 1,
		},
		{
			name:     "Two elements, k=1",
			nums:     []int{2, 1},
			k:        1,
			expected: 2,
		},
		{
			name:     "Two elements, k=2",
			nums:     []int{2, 1},
			k:        2,
			expected: 1,
		},
		{
			name:     "All same elements",
			nums:     []int{1, 1, 1, 1, 1},
			k:        3,
			expected: 1,
		},
		{
			name:     "With negative numbers",
			nums:     []int{-1, -2, -3, -4, -5},
			k:        2,
			expected: -2,
		},
		{
			name:     "Mixed positive and negative",
			nums:     []int{3, -2, 5, -1, 4},
			k:        3,
			expected: 3,
		},
		{
			name:     "K equals 1 (largest)",
			nums:     []int{3, 2, 1, 5, 6, 4},
			k:        1,
			expected: 6,
		},
		{
			name:     "K equals length (smallest)",
			nums:     []int{3, 2, 1, 5, 6, 4},
			k:        6,
			expected: 1,
		},
		{
			name:     "Duplicates in array",
			nums:     []int{2, 2, 2, 1, 1, 1},
			k:        3,
			expected: 2,
		},
		{
			name:     "Large range",
			nums:     []int{10, 1, 5, 8, 3, 7, 2, 9, 4, 6},
			k:        3,
			expected: 8,
		},
		{
			name:     "Reverse sorted",
			nums:     []int{5, 4, 3, 2, 1},
			k:        2,
			expected: 4,
		},
		{
			name:     "Already sorted ascending",
			nums:     []int{1, 2, 3, 4, 5},
			k:        2,
			expected: 4,
		},
		{
			name:     "Complex case with many duplicates",
			nums:     []int{3, 2, 3, 1, 2, 4, 5, 5, 6, 7, 7, 8, 2, 3, 1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6},
			k:        2,
			expected: 10,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// 复制输入数组，避免修改原始测试用例
			nums := make([]int, len(tt.nums))
			copy(nums, tt.nums)

			result := FindKthLargest(nums, tt.k)

			if result != tt.expected {
				t.Errorf("FindKthLargest() = %v, want %v", result, tt.expected)
			}
		})
	}
}

// Benchmark tests
func BenchmarkFindKthLargest(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		nums[i] = 1000 - i // 逆序数组
	}
	k := 500

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		FindKthLargest(testNums, k)
	}
}
