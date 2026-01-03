package e88mergesortedarray

import (
	"reflect"
	"testing"
)

func TestMerge(t *testing.T) {
	tests := []struct {
		name     string
		nums1    []int
		m        int
		nums2    []int
		n        int
		expected []int
	}{
		{
			name:     "Example 1",
			nums1:    []int{1, 2, 3, 0, 0, 0},
			m:        3,
			nums2:    []int{2, 5, 6},
			n:        3,
			expected: []int{1, 2, 2, 3, 5, 6},
		},
		{
			name:     "Example 2",
			nums1:    []int{1},
			m:        1,
			nums2:    []int{},
			n:        0,
			expected: []int{1},
		},
		{
			name:     "Example 3",
			nums1:    []int{0},
			m:        0,
			nums2:    []int{1},
			n:        1,
			expected: []int{1},
		},
		{
			name:     "nums1 empty",
			nums1:    []int{0, 0},
			m:        0,
			nums2:    []int{1, 2},
			n:        2,
			expected: []int{1, 2},
		},
		{
			name:     "nums2 empty",
			nums1:    []int{1, 2, 3, 0, 0},
			m:        3,
			nums2:    []int{},
			n:        0,
			expected: []int{1, 2, 3, 0, 0},
		},
		{
			name:     "All nums2 smaller",
			nums1:    []int{4, 5, 6, 0, 0, 0},
			m:        3,
			nums2:    []int{1, 2, 3},
			n:        3,
			expected: []int{1, 2, 3, 4, 5, 6},
		},
		{
			name:     "All nums2 larger",
			nums1:    []int{1, 2, 3, 0, 0, 0},
			m:        3,
			nums2:    []int{4, 5, 6},
			n:        3,
			expected: []int{1, 2, 3, 4, 5, 6},
		},
		{
			name:     "Interleaved",
			nums1:    []int{1, 3, 5, 0, 0, 0},
			m:        3,
			nums2:    []int{2, 4, 6},
			n:        3,
			expected: []int{1, 2, 3, 4, 5, 6},
		},
		{
			name:     "Single element each",
			nums1:    []int{2, 0},
			m:        1,
			nums2:    []int{1},
			n:        1,
			expected: []int{1, 2},
		},
		{
			name:     "Duplicate values",
			nums1:    []int{1, 2, 2, 0, 0, 0},
			m:        3,
			nums2:    []int{2, 3, 4},
			n:        3,
			expected: []int{1, 2, 2, 2, 3, 4},
		},
		{
			name:     "Negative numbers",
			nums1:    []int{-1, 0, 3, 0, 0, 0},
			m:        3,
			nums2:    []int{-2, -1, 4},
			n:        3,
			expected: []int{-2, -1, -1, 0, 3, 4},
		},
		{
			name:     "Same values",
			nums1:    []int{1, 1, 1, 0, 0, 0},
			m:        3,
			nums2:    []int{1, 1, 1},
			n:        3,
			expected: []int{1, 1, 1, 1, 1, 1},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// 复制输入数组，避免修改原始测试用例
			nums1 := make([]int, len(tt.nums1))
			copy(nums1, tt.nums1)

			Merge(nums1, tt.m, tt.nums2, tt.n)

			if !reflect.DeepEqual(nums1, tt.expected) {
				t.Errorf("Merge() = %v, want %v", nums1, tt.expected)
			}
		})
	}
}

// Benchmark tests
func BenchmarkMerge(b *testing.B) {
	nums1 := make([]int, 200)
	nums2 := make([]int, 100)
	for i := 0; i < 100; i++ {
		nums1[i] = i * 2
		nums2[i] = i*2 + 1
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		testNums1 := make([]int, len(nums1))
		copy(testNums1, nums1)
		testNums2 := make([]int, len(nums2))
		copy(testNums2, nums2)
		Merge(testNums1, 100, testNums2, 100)
	}
}
