package m912sortarray

import (
	"reflect"
	"testing"
)

// 共用的测试用例，用于测试所有排序算法
func TestSortArray(t *testing.T) {
	tests := []struct {
		name     string
		nums     []int
		expected []int
	}{
		{
			name:     "Example 1",
			nums:     []int{5, 2, 3, 1},
			expected: []int{1, 2, 3, 5},
		},
		{
			name:     "Example 2",
			nums:     []int{5, 1, 1, 2, 0, 0},
			expected: []int{0, 0, 1, 1, 2, 5},
		},
		{
			name:     "Empty array",
			nums:     []int{},
			expected: []int{},
		},
		{
			name:     "Single element",
			nums:     []int{1},
			expected: []int{1},
		},
		{
			name:     "Already sorted",
			nums:     []int{1, 2, 3, 4, 5},
			expected: []int{1, 2, 3, 4, 5},
		},
		{
			name:     "Reverse order",
			nums:     []int{5, 4, 3, 2, 1},
			expected: []int{1, 2, 3, 4, 5},
		},
		{
			name:     "All same elements",
			nums:     []int{3, 3, 3, 3},
			expected: []int{3, 3, 3, 3},
		},
		{
			name:     "All same elements large",
			nums:     makeLargeArray(1000, 5), // 1000 个元素，都是 5
			expected: makeLargeArray(1000, 5),
		},
		{
			name:     "With negative numbers",
			nums:     []int{-5, 2, -3, 1, 0, -1},
			expected: []int{-5, -3, -1, 0, 1, 2},
		},
		{
			name:     "Large range",
			nums:     []int{10, 1, 5, 8, 3, 7, 2, 9, 4, 6},
			expected: []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		},
		{
			name:     "Duplicates",
			nums:     []int{2, 1, 2, 3, 1, 3, 2},
			expected: []int{1, 1, 2, 2, 2, 3, 3},
		},
		{
			name:     "Two elements",
			nums:     []int{2, 1},
			expected: []int{1, 2},
		},
		{
			name:     "Large array",
			nums:     []int{64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42},
			expected: []int{11, 12, 22, 25, 34, 42, 50, 64, 76, 88, 90},
		},
	}

	// 测试归并排序
	// t.Run("MergeSort", func(t *testing.T) {
	// 	for _, tt := range tests {
	// 		t.Run(tt.name, func(t *testing.T) {
	// 			// 复制输入数组，避免修改原始测试用例
	// 			nums := make([]int, len(tt.nums))
	// 			copy(nums, tt.nums)

	// 			result := SortArrayMergeSort(nums)

	// 			if !reflect.DeepEqual(result, tt.expected) {
	// 				t.Errorf("SortArrayMergeSort() = %v, want %v", result, tt.expected)
	// 			}
	// 		})
	// 	}
	// })

	// 测试快速排序
	t.Run("QuickSort", func(t *testing.T) {
		for _, tt := range tests {
			t.Run(tt.name, func(t *testing.T) {
				// 复制输入数组，避免修改原始测试用例
				nums := make([]int, len(tt.nums))
				copy(nums, tt.nums)

				result := SortArrayQuickSort(nums)

				if !reflect.DeepEqual(result, tt.expected) {
					t.Errorf("SortArrayQuickSort() = %v, want %v", result, tt.expected)
				}
			})
		}
	})
}

// Benchmark tests
func BenchmarkSortArrayMergeSort(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		nums[i] = 1000 - i // 逆序数组，最坏情况
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		SortArrayMergeSort(testNums)
	}
}

func BenchmarkSortArrayQuickSort(b *testing.B) {
	nums := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		nums[i] = 1000 - i // 逆序数组，最坏情况
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums := make([]int, len(nums))
		copy(testNums, nums)
		SortArrayQuickSort(testNums)
	}
}

// makeLargeArray 创建一个指定大小和值的数组
func makeLargeArray(size int, value int) []int {
	arr := make([]int, size)
	for i := range arr {
		arr[i] = value
	}
	return arr
}

// TestQuickSortAllSameElementsTimeout 专门测试所有元素相同时的超时场景
// 这个测试用例用于检测快速排序在处理所有元素相同的数组时是否会超时
func TestQuickSortAllSameElementsTimeout(t *testing.T) {
	// 使用较大的数组来触发超时（如果算法有问题）
	// LeetCode 912 的约束是 1 <= nums.length <= 5 * 10^4
	// 我们使用接近上限的数组大小来测试
	testCases := []struct {
		name  string
		size  int
		value int
	}{
		{
			name:  "Small array all same",
			size:  100,
			value: 1,
		},
		{
			name:  "Medium array all same",
			size:  1000,
			value: 2,
		},
		{
			name:  "Large array all same",
			size:  10000,
			value: 3,
		},
		{
			name:  "Very large array all same (接近 LeetCode 上限)",
			size:  50000,
			value: 4,
		},
	}

	for _, tt := range testCases {
		t.Run(tt.name, func(t *testing.T) {
			nums := make([]int, tt.size)
			for i := range nums {
				nums[i] = tt.value
			}

			// 记录开始时间
			result := SortArrayQuickSort(nums)

			// 验证结果正确性
			expected := make([]int, tt.size)
			for i := range expected {
				expected[i] = tt.value
			}

			if !reflect.DeepEqual(result, expected) {
				t.Errorf("SortArrayQuickSort() = %v (first 10: %v), want %v (first 10: %v)",
					result, result[:min(10, len(result))],
					expected, expected[:min(10, len(expected))])
			}

			// 验证所有元素都相同
			for i := 0; i < len(result); i++ {
				if result[i] != tt.value {
					t.Errorf("result[%d] = %d, want %d", i, result[i], tt.value)
					break
				}
			}
		})
	}
}

// min 返回两个整数中的较小值
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
