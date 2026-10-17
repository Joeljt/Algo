"""1. 两数之和

https://leetcode.com/problems/two-sum/

整数数组 nums，整数 target。
找出和为 target 的两个不同下标 i、j，返回 [i, j]（顺序任意）。保证恰好一组解。

决定性条件：
- 数组未排序：对撞双指针（167）不适用，应想到哈希查 complement。
- 只需一组解：见到 complement 在表里即可返回，不必存所有配对。
- 下标不能复用同一元素：存入表的是「已扫过的下标」，当前数先查再存。

不变量：

步骤：
"""


def two_sum(nums: list, target: int) -> list:
    raise NotImplementedError
