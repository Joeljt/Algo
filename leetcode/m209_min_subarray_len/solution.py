"""209. 长度最小的子数组

https://leetcode.com/problems/minimum-size-subarray-sum/

正整数数组 nums，正整数 target。
找出和至少达到 target 的最短连续子数组，返回它的长度。没有这样的子数组就返回 0。

不变量：

步骤：
"""


def min_subarray_len(target: int, nums: list) -> int:
    left = 0
    # 初始化一个比 nums 长度大的值，用于记录最短长度
    shortest = float('inf')
    sum = 0
    for right in range(len(nums)):
        # 每遍历一个元素，就记录一下数据总和
        sum += nums[right] 
        while sum >= target:
            # 如果当前总和超过 target，就说明已经满足条件了，应该记录一下当前已知的最短长度
            # 注意这里一定要做 min 比较，否则在后面的遍历过程中，可能会出现更长的连续子串，把之前更短的子串覆盖掉
            shortest = min(shortest, right - left + 1)
            # 尝试缩短左端，直到不满足 >= target 的条件
            # 本次 left++ 后不再满足条件，所以 min length 也不会被更新，所以对结果没有影响
            sum -= nums[left]
            left += 1
        
        # 如果尚不满足条件，就继续向右扩展
    
    # 如果最短长度没有被更新，则说明没有找到满足条件的子数组，返回 0
    return shortest if shortest != float('inf') else 0

if __name__ == "__main__":
    print(min_subarray_len(7, [2, 3, 1, 2, 4, 3]))
