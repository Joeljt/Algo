# 算法练习

用 Python 手写 LeetCode。数据结构用语言自带的。

每周四次，每次 30 分钟。错过一次，下一次仍然做 30 分钟。

## 一道题怎么写

1. 在 `solution.py` 顶部用中文写下不变量和步骤。
2. 自己把步骤写成 Python。可以查语法，不要让 AI 把函数写出来。
3. 运行 `.venv/bin/pytest`。
4. 通过后删掉函数体，从 `raise NotImplementedError` 再写一遍。默写通过，这道题才算完成。

## 进度

同向双指针已完成：[283. 移动零](leetcode/e283_move_zeros/solution.py)、[27. 移除元素](leetcode/e27_remove_element/solution.py)。两端往中间夹的双指针先不补。

当前题型是滑动窗口。每次练习先花 10 分钟默写一道已完成的题，默写通过再做新题。

## 眼下的队列

- [x] [283. 移动零](leetcode/e283_move_zeros/solution.py)
- [x] [27. 移除元素](leetcode/e27_remove_element/solution.py)
- [ ] [209. 长度最小的子数组](leetcode/m209_min_subarray_len/solution.py) — 滑动窗口

不用完成题数计进度。一种题型能默写代表题，再做一道变体，然后换下一种。

## 目录

一题一个目录，放在 `leetcode/` 下。目录名以难度开头：`e` easy，`m` medium，`h` hard。例如 `leetcode/e283_move_zeros/`，里面是 `solution.py` 和 `test_solution.py`。

## 命令

```bash
python3 -m venv .venv
.venv/bin/pip install "pytest>=7,<9"
.venv/bin/pytest
.venv/bin/pytest leetcode/m209_min_subarray_len
```
