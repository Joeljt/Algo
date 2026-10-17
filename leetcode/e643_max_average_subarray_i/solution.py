"""643. 子数组最大平均数 I

https://leetcode.com/problems/maximum-average-subarray-i/

整数数组 nums 和整数 k，找长度 k 的连续子数组的最大平均数。

决定性条件：
- 窗口长度恒为 k：每步右进左出各一格，不必用 209/3 那种「条件不满足才 while 缩 left」。
- k 固定时 max(平均) 等价于 max(窗口和)：可先比 max_sum，最后除以 k。
- 不必机械套变长窗口模板；滚动 window_sum 往往最简单。

不变量（find_max_average：长度固定为 k，滚动求和）：
- 第一次 sum(nums[:k]) 后，窗口为 nums[0 : k]，window_sum 为其元素和。
- 循环中 i 为窗口右端下标，窗口为 nums[i - k + 1 : i + 1]，长度恒为 k。
- 每步 window_sum += nums[i] - nums[i - k]，即右进左出；max_sum 记录出现过的最大窗口和（与最大平均数等价，因 k 固定）。

不变量（find_max_average1：双指针维护长度 k）：
- 当 right - left + 1 == k 时，sum 为 nums[left : right + 1] 的和；之后 sum 减 nums[left]、left += 1，窗口仍长 k。

步骤：
给定的窗口大小，只需要滚动计算窗口内的平均数，并记录最大值输出即可

"""

def find_max_average(nums: list, k: int) -> float:
    # 计算窗口内数据总和
    window_sum = sum(nums[:k])
    # 记录为当前的最大值
    max_sum = window_sum

    # 从第 k 个元素开始遍历
    for i in range(k, len(nums)):
        # 窗口内总和 = 前 k 个元素 + nums[k+1] - nums[k-1]
        window_sum = window_sum + nums[i] - nums[i-k]
        # 更新最值
        if window_sum > max_sum:
            max_sum = window_sum

    # 最后返回平均数即可
    return max_sum / k

def find_max_average1(nums: list, k: int) -> float:
    left = 0
    sum = 0
    average = float('-inf')

    for right in range(len(nums)):
        # 把窗口内的所有值都加起来，计算平均值
        sum += nums[right]
        # 到达窗口上限后，开始滑动
        if right - left + 1 == k:
            # 计算平均值
            # 平均值的计算位置很重要，因为题目要求是 k 的连续子数组的平均值，如果在外边计算得到的平均值就不是子数组了
            average = max(average, sum / k)
            # 之后开始滑动
            sum -= nums[left]
            left += 1

    return average

if __name__ == '__main__':
    # find_max_average([-6662,5432,-8558,-8935,8731,-3083,4115,9931,-4006,-3284,-3024,1714,-2825,-2374,-2750,-959,6516,9356,8040,-2169,-9490,-3068,6299,7823,-9767,5751,-7897,6680,-1293,-3486,-6785,6337,-9158,-4183,6240,-2846,-2588,-5458,-9576,-1501,-908,-5477,7596,-8863,-4088,7922,8231,-4928,7636,-3994,-243,-1327,8425,-3468,-4218,-364,4257,5690,1035,6217,8880,4127,-6299,-1831,2854,-4498,-6983,-677,2216,-1938,3348,4099,3591,9076,942,4571,-4200,7271,-6920,-1886,662,7844,3658,-6562,-2106,-296,-3280,8909,-8352,-9413,3513,1352,-8825], 90)
    find_max_average([1,12,-5,-6,50,3], 4)