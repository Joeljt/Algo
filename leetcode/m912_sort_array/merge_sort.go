package m912sortarray

// SortArrayMergeSort 排序数组 - 归并排序解法
// LeetCode 912: 给你一个整数数组 nums，请你将该数组升序排列。
//
// 示例 1：
//
//	输入：nums = [5,2,3,1]
//	输出：[1,2,3,5]
//
// 示例 2：
//
//	输入：nums = [5,1,1,2,0,0]
//	输出：[0,0,1,1,2,5]
//
// 提示：
//
//	1 <= nums.length <= 5 * 10^4
//	-5 * 10^4 <= nums[i] <= 5 * 10^4
//
// 思路：归并排序（Merge Sort）
//
//	归并排序采用分治策略：
//	1. 分解：将数组分成两半，递归地对两半进行排序
//	2. 合并：将两个已排序的子数组合并成一个有序数组
//
//	时间复杂度: O(n log n) - 最坏、平均、最好情况都是 O(n log n)
//	空间复杂度: O(n) - 需要额外的数组空间来存储合并结果
func SortArrayMergeSort(nums []int) []int {
	if len(nums) <= 1 {
		return nums
	}
	mergeSort(nums, 0, len(nums)-1)
	return nums
}

// mergeSort 递归地进行归并排序
func mergeSort(nums []int, left, right int) {

}
