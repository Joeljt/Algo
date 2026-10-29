"""128. 最长连续序列

https://leetcode.com/problems/longest-consecutive-sequence/

未排序整数数组 nums，返回其中最长连续数字序列的长度。要求时间复杂度 O(n)。

决定性条件：
- 要求 O(n)，所以不能排序。先用 set 去重，后面靠集合判断某个数在不在。
- set 的 in 是 O(1)。这 n 次查找本身是 O(n)，不会再乘出一个 n。
- 只从起点往后数。如果每个数都从自己往后数，完全连续时是 N * N。

不变量：
- 转成 set 之后，每个数只出现一次。
- x - 1 在集合里，当前元素就不是连续区间的起点，跳过，只是访问一下。
- x - 1 不在集合里，x 就是这段的起点。从 x 开始查 x、x + 1、x + 2，直到找不到为止。
- 每段区间的长度独立计算，每次重置，只保留最长的那个。
- 每个数最多被内层数一次：外层遍历一遍是 N，内层加起来也是 N。最坏是 N + N，不是 N * N，所以是 O(n)。

步骤：
先用 set 对元素去重，不需要排序。
然后遍历每一项，优先检查 x - 1 是否在集合内：
- 在：当前元素不是连续区间的起始元素，直接跳过。
- 不在：x 是区间起点，从 x 开始检查后面的数是否在集合内，直到找不到为止。
  这一段的长度从 0 重新数，和已知的最长比较，只保留更长的。
- 如果当前长度的两倍已经大于集合大小，剩下的数不够再组成更长的一段，可以提前结束。

假设 [100, 4, 200, 1, 3, 2]，去重后是这 6 个数。集合的遍历顺序不固定，哪一个先遇到不影响，因为只有起点才会把这一段数完：
- 100：99 不在，是起点。101 不在，长度 1。
- 4：3 在，不是起点，跳过。
- 200：199 不在，是起点。201 不在，长度 1。
- 1：0 不在，是起点。1、2、3、4 都在，5 不在，长度 4。
- 3：2 在，跳过。
- 2：1 在，跳过。
最长是 4。

对 set 的认识（128 做完才把这几件事连上）：
我以前只知道 map 是 O(1)，因为有明确的 key、value。set 我一直当去重的 list 来用，还会写 set[0]。虽然知道它底层是 hashtable，但没把它当成一张表。

set 和去重 list 的核心区别是底层结构，不是「里面有没有重复元素」：
- list 是数组，按下标存。in 只能从头扫到尾，是 O(n)。就算事先去过重，查找还是 O(n)。
- set 是 hashtable。元素本身就是 key，没有另外的 value。add 就是放入 key，遍历就是遍历这些 key。
- in 和 map 查 key 是同一条路：算哈希，跳到桶里看在不在。单次 add、单次 in 平均 O(1)。
- in 只回答在不在。map.get(key) 找到后还会把 value 交出来。
- 去重是 key 不能重复的结果，不是 set 的原始目的。list(set(nums)) 变回数组之后，O(1) 查找也丢了。
- 没有下标，所以没有 set[0]。

遍历没有顺序。语言不保证插入顺序，也不保证大小顺序。集合不增删时，同一次运行里再遍历一次，顺序不变；加一个或删一个，剩下的元素也可能换位置。
实测按 100, 4, 200, 1, 3, 2 插入，遍历得到 [1, 2, 3, 100, 4, 200]。dict 从 Python 3.7 起按插入顺序遍历 key，set 没有这个保证。需要顺序就用 list，或者 sorted(set)。

整张表走一遍是 O(n)，其中每一步查找是 O(1)。128 的最坏情况是外层 N 加内层 N，不是 N * N。

不是所有叫 set 的都是 O(1)。Python 的 set、Java 的 HashSet、C++ 的 unordered_set、Go 的 map[T]struct{}、JavaScript 的 Set 才是哈希。C++ 的 set、Java 的 TreeSet 是树，查找是 O(log n)。

反复问「这个值在不在」时，先放进 set，是常用的优化，多花 O(n) 空间。只查一次，建集合的成本就抵消了。数轴又短又密时，布尔数组往往比哈希更快，下标本身就是位置。

常用操作：set() 建空集（{} 是空 dict）、add、in / not in、remove（没有会报错）、discard（没有也不报错）、len、for x in s。
| & - ^ 是并集、交集、差集、对称差，得到的是新 set。元素必须能算哈希，list 不能放进去。

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
