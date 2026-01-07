package m912sortarray

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

	// 调用 partition 方法获取一个基准点（下标），该基准点已经处于正确位置
	// < pivot 的值都应该在其左侧，> pivot 的值都应该在其右侧
	pivot := partition(nums, left, right)
	// 根据 pivot 将数组分成左右两部分，然后分段去处理
	quickSort(nums, left, pivot-1)
	quickSort(nums, pivot+1, right)
}

// 选定一个标定元素，然后在遍历过程中将该元素放到数组中间
// 保证所有在该元素左侧的元素都小于它，所有在该元素右侧的元素都大于它
// 最后返回该元素所在的下标
// 这里注意循环不变量的选择，left 和 right 都是可以取到的范围
func partition(nums []int, left, right int) int {
	// 标定点可以随便选，直接用当前区间的最左侧元素
	target := nums[left]

	// 三路快排
	// 将数组分为三个部分，左侧区间 <target、当前遍历区间、右侧区间 >target

	// 初始化遍历指针，标定点选择了第一个元素，所以遍历需要跳过 left 索引，直接从 left + 1 开始
	i := left + 1
	// 初始化两个指针指向首位两端，注意这里 start 指向 left 是正确的，因为遍历的起始点是 left+1
	start, end := left, right+1

	for i < end {
		if nums[i] < target {
			// 当前遍历到的元素比 target 小，把元素交换到左侧
			// 因为 start 指针默认指向区间外，所以需要先向前推进以后再进行交换
			start++
			nums[i], nums[start] = nums[start], nums[i]
			// 继续向前查看下一个元素
			i++
		} else if nums[i] > target {
			// 当前遍历到的元素比 target 大，需要交换到右侧
			// 但是由于右侧指针指向数组边界外，需要先维护指针再交换
			end--
			nums[i], nums[end] = nums[end], nums[i]
			// 因为交换过来的元素也是新元素，还没有接受过检查，所以 i 指针不需要向前推进
		} else {
			// 当前元素与目标元素相当，直接跳过查看下一个元素即可
			i++
		}
	}

	// 注意在这个时候，target 只是作为标准在进行判断，target 目前还在 left 的位置上，我们需要将 target 放到它应该在的位置

	// 一次循环完成后
	// 所有 nums[left, start] < target
	// 所有 nums[end, right] > target
	// 所有 nums[start+1, end-1] = target
	// start 指向最后一个 < target 的值，所以直接把它和 left 交换即可保持定义不变
	nums[left], nums[start] = nums[start], nums[left]

	// 交换以后 start 的位置就是 target 了，所以返回 start 即可
	return start
}
