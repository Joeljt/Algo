package m75sortcolors

import (
	"reflect"
	"testing"
)

func TestSortColors(t *testing.T) {
	tests := []struct {
		name     string
		nums     []int
		expected []int
	}{
		{
			name:     "Example 1",
			nums:     []int{2, 0, 2, 1, 1, 0},
			expected: []int{0, 0, 1, 1, 2, 2},
		},
		{
			name:     "Example 2",
			nums:     []int{2, 0, 1},
			expected: []int{0, 1, 2},
		},
		{
			name:     "Single element 0",
			nums:     []int{0},
			expected: []int{0},
		},
		{
			name:     "Single element 1",
			nums:     []int{1},
			expected: []int{1},
		},
		{
			name:     "Single element 2",
			nums:     []int{2},
			expected: []int{2},
		},
		{
			name:     "Already sorted",
			nums:     []int{0, 0, 1, 1, 2, 2},
			expected: []int{0, 0, 1, 1, 2, 2},
		},
		{
			name:     "Reverse order",
			nums:     []int{2, 2, 1, 1, 0, 0},
			expected: []int{0, 0, 1, 1, 2, 2},
		},
		{
			name:     "Only 0 and 1",
			nums:     []int{1, 0, 1, 0, 1},
			expected: []int{0, 0, 1, 1, 1},
		},
		{
			name:     "Only 1 and 2",
			nums:     []int{2, 1, 2, 1, 2},
			expected: []int{1, 1, 2, 2, 2},
		},
		{
			name:     "Only 0 and 2",
			nums:     []int{2, 0, 2, 0, 2},
			expected: []int{0, 0, 2, 2, 2},
		},
		{
			name:     "Mixed order",
			nums:     []int{1, 2, 0},
			expected: []int{0, 1, 2},
		},
		{
			name:     "All zeros",
			nums:     []int{0, 0, 0},
			expected: []int{0, 0, 0},
		},
		{
			name:     "All ones",
			nums:     []int{1, 1, 1},
			expected: []int{1, 1, 1},
		},
		{
			name:     "All twos",
			nums:     []int{2, 2, 2},
			expected: []int{2, 2, 2},
		},
		{
			name:     "Complex case",
			nums:     []int{2, 1, 0, 2, 1, 0, 2, 1, 0},
			expected: []int{0, 0, 0, 1, 1, 1, 2, 2, 2},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// 复制输入数组，避免修改原始测试用例
			nums := make([]int, len(tt.nums))
			copy(nums, tt.nums)
			SortColorsCountingSort(nums)
			if !reflect.DeepEqual(nums, tt.expected) {
				t.Errorf("SortColors() = %v, want %v", nums, tt.expected)
			}
		})
	}

	// for _, tt := range tests {
	// 	t.Run(tt.name, func(t *testing.T) {
	// 		// 复制输入数组，避免修改原始测试用例
	// 		nums := make([]int, len(tt.nums))
	// 		copy(nums, tt.nums)
	// 		SortColorsTwoPointers(nums)
	// 		if !reflect.DeepEqual(nums, tt.expected) {
	// 			t.Errorf("SortColors() = %v, want %v", nums, tt.expected)
	// 		}
	// 	})
	// }
}

// Benchmark tests
func BenchmarkSortColors(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		nums[i] = i % 3 // 创建包含 0、1、2 的数组
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		SortColorsCountingSort(testNums)
	}

	b.ResetTimer()
}
