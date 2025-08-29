package main

func moveZeroes(nums []int) {
	j := 0
	for i := 0; i < len(nums); i++ {
		if nums[i] != 0 {
			nums[j] = nums[i]
			j++
		}
	}
	// 将剩余位置填充为0
	for j < len(nums) {
		nums[j] = 0
		j++
	}
}
