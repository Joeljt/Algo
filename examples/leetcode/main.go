package main

import "fmt"

// 283. Move Zeroes
// 题目：给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//
// 示例:
// 输入: [0,1,0,3,12]
// 输出: [1,3,12,0,0]
//
// 说明:
// 必须在原数组上操作，不能拷贝额外的数组。
// 尽量减少操作次数。

// 方法1: 双指针法（推荐）
// 时间复杂度: O(n)
// 空间复杂度: O(1)
func moveZeroes(nums []int) {
	// 使用两个指针：slow 指向下一个非零元素应该放置的位置
	// fast 用于遍历数组
	slow := 0

	// 第一次遍历：将所有非零元素移到前面
	for fast := 0; fast < len(nums); fast++ {
		if nums[fast] != 0 {
			nums[slow] = nums[fast]
			slow++
		}
	}

	// 第二次遍历：将剩余位置填充为0
	for i := slow; i < len(nums); i++ {
		nums[i] = 0
	}
}

// 方法2: 交换法（一次遍历）
// 时间复杂度: O(n)
// 空间复杂度: O(1)
func moveZeroesSwap(nums []int) {
	slow := 0
	for fast := 0; fast < len(nums); fast++ {
		if nums[fast] != 0 {
			// 交换非零元素到前面
			nums[slow], nums[fast] = nums[fast], nums[slow]
			slow++
		}
	}
}

func main() {
	fmt.Println("=== LeetCode 283. Move Zeroes ===")
	fmt.Println()

	// 测试用例1
	nums1 := []int{0, 1, 0, 3, 12}
	fmt.Printf("输入: %v\n", nums1)
	moveZeroes(nums1)
	fmt.Printf("输出: %v\n", nums1)
	fmt.Println()

	// 测试用例2
	nums2 := []int{0}
	fmt.Printf("输入: %v\n", nums2)
	moveZeroes(nums2)
	fmt.Printf("输出: %v\n", nums2)
	fmt.Println()

	// 测试用例3
	nums3 := []int{0, 0, 1}
	fmt.Printf("输入: %v\n", nums3)
	moveZeroes(nums3)
	fmt.Printf("输出: %v\n", nums3)
	fmt.Println()

	// 测试交换法
	nums4 := []int{0, 1, 0, 3, 12}
	fmt.Printf("交换法 - 输入: %v\n", nums4)
	moveZeroesSwap(nums4)
	fmt.Printf("交换法 - 输出: %v\n", nums4)
}

