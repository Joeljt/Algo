"""3. 无重复字符的最长子串

https://leetcode.cn/problems/longest-substring-without-repeating-characters/

字符串 s，求不含重复字符的最长子串长度。

决定性条件：
- 子串必须连续：只能滑动窗口，不能排序后双指针。
- 字符不可重复：右扩后若重复，必须缩左端直到窗口内无重复（或按上次出现位置跳 left）。
- 求最长：在合法窗口的每一刻用 max 更新，不能只记当前长度。

不变量（主函数：字典记上次下标）：
- last_index[c]：字符 c 最近一次出现的下标。
- left_exclusive：窗口左边界再左侧一格；当前窗口为 s[left_exclusive + 1 : right]，长度 = right - left_exclusive（初始 -1 表示空窗口）。
- 每轮 for 开始时，上述窗口内无重复字符，且 left_exclusive 只增不减。
- 若 s[right] 曾在窗口内出现，则 left_exclusive 至少移到该字符旧下标；用 max(left_exclusive, last_index[ch]) 避免墙往回退。
- 更新 last_index[ch] = right 后，窗口 s[left_exclusive + 1 : right] 仍无重复。

步骤：

pwwkew

依次遍历整个字符串，过程中记录遇到过的最长的不重复子串
然后检查当前的元素是否已经有过重复的了，如果有就移动左边界，同时更新长度信息

第一轮：
left = 0, right = 0, char = p, substr = p, longest = 1

第二轮
left = 0, right = 1, char = w, substr = pw, longest = 2

第三轮
left = 0, right = 2, char = w, substr = pww, 需要一直更新左边界（收窄窗口），直到不再有重复元素

第四轮
left = 2（收窄左边界）, right = 3（继续扩大右边界）, char = k, substr = wk, longest = 2

第五轮
left = 2, right = 4, char = e, substr = wke, longest = 3

第六轮
left = 2, right = 5, char = w, substr = wkew，更新左边界，直到不再有重复元素，longest = 3

过程中仍然要注意，不要把已经得到过的最大值丢掉，利用 max 做比较，否则窗口收窄以后之前的信息就丢失了

但是这个解法有个缺点，左指针并不需要依次递增，即多了很多无谓的循环。
发现有重复字符时，可以直接把左指针移动到第一个重复字符的下一个位置即可。
也就是后面这个字典版本的，直接跳，而不是循环减，可以提高一部分效率
"""

def length_of_longest_substring(s: str) -> int:
    """字典版：记上次下标，重复时左边界一步跳（与 length_of_longest_substring 同思路）。"""
    last_index: dict[str, int] = {}
    left_exclusive = -1  # 窗口为 s[left_exclusive + 1 : right]，长度 = right - left_exclusive
    best_len = 0

    for right, ch in enumerate(s):
        if ch in last_index:
            left_exclusive = max(left_exclusive, last_index[ch])
        last_index[ch] = right
        best_len = max(best_len, right - left_exclusive)

    return best_len

def length_of_longest_substring3(s: str) -> int:
    left = 0
    longest = 0
    window = set()

    for right, char in enumerate(s):
        # 先问：窗口里已经有这个字符了吗？有就缩左端，直到没有
        while char in window:
            window.remove(s[left])
            left += 1
        # 现在窗口里没有 char，放心加进去
        window.add(char)
        longest = max(longest, right - left + 1)

    return longest

def length_of_longest_substring2(s: str) -> int:
    left = 0
    longest = 0
    window = [] # 维护一个滑动窗口

    for right, char in enumerate(s):
        # 把最新考察的元素添加到窗口里
        window.append(char)
        # 检查新加入的元素是否有重复，如果有就缩减左边界，直到其不再重复为止
        while window.count(char) > 1:
            window.remove(s[left])
            left += 1
        # 如果窗口内没有重复元素，就记录一下当前的最大长度
        # 这里要注意做 max 比较，避免后面窗口缩减以后，把之前已经得到过的最大子串丢失掉
        longest = max(longest, right - left + 1)
    
    return longest

def length_of_longest_substring1(s: str) -> int:
    left = 0
    longest = 0
    for right, char in enumerate(s):
        while char in s[left:right]:
            left += 1
        longest = max(longest, right - left + 1)

    return longest

def length_of_longest_substring_set_clear(s: str) -> int:
    """集合版：右扩，重复则从 left 逐格缩。"""
    left = 0
    best_len = 0
    window_chars = set()

    for right, ch in enumerate(s):
        while ch in window_chars:
            window_chars.remove(s[left])
            left += 1
        window_chars.add(ch)
        best_len = max(best_len, right - left + 1)

    return best_len

if __name__ == '__main__':
    print(length_of_longest_substring("abcabcbb"))
