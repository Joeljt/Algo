"""217. 存在重复元素

https://leetcode.com/problems/contains-duplicate/

整数数组 nums，是否存在某个值至少出现两次。

决定性条件：
- 只需判断「有没有重复」，不必返回下标或次数：第二次见到即可 True。
- 数组未排序：不能靠相邻比较，要用哈希记下已经扫过的值。
- 全不重复或空数组：扫完都没撞上，返回 False。

不变量：
d 的 key 是已扫过的值，value 恒为 1，只表示「出现过」。
扫到下标 i 时，d 只含 nums[0 .. i-1]。
若 d.get(nums[i]) 不是 None，则 nums[i] 在前面已经出现过。

步骤：
遍历数组，每次先查当前值是否已在字典中：
- 在：已经重复，返回 True；
- 不在：把当前值写入字典，继续。
全部写完都没撞上，返回 False。

假设 [1, 2, 3, 1]：
第一轮，字典为空，1 不在，写入 {1: 1}；
第二轮，2 不在，写入 {1: 1, 2: 1}；
第三轮，3 不在，写入 {1: 1, 2: 1, 3: 1}；
第四轮，1 已在字典中，返回 True。

"""


def contains_duplicate(nums: list) -> bool:
    d = {}
    for i in range(len(nums)):
        if d.get(nums[i]) != None:
            return True
        d[nums[i]] = 1
    return False
