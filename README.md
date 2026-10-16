# 算法练习

用 Python 手写 LeetCode。数据结构用语言自带的。

题型顺序、每周节奏、过关标准、卡住怎么办，都在 [PLAN.md](PLAN.md)。

## 一道题怎么写

1. 在 `solution.py` 顶部用中文写下不变量和变量含义。
2. 自己把步骤写成 Python。可以查语法，不要让 AI 把函数写出来。
3. 运行 `.venv/bin/pytest <题目目录>`。
4. 讲解题隔天从空文件在 LeetCode 默写到 AC，才算完成。

## 当前位置

| 状态 | 内容 |
| --- | --- |
| 已完成 | 同向双指针 283、27；滑动窗口 209 |
| 进行中（第 0 周） | 滑动窗口收尾：[3](leetcode/m3_longest_substring_without_repeating/solution.py)、[643](leetcode/e643_max_average_subarray_i/solution.py) |
| 下一周 | 哈希：[1](leetcode/e1_two_sum/solution.py)、[217](leetcode/e217_contains_duplicate/solution.py)、[49](leetcode/m49_group_anagrams/solution.py) |

模板只建到下一周为止，其余题型到了那一周再建。

## 命令

```bash
python3 -m venv .venv
.venv/bin/pip install "pytest>=7,<9"
.venv/bin/pytest leetcode/m3_longest_substring_without_repeating
```
