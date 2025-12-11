package e283movezeros

// MoveZeroes solves LeetCode 283. Move Zeroes
// Problem: Given an integer array nums, move all 0's to the end of it while maintaining
// the relative order of the non-zero elements.
//
// Note that you must do this in-place without making a copy of the array.
//
// Example:
//
//	Input: nums = [0,1,0,3,12]
//	Output: [1,3,12,0,0]
//
// Time Complexity: O(n)
// Space Complexity: O(1)
func MoveZeroes(nums []int) {
	// Use two pointers: slow points to the next position for non-zero elements
	// fast is used to traverse the array
	slow := 0

	// First pass: move all non-zero elements to the front
	for fast := 0; fast < len(nums); fast++ {
		if nums[fast] != 0 {
			nums[slow] = nums[fast]
			slow++
		}
	}

	// Second pass: fill remaining positions with zeros
	for i := slow; i < len(nums); i++ {
		nums[i] = 0
	}
}

// MoveZeroesSwap is an alternative solution using swap (one pass)
// Time Complexity: O(n)
// Space Complexity: O(1)
func MoveZeroesSwap(nums []int) {
	slow := 0
	for fast := 0; fast < len(nums); fast++ {
		if nums[fast] != 0 {
			// Swap non-zero element to the front
			nums[slow], nums[fast] = nums[fast], nums[slow]
			slow++
		}
	}
}
