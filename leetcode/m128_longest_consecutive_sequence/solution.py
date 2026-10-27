"""128. 最长连续序列

https://leetcode.com/problems/longest-consecutive-sequence/

未排序整数数组 nums，返回其中最长连续数字序列的长度。要求时间复杂度 O(n)。

决定性条件：

不变量：

步骤：
"""

def longest_consecutive(nums: list) -> int:
    longest = 0

    # 去重，同时让「判断某个数在不在」从列表的 O(n) 变成集合的 O(1)
    nums = set(nums)

    # 直接遍历集合里的每个元素，不需要下标
    for value in nums:

        # 检查 x-1 在不在集合里，如果在的话，说明当前元素不是连续区间起点
        if (value - 1) in nums:
            continue

        # 否则 value 是起点，每个起点各自从 0 开始数，不能沿用上一段的长度
        cur_length = 0
        while value in nums:
            cur_length += 1
            value += 1

        # 这一段数完了，和历史最大值比较，longest 不能清零
        longest = max(longest, cur_length)

        # 优化
        # 如果当前找到的连续序列长度的两倍大于数组长度，说明已经找到了最长的连续序列，可以提前结束
        if longest * 2 > len(nums):
            break
        
    return longest


def longest_consecutive1(nums: list) -> int:
    nums = set(nums)

    if len(nums) == 0: return 0
    if len(nums) == 1: return 1

    sorted_nums = sorted(nums)
    dict = {}
    key = 0
    for i in range(1, len(sorted_nums)):
        # 跳过连续元素
        if sorted_nums[i] == sorted_nums[i - 1]:
            continue
        if sorted_nums[i] - sorted_nums[i - 1] == 1:
           if key not in dict:
                dict[key] = 1
           dict[key] = dict[key] + 1
        else:
            key = i # 连续被打断，更新 hashkey，为下一组连续数做准备

    values = list(dict.values())
    return max(values) if len(values) else 0

if __name__ == '__main__':
    # longest_consecutive([1, 10])
    longest_consecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1])
