package m912sortarray

import "math/rand"

// SortArrayQuickSort 排序数组 - 快速排序解法
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
// 思路：快速排序（Quick Sort）
//
//	快速排序采用分治策略：
//	1. 选择基准值（pivot）：从数组中选择一个元素作为基准
//	2. 分区（partition）：将数组重新排列，使得所有小于基准的元素在基准左边，
//	   所有大于基准的元素在基准右边
//	3. 递归：递归地对基准左右两边的子数组进行排序
//
//	时间复杂度:
//	  - 平均情况: O(n log n)
//	  - 最坏情况: O(n^2) - 当每次选择的基准都是最大或最小元素时
//	  - 最好情况: O(n log n)
//	空间复杂度: O(log n) - 递归调用栈的深度
func SortArrayQuickSort(nums []int) []int {
	quickSort(nums, 0, len(nums)-1)
	return nums
}

// quickSort 递归地进行快速排序
// 快排的核心逻辑是 partition 操作
// partition 的目标是返回某个基准点，该基准点已经处于自己正确的位置上，根据该基准点将数组分为两部分，
// 左侧部分都小于该基准点，右侧部分都大于该基准点，然后递归地对左侧和右侧部分进行排序。
func quickSort(nums []int, left, right int) {

	// 当前要处理的区间长度为 1，说明这个区间已经是有序的，直接返回
	if left >= right {
		return
	}

	// 调用 partition 方法获取两个下标，这两个下标将数组分为三部分，左侧部分都小于该基准点，右侧部分都大于该基准点，中间部分等于该基准点
	lt, gt := partition(nums, left, right)
	// 根据 lt 和 gt 将数组分成三部分，然后分段去处理
	quickSort(nums, left, lt-1)
	quickSort(nums, gt+1, right)
}

// 选定一个标定元素，然后在遍历过程中将该元素放到数组中间
// 保证所有在该元素左侧的元素都小于它，所有在该元素右侧的元素都大于它
// 最后返回该元素所在的下标
// 这里注意循环不变量的选择，left 和 right 都是可以取到的范围
func partition(nums []int, left, right int) (int, int) {
	// 标定点可以随便选，直接用当前区间的最左侧元素
	// left 是偏移量，保证随机索引在 [left, right] 范围内
	randomIndex := left + rand.Intn(right-left+1)
	nums[left], nums[randomIndex] = nums[randomIndex], nums[left]

	target := nums[left]

	i := left + 1
	lt, gt := left, right+1

	for i < gt {
		if nums[i] < target {
			lt++
			nums[i], nums[lt] = nums[lt], nums[i]
			i++
		} else if nums[i] > target {
			gt--
			nums[i], nums[gt] = nums[gt], nums[i]
		} else {
			i++
		}
	}

	nums[left], nums[lt] = nums[lt], nums[left]

	return lt, gt - 1 // gt 指向的是 >target 的第一个元素，-1 以后是等于 target 的最后一个元素
}
