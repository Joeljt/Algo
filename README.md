# 算法练习

用 Python 手写 LeetCode。数据结构用语言自带的。

每周四次，每次 30 分钟。错过一次，下一次仍然做 30 分钟。

## 一道题怎么写

1. 在 `solution.py` 顶部用中文写下不变量和步骤。
2. 自己把步骤写成 Python。可以查语法，不要让 AI 把函数写出来。
3. 运行 `.venv/bin/pytest`。
4. 通过后删掉函数体，从 `raise NotImplementedError` 再写一遍。LeetCode 上再默写 AC，这道题才算完成。

## 进度

- 同向双指针：[283](leetcode/e283_move_zeros/solution.py)、[27](leetcode/e27_remove_element/solution.py)
- 滑动窗口：[209](leetcode/m209_min_subarray_len/solution.py)

每次练习先花 10 分钟默写一道已完成的题（283 / 27 / 209 轮换），默写通过再做新题。

## 眼下的队列

- [x] [283. 移动零](leetcode/e283_move_zeros/solution.py)
- [x] [27. 移除元素](leetcode/e27_remove_element/solution.py)
- [x] [209. 长度最小的子数组](leetcode/m209_min_subarray_len/solution.py)
- [ ] [1. 两数之和](leetcode/e1_two_sum/solution.py) — 哈希：遍历时记下「还缺哪个数」

滑动窗口变体（[3. 无重复字符的最长子串](https://leetcode.com/problems/longest-substring-without-repeating-characters/)）等三类题都稳了再加，不必现在开。

## 之后（按顺序，一种毕业再开下一种）

1. 哈希 — 1 代表题，可选变体 [217. 存在重复元素](https://leetcode.com/problems/contains-duplicate/)（更简单，想热身先做）
2. 栈 — [20. 有效的括号](https://leetcode.com/problems/valid-parentheses/)
3. 二分 — [704. 二分查找](https://leetcode.com/problems/binary-search/) 或 [35. 搜索插入位置](https://leetcode.com/problems/search-insert-position/)

## 目录

一题一个目录，放在 `leetcode/` 下。目录名以难度开头：`e` easy，`m` medium，`h` hard。例如 `leetcode/e283_move_zeros/`，里面是 `solution.py` 和 `test_solution.py`。

## 命令

```bash
python3 -m venv .venv
.venv/bin/pip install "pytest>=7,<9"
.venv/bin/pytest
.venv/bin/pytest leetcode/e1_two_sum
```
