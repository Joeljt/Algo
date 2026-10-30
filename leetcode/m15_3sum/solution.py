"""15. 三数之和

https://leetcode.cn/problems/3sum/

整数数组 nums，找出所有和为 0 的三元组，不重复。

不变量：

步骤：

最简单的就是三重 for 循环，直接开始比，有相加等于 0 的就记录下来，然后排序再用 set 去重，得到不重复的三元组列表。
但是复杂度爆炸，N*N*N，会超时

"""

def three_sum(nums: list) -> list:
    return []

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
    v = three_sum1([-1, 0, 1, 2, -1, -4])
    print(v)


