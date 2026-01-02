package e27removeelement

import (
	"reflect"
	"testing"
)

func TestRemoveElement(t *testing.T) {
	tests := []struct {
		name           string
		nums           []int
		val            int
		expectedLength int
		expectedNums   []int
	}{
		{
			name:           "Example 1",
			nums:           []int{3, 2, 2, 3},
			val:            3,
			expectedLength: 2,
			expectedNums:   []int{2, 2},
		},
		{
			name:           "Example 2",
			nums:           []int{0, 1, 2, 2, 3, 0, 4, 2},
			val:            2,
			expectedLength: 5,
			expectedNums:   []int{0, 1, 3, 0, 4},
		},
		{
			name:           "No matching elements",
			nums:           []int{1, 2, 3, 4},
			val:            5,
			expectedLength: 4,
			expectedNums:   []int{1, 2, 3, 4},
		},
		{
			name:           "All elements match",
			nums:           []int{2, 2, 2, 2},
			val:            2,
			expectedLength: 0,
			expectedNums:   []int{},
		},
		{
			name:           "Empty array",
			nums:           []int{},
			val:            1,
			expectedLength: 0,
			expectedNums:   []int{},
		},
		{
			name:           "Single element matching",
			nums:           []int{1},
			val:            1,
			expectedLength: 0,
			expectedNums:   []int{},
		},
		{
			name:           "Single element not matching",
			nums:           []int{1},
			val:            2,
			expectedLength: 1,
			expectedNums:   []int{1},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// 复制输入数组，避免修改原始测试用例
			nums := make([]int, len(tt.nums))
			copy(nums, tt.nums)

			length := RemoveElement(nums, tt.val)

			if length != tt.expectedLength {
				t.Errorf("RemoveElement() length = %d, want %d", length, tt.expectedLength)
			}

			// 检查前 length 个元素是否正确
			if !reflect.DeepEqual(nums[:length], tt.expectedNums) {
				t.Errorf("RemoveElement() nums[:%d] = %v, want %v", length, nums[:length], tt.expectedNums)
			}
		})
	}
}

// Benchmark tests
func BenchmarkRemoveElement(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		if i%3 == 0 {
			nums[i] = 2 // 要移除的值
		} else {
			nums[i] = i
		}
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		RemoveElement(testNums, 2)
	}
}

