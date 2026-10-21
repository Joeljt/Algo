"""49. 字母异位词分组

https://leetcode.com/problems/group-anagrams/

字符串数组 strs，把字母异位词放在同一组，返回所有分组（组间、组内顺序任意）。

决定性条件：
- 只要分组，不要求顺序：用 key 把词存进 map，最后取 values 即可。
- 重点是设计 key，且要满足两个方向：
  异位词 -> key 相同；非异位词 -> key 不同（否则会把不同的词分到同一组）。
- key 必须可哈希（不可变），list 不能当 key，要转成 tuple 或 str。

不变量（group_anagrams：每个词单独计数，26 位次数数组转 tuple 当 key）：
- d 的 key 是某个词的字母计数（a-z 各出现几次），value 是具有这个计数的所有原词。
- 扫到下标 i 时，strs[0 .. i-1] 已经按计数分好组，同一个 key 下的词互为异位词。
- 计数是对「每个单词自己」数，不是把所有单词混在一起数。

步骤：
遍历每个单词，给它算出一个 key，用 key 把它存进 map，最后输出 map 的 values：
1. 每个单词单独建一个 26 个元素的数组，起始值全为 0；
2. 遍历单词的每个字母，用 ord(字母) - ord('a') 得到 0-25 的下标，对应位置 +1；
3. 数组转成 tuple 当 key（list 不能当 key）。异位词字母完全相同，key 也完全相同；
4. key 不在 map 里就先建空列表，再把原词追加进去；
5. 返回 list(d.values())，d.values() 不是 list，需要转换。

假设 ["eat", "tea", "tan"]：
- "eat" 的计数里 a、e、t 各 1，其余 0，存入 {该计数: ["eat"]}；
- "tea" 的计数和 "eat" 完全一样，追加到同一组：["eat", "tea"]；
- "tan" 的计数里 a、n、t 各 1，是新 key，另起一组 ["tan"]。

写法对比（key 怎么设计）：
- 排序（group_anagrams1）：sorted(word) 再 join 成字符串。异位词排序后相同，
  复杂度 O(n * k log k)。通用，任何语言都能用，不依赖字符范围。
- 计数 tuple（group_anagrams）：O(n * k)，但要知道字符范围（这里是 26 个小写字母）。

几个撞 key 的坑（都是「key 里的信息丢太多」）：
- ASCII 码相加：加法拆不回去，"ad" 和 "bc" 的和可能相同。
- 26 位位掩码：只记「有没有出现」，不记次数，"aab" 和 "ab" 掩码相同，但不是异位词。
- 计数用字符串拼接：必须加分隔符，否则次数 [1, 11] 和 [11, 1] 都变成 "111"。
  而且 join 只能拼 str，要先 map(str, arr)。

扩展：质数乘积做 key
- 给 a-z 各分配一个不同的质数（a=2, b=3, c=5, ... z=101），一个词的 key 是所有字母对应质数的乘积。
- 乘法有交换律，字母顺序不影响结果，所以异位词乘积相同。
- 质因数分解唯一，乘积相同就说明字母和各自次数都相同，所以非异位词不会撞。
  同时满足两个方向，比 ASCII 求和、位掩码都强。
- 代价：依赖大整数。Python 的 int 不溢出，能用；Java、Go、C++ 的定长整数遇到长单词会溢出，
  溢出后不同的词可能得到相同 key。乘积越大乘法也越慢。
- 空串乘积是初始值 1。通用性不如排序和计数 tuple，当作了解即可。

没有 tuple 的语言：把计数序列变成可哈希的值。
- 带分隔符拼字符串，最通用（如 "#1#0#2#..."，每个次数前后都加）；
- 或用语言自带的可比较类型：Java 的 List<Integer>（不是 int[]）、Go 的 [26]int（不是切片）、C++ 的 vector<int>；
- 实在不行就退回排序。
"""

def group_anagrams(strs: list) -> list[list[str]]:
    d = {}
    base = ord('a')
    for i in range(len(strs)):
        cur = strs[i]

        # 每个单词都单独构建一个 26 个元素的数组，起始值为 0
        # -'a' 可以让每个字母偏移到正确的数组下标，严格对应 a-z 的字母序
        # python 要用 ord() 转成 char
        arr = [0] * 26
        for s in cur:
            arr[ord(s) - base] += 1

        # 重新构建 hashkey，异位词因为字母完全相同，key 也会完全相同
        key = tuple(arr)
        if key not in d:
            d[key] = []
        d[key].append(cur)

    return list(d.values()) 

def group_anagrams1(strs: list) -> list[list[str]]:
    d = {}
    for i in range(len(strs)):
        cur = strs[i]
        # 遍历每一个字符串，对字符串进行排序后作为 key 存储当前字符串
        # 异位词排序后相同，可以作为 hashkey 对原始数据进行分组
        key = "".join(sorted(cur))
        if d.get(key) != None:
            d[key].append(cur)
        else:
            d[key] = [cur]
    return list(d.values())

if __name__ == "__main__":
    group_anagrams(["eat", "tea", "tan", "ate", "nat", "bat"])