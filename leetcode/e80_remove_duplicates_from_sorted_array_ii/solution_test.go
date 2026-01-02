package e80removeduplicatesfromsortedarrayii

import (
	"reflect"
	"testing"
)

func TestRemoveDuplicates(t *testing.T) {
	tests := []struct {
		name           string
		nums           []int
		expectedLength int
		expectedNums   []int
	}{
		{
			name:           "Example 1",
			nums:           []int{1, 1, 1, 2, 2, 3},
			expectedLength: 5,
			expectedNums:   []int{1, 1, 2, 2, 3},
		},
		{
			name:           "Example 2",
			nums:           []int{0, 0, 1, 1, 1, 1, 2, 3, 3},
			expectedLength: 7,
			expectedNums:   []int{0, 0, 1, 1, 2, 3, 3},
		},
		{
			name:           "All same elements",
			nums:           []int{1, 1, 1, 1},
			expectedLength: 2,
			expectedNums:   []int{1, 1},
		},
		{
			name:           "No duplicates",
			nums:           []int{1, 2, 3},
			expectedLength: 3,
			expectedNums:   []int{1, 2, 3},
		},
		{
			name:           "Each element appears twice",
			nums:           []int{1, 1, 2, 2, 3, 3},
			expectedLength: 6,
			expectedNums:   []int{1, 1, 2, 2, 3, 3},
		},
		{
			name:           "Single element",
			nums:           []int{1},
			expectedLength: 1,
			expectedNums:   []int{1},
		},
		{
			name:           "Two same elements",
			nums:           []int{1, 1},
			expectedLength: 2,
			expectedNums:   []int{1, 1},
		},
		{
			name:           "Empty array",
			nums:           []int{},
			expectedLength: 0,
			expectedNums:   []int{},
		},
		{
			name:           "Complex case",
			nums:           []int{1, 1, 1, 2, 2, 2, 3, 3, 3, 3},
			expectedLength: 6,
			expectedNums:   []int{1, 1, 2, 2, 3, 3},
		},
		{
			name:           "One element appears once, others twice",
			nums:           []int{1, 1, 2, 2, 2, 3},
			expectedLength: 5,
			expectedNums:   []int{1, 1, 2, 2, 3},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// 复制输入数组，避免修改原始测试用例
			nums := make([]int, len(tt.nums))
			copy(nums, tt.nums)

			length := RemoveDuplicates(nums)

			if length != tt.expectedLength {
				t.Errorf("RemoveDuplicates() length = %d, want %d", length, tt.expectedLength)
			}

			// 检查前 length 个元素是否正确
			if !reflect.DeepEqual(nums[:length], tt.expectedNums) {
				t.Errorf("RemoveDuplicates() nums[:%d] = %v, want %v", length, nums[:length], tt.expectedNums)
			}
		})
	}
}

// Benchmark tests
func BenchmarkRemoveDuplicates(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		// 创建包含重复元素的数组
		nums[i] = i / 3 // 每个数字会出现3次
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		RemoveDuplicates(testNums)
	}
}

