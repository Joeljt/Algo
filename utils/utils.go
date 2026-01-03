package utils

// Swap 交换切片中两个位置的元素
// 如果索引越界，函数不会执行任何操作
func Swap[T any](slice []T, i, j int) {
	if i < 0 || i >= len(slice) || j < 0 || j >= len(slice) {
		return
	}
	slice[i], slice[j] = slice[j], slice[i]
}

// Max 返回两个整数中的较大值
func Max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// Min 返回两个整数中的较小值
func Min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// MaxOf 返回整数切片中的最大值
// 如果切片为空，返回 0
func MaxOf(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	max := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > max {
			max = nums[i]
		}
	}
	return max
}

// MinOf 返回整数切片中的最小值
// 如果切片为空，返回 0
func MinOf(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	min := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] < min {
			min = nums[i]
		}
	}
	return min
}

// Reverse 反转切片（原地操作）
func Reverse[T any](slice []T) {
	for i, j := 0, len(slice)-1; i < j; i, j = i+1, j-1 {
		slice[i], slice[j] = slice[j], slice[i]
	}
}

// ReverseRange 反转切片中指定范围的元素（原地操作）
// [start, end) 左闭右开区间
// 如果索引越界，函数不会执行任何操作
func ReverseRange[T any](slice []T, start, end int) {
	if start < 0 || end > len(slice) || start >= end {
		return
	}
	for i, j := start, end-1; i < j; i, j = i+1, j-1 {
		slice[i], slice[j] = slice[j], slice[i]
	}
}

// IndexOf 返回元素在切片中第一次出现的索引，如果不存在则返回 -1
func IndexOf[T comparable](slice []T, target T) int {
	for i, v := range slice {
		if v == target {
			return i
		}
	}
	return -1
}

// LastIndexOf 返回元素在切片中最后一次出现的索引，如果不存在则返回 -1
func LastIndexOf[T comparable](slice []T, target T) int {
	for i := len(slice) - 1; i >= 0; i-- {
		if slice[i] == target {
			return i
		}
	}
	return -1
}

// Equal 比较两个切片是否相等（长度和元素都相同）
func Equal[T comparable](a, b []T) bool {
	if len(a) != len(b) {
		return false
	}
	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}
	return true
}

// Copy 创建切片的深拷贝
func Copy[T any](slice []T) []T {
	result := make([]T, len(slice))
	copy(result, slice)
	return result
}
