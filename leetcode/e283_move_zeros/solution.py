"""283. 移动零

https://leetcode.com/problems/move-zeroes/

把所有 0 移到末尾，保持非 0 元素的相对顺序，原地修改。

决定性条件：
- 原地、O(1) 额外空间：不能用新数组，只能交换或覆盖。
- 非 0 相对顺序不变：只能「按扫描顺序把非 0 写到前面」，不能排序。
- 0 只需全部到末尾：写指针 / 交换即可，不必统计 0 的个数再填。

不变量：
slow 是最后一个已经放好的非 0 的下标。每次看 fast 之前：
nums[0] 到 nums[slow] 是已经看过的非 0，相对顺序不变。slow 为 -1 时这一段为空。
nums[slow + 1] 到 nums[fast - 1] 全是 0。
fast 还没看到的元素保持原样。

步骤：
"""

# 原地修改的情况下，实际上需要两个指针来操作
# 一个指针用来做基础的数组遍历，一次数组遍历是无论如何都不可少的，因为至少要完整看过一遍数组才能知道哪些是 0，哪些是非 0
# 因为是把所有非 0 的元素移到前面，所以可以用一个指针来记录当前最后一个非 0 元素的位置
def move_zeroes(nums: list) -> None:
    slow = -1 # 最后一个已经放好的非 0 的下标，还没放过任何元素，所以是 -1
    for fast in range(len(nums)):
        if nums[fast] != 0:
            slow += 1 # 因为 slow 是即将放置元素的位置，所以需要先 +1 再放置
            nums[slow], nums[fast] = nums[fast], nums[slow]

# 原地修改的情况下，实际上需要两个指针来操作
# 一个指针用来做基础的数组遍历，一次数组遍历是无论如何都不可少的，因为至少要完整看过一遍数组才能知道哪些是 0，哪些是非 0
# 因为是把所有非 0 的元素移到前面，所以可以用一个指针来记录当前最后一个非 0 元素的位置
def move_zeroes_2(nums: list) -> None:
    slow = 0 # 下一个非 0 该放的位置
    for fast in range(len(nums)):
        if nums[fast] != 0:
            if slow != fast: # 可以避免第一个元素就是非 0 的时候，自己和自己交换
                nums[slow], nums[fast] = nums[fast], nums[slow]
            slow += 1
            
# 暴力解法
# 完整遍历整个数组，每次找到 0 后，就从当前位置的下一个位置开始，找到第一个非 0 的元素，然后交换它们的位置
# 但是这个解法有浪费，对于存在大量 0 的情况，每个 0 都会被多次访问
def move_zeroes_1(nums: list) -> None:
    for i in range(len(nums)):
        if nums[i] == 0:
            for j in range(i + 1, len(nums)):
                if nums[j] != 0:
                    nums[i], nums[j] = nums[j], nums[i]
                    break