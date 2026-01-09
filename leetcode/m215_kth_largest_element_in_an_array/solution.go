package m215kthlargestelementinanarray

import (
	"math/rand"
	"sort"
)

// FindKthLargest 数组中的第K个最大元素
// LeetCode 215: 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
//
// 示例 1：
//
//	输入：nums = [3,2,1,5,6,4], k = 2
//	输出：5
//
// 示例 2：
//
//	输入：nums = [3,2,3,1,2,4,5,5,6], k = 4
//	输出：4
//
// 提示：
//
//	1 <= k <= nums.length <= 10^4
//	-10^4 <= nums[i] <= 10^4
//
// 思路提示：
//
//  1. 可以直接排序后取第 k 个最大元素，时间复杂度 O(n log n)
//  2. 可以使用堆（优先队列），维护一个大小为 k 的最小堆，时间复杂度 O(n log k)
//  3. 可以使用快速选择算法（Quick Select），平均时间复杂度 O(n)，最坏 O(n^2)
//
// 时间复杂度: 取决于实现方式
// 空间复杂度: 取决于实现方式
func FindKthLargestBySort(nums []int, k int) int {
	sort.Ints(nums)
	return nums[len(nums)-k]
}

// FindKthLargest 数组中的第K个最大元素
// 使用快速选择算法实现，基于三路快排优化，平均时间复杂度 O(n)
func FindKthLargest(nums []int, k int) int {
	index := quickSelect(nums, 0, len(nums)-1, k-1)
	return nums[index]
}

func quickSelect(nums []int, left, right, k int) int {

	if left >= right {
		return left
	}

	gt, lt := partition(nums, left, right)

	if k < gt {
		return quickSelect(nums, left, gt, k)
	} else if k > lt {
		return quickSelect(nums, lt, right, k)
	} else {
		return gt
	}

}

// 基于快排的 partition 逻辑
// 如果某个元素处于它应该在的位置，那就返回其所在的下标，然后基于该下标将数据一分为二，递归查找
// 查找第 k 个最大的元素
// 要么转换为正序索引，比如 6 个元素的场景下，第 2 大的元素目标索引实际上应该是 4
// 要么在排序的时候就倒过来，由大到小降序排列，这样索引和语意没有偏差，6个元素，第 2 大的索引为 1
// 普通的快排在有大量重复元素的 case 下复杂度会退化为 n^2，因此需要使用三路快排实现
func partition(nums []int, left, right int) (int, int) {

	// 随机下标
	randIndex := left + rand.Intn(right-left+1)
	nums[left], nums[randIndex] = nums[randIndex], nums[left]

	// 选择标定点
	target := nums[left]

	// 三路快排指针
	gt, lt, i := left, right, left+1

	// 从第二个元素开始向后遍历，过程中保证循环不变量如下：
	// nums[left, gt) > target
	// nums[gt, i) = target
	// nums(lt, right] < target
	for i <= lt {
		if nums[i] > target {
			nums[i], nums[gt] = nums[gt], nums[i]
			gt++
			i++
		} else if nums[i] < target {
			nums[i], nums[lt] = nums[lt], nums[i]
			lt--
		} else {
			i++
		}
	}

	return gt, lt
}
