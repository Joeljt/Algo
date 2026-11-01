"""15. 三数之和

https://leetcode.cn/problems/3sum/

整数数组 nums，找出所有和为 0 的三元组，不重复。

决定性条件：
- 要全部不重复的三元组，不是 LC 1 那种「恰好一对」。固定一个数之后，右边变成两数之和。
- 两数之和可以用哈希求补（不要求有序），也可以排序后对撞（要求有序）。两种都能算对。
- 本题更适合排序 + 对撞：相同值挨在一起，方便跳过重复；nums[i] > 0 以后后面更大，可以直接 break。
  这个剪枝往往比内层 while 跳重复更管用，全 0 的大数据尤其明显。
- 三重循环再 set 去重是对的，但是 N*N*N，会超时。

不变量（three_sum：排序 + 固定 nums[i] + 右侧对撞）：
- 数组已非递减。left、right 在 i 右侧，始终 left < right。
- target = -nums[i]，要找 left、right 使两数之和等于 target。
- nums[i] > 0：后面全是更大的正数，不可能再有和为 0 的三元组，外层结束。
- nums[i] == nums[i-1]：这个固定值已经找过，跳过。
- 和偏大右移，偏小左移；相等就记录一组，两端各进一步。

步骤：
把题目转化成两数之和：
1. 先排序；
2. 遍历每个 nums[i]，target = -nums[i]；
3. 在 i 后面的子数组里，对撞找两数之和为 target，和 nums[i] 组成三元组。

假设 [-1, 0, 1, 2, -1, -4]，排序后 [-4, -1, -1, 0, 1, 2]：
- i 在 -4，target=4，左右对撞找不到；
- i 在第一个 -1，target=1，找到 (-1, 0, 1)、(-1, -1, 2) 这类解；
- 第二个 -1 与前一个相同，跳过；
- 碰到 > 0 的固定值就结束。

写法对比：
- three_sum：排序 + 对撞。推荐提交。
- three_sum2：排序后仍用哈希求补。外层同样可以 >0 break、跳过重复 i，逻辑正确；
  但每个 i 都要建字典，全 0 时内层仍可能对同一组 (0,0,0) 命中很多次，不如对撞稳。
- three_sum1：三重循环 + set，超时。

"""

def three_sum(nums: list) -> list:
    nums = sorted(nums)
    result = set()

    for i in range(len(nums)):

        # 数组已排序，所有 >0 的值都不需要再看，因为后面的值更大，不可能等于 0
        if nums[i] > 0: break

        # 已经看过的重复值直接跳过
        if i > 0 and nums[i] == nums[i - 1]: continue

        # 当前元素右侧的子数组，作为寻找两数之和的数组范围
        left = i + 1
        right = len(nums) - 1
        # 当前元素对 0 求补，即剩下两个值的和
        target = -nums[i]

        while left < right:
            left_value = nums[left]
            right_value = nums[right]

            # 两端指针对撞，确定和目标值的差距，并移动两端指针
            if left_value + right_value > target:
                right -= 1
            elif left_value + right_value < target:
                left += 1
            else:
                result.add((nums[i], left_value, right_value))
                left += 1
                right -= 1

    return list(result)

def three_sum2(nums: list) -> list:
    nums = sorted(nums)
    result = set()

    for i in range(len(nums)):

        # 基于排序做剪枝优化
        if nums[i] > 0: break
        if i > 0 and nums[i] == nums[i - 1]: continue

        # 当前元素对 0 求补，作为两数之和的 target
        target = -nums[i]
        dic = dict() 

        for j in range(i + 1, len(nums)):
            # 检查字典里有没有当前元素相对于 target 的补
            # 如果有说明之前已经查看过了，也就找到了答案，否则就纳入字典中
            d_value = dic.get(nums[j])

            # 如果当前元素在字典里有值，就说明之前添加过，有与其对应的值
            if d_value != None:
                # nums[i] 是外层，nums[j] 是内层，d_value 是补，三者构成三元组
                target_list = sorted([nums[i], nums[j], d_value]) 
                result.add(tuple(target_list))
            else:
                # 字典里没有当前值的补，用该补值做 key，记录当前值，方便后面找到补的时候直接知道对应的补是多少
                dic.setdefault(target - nums[j], nums[j])

    return list(result)

def three_sum1(nums: list) -> list:
    result = set()
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            for k in range(j + 1, len(nums)):
                if nums[i] + nums[j] + nums[k] == 0:
                    dedup = sorted([nums[i], nums[j], nums[k]])
                    result.add(tuple(dedup))
    return list(result)

if __name__ == "__main__":
    v = three_sum([-1, 0, 1, 2, -1, -4])
    print(v)


