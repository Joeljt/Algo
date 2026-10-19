"""1. 两数之和

https://leetcode.com/problems/two-sum/

整数数组 nums，整数 target。
找出和为 target 的两个不同下标 i、j，返回 [i, j]（顺序任意）。保证恰好一组解。

决定性条件：
- 数组未排序：对撞双指针（167）不适用，应想到哈希查 complement。
- 只需一组解：见到 complement 在表里即可返回，不必存所有配对。
- 下标不能复用同一元素：存入表的是「已扫过的下标」，当前数先查再存。

不变量：
d 的 key 是已扫过的数 x 的补值 target - x，value 是 x 的下标。
扫到下标 i 时，d 只含下标 < i 的信息。
若 nums[i] 已在 d 中，则前面某数 x 满足 x + nums[i] == target。

步骤：
遍历数组，每次先查当前值是否已经作为某数的补值出现过：
- 不在字典中：把 target - nums[i] 写入，记下当前下标；
- 在字典中：前面已经见过它的配对，直接返回。

假设 [3, 2, 4]，目标是 6：

第一轮，字典为空，以 3 为 key 取不出任何值，则以 6-3=3 为 key 写入 index 0；
第二轮，字典为 {3: 0}，以 2 为 key 没有值，以 4 为 key 写入 index 1；
第三轮，字典为 {3: 0, 4: 1}，以 4 为 key 取出 1，说明之前已经找到 4 的配对，下标为 1，返回 [1, 2]。

"""


def two_sum(nums: list, target: int) -> list:
    d = dict()
    for i in range(len(nums)):
        value = d.get(nums[i])
        if value != None:
            return [i, value]
        d.setdefault(target - nums[i], i)
    return [-1, -1]
