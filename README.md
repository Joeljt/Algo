# 算法练习

用 Python 手写 LeetCode。数据结构用语言自带的。

**完整路线（每种题型 1 讲解 + 2 练习、先后顺序）见 [PLAN.md](PLAN.md)。**

每周四次，每次 30 分钟。错过一次，下一次仍然做 30 分钟。

## 一道题怎么写

1. 在 `solution.py` 顶部用中文写下不变量和步骤。
2. 自己把步骤写成 Python。可以查语法，不要让 AI 把函数写出来。
3. 运行 `.venv/bin/pytest`。
4. 通过后删掉函数体默写，LeetCode AC，这道题才算完成。

## 当前位置（详见 PLAN 执行顺序）

| 状态 | 内容 |
| --- | --- |
| 已毕业 | 同向双指针 283、27；滑动窗口 209 |
| **进行中** | 哈希 — [1. 两数之和](leetcode/e1_two_sum/solution.py) |
| 下一步 | 见 [PLAN.md](PLAN.md) 执行顺序；`leetcode/` 下已建好至 **栈** 为止的题面与 pytest 模板 |

每次练习：先 10 分钟默写复习池（283 / 27 / 209 轮换），再做 PLAN 里当前题型。

## 目录

一题一个目录：`leetcode/{e|m|h}{题号}_{slug}/`，内含 `solution.py`、`test_solution.py`。

## 命令

```bash
python3 -m venv .venv
.venv/bin/pip install "pytest>=7,<9"
.venv/bin/pytest
.venv/bin/pytest leetcode/e1_two_sum
```
