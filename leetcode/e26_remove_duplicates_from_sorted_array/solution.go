package main

func removeDuplicates(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	j := 0
	for i := 1; i < len(nums); i++ {
		// fast 指针完整遍历整个数组，过程中比对 slow 指针的指向
		// 给定的数组本身是有序的，只有 slow 和 fast 指向不同值的时候，说明遇到了一个不一样的值
		if nums[i] != nums[j] {
			// 维护指针
			j++
			// 把遍历到的新值赋值到数组前面
			nums[j] = nums[i]
		}
	}
	// slow 是数组下表指向，即 len - 1，所以返回的时候需要 +1
	return j + 1
}
