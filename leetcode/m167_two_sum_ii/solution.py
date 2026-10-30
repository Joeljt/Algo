"""167. 两数之和 II - 输入有序数组

https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

非递减数组 numbers（1-indexed 下标），target。
找出和为 target 的两个数，返回 [index1, index2]，1 <= index1 < index2。

决定性条件：
- 数组是非严格升序的：左右两端相加，和偏小只能动左端才可能变大，偏大只能动右端才可能变小。
  每一步丢掉一端，不会漏解。无序数组没有这条，那是第 1 题用哈希的原因。
- 保证恰好一组解：找到就返回，不必继续扫。
- 下标是 1-indexed，且不能指向同一个位置：返回时 +1，循环条件是 left < right。

不变量：
- left 在左端，right 在右端，始终 left < right。
- [left, right] 以外已经丢掉的端点，不可能再和另一端组成答案。
- 当前和 < target：numbers[left] 太小，left 右移。
- 当前和 > target：numbers[right] 太大，right 左移。
- 当前和 == target：这对就是答案。

步骤：
数组本身是非严格升序排列的，所以用对撞指针：
两端相加，小于目标值就移动左端，大于目标值就移动右端，等于就返回（下标要 +1）。
直到 left 和 right 相遇还没找到，返回 [-1, -1]。

假设 [2, 7, 11, 15]，目标是 9：
- left=0, right=3，2+15=17 > 9，右端太大，right 左移到 2；
- 2+11=13 > 9，right 再左移到 1；
- 2+7=9，找到，返回 [1, 2]。

"""

def two_sum(numbers: list, target: int) -> list:
    left = 0
    right = len(numbers) - 1
    while left < right:
        if numbers[left] + numbers[right] < target:
            left = left + 1
        elif numbers[left] + numbers[right] > target:
            right = right - 1
        else:
            return [left + 1, right + 1]
    
    return [-1, -1]

if __name__ == '__main__':
    two_sum([2, 7, 11, 15], 9)