# 算法学习路线图

按 **题型** 推进：每种题型 **1 道讲解题**（吃透不变量 + 默写）+ **2 道练习题**（一道巩固、一道变式）。  
毕业标准与 [README](README.md) 相同：本地 pytest → 删代码默写 → LeetCode AC。  
节奏：每周 4 次 × 30 分钟；每次先 10 分钟默写 **已毕业** 的题（从下面「复习池」轮换）。

---

## 复习池（已毕业）

| 题型 | 题号 |
| --- | --- |
| 同向双指针 | 283, 27 |
| 滑动窗口 | 209 |

---

## 阶段一：数组与指针（打基础）

### 1. 同向双指针 — 已完成

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [283. 移动零](https://leetcode.com/problems/move-zeroes/) | `e283_move_zeros` | `slow` = 下一个写入位置 |
| 练习 | [27. 移除元素](https://leetcode.com/problems/remove-element/) | `e27_remove_element` | 同上，返回 `k` |
| 练习 | [26. 删除有序数组中的重复项](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) | `e26_remove_duplicates_from_sorted_array` | 有序 + 慢指针写不重复段 |

### 2. 滑动窗口 — 209 已完成，补 2 练

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [209. 长度最小的子数组](https://leetcode.com/problems/minimum-size-subarray-sum/) | `m209_min_subarray_len` | 扩 `right`，够和则 `while` 缩 `left` |
| 练习 | [3. 无重复字符的最长子串](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | `m3_longest_substring_without_repeating` | 窗口内用 `set`/字典判重复 |
| 练习 | [643. 子数组最大平均数 I](https://leetcode.com/problems/maximum-average-subarray-i/) | `e643_max_average_subarray_i` | 固定长度窗口，入门变式 |

### 3. 对撞双指针（与「同向」分开记）

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [167. 两数之和 II](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | `m167_two_sum_ii` | 有序，左右向中间夹 |
| 练习 | [11. 盛最多水的容器](https://leetcode.com/problems/container-with-most-water/) | `m11_container_with_most_water` | 移动较短边 |
| 练习 | [15. 三数之和](https://leetcode.com/problems/3sum/) | `m15_3sum` | 排序 + 固定一数 + 167 |

---

## 阶段二：哈希与栈

### 4. 哈希表

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [1. 两数之和](https://leetcode.com/problems/two-sum/) | `e1_two_sum` | 遍历时查 `target - x` 是否在表里 |
| 练习 | [217. 存在重复元素](https://leetcode.com/problems/contains-duplicate/) | `e217_contains_duplicate` | 集合判重 |
| 练习 | [242. 有效的字母异位词](https://leetcode.com/problems/valid-anagram/) | `e242_valid_anagram` | 计数 / 排序 |

### 5. 栈

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [20. 有效的括号](https://leetcode.com/problems/valid-parentheses/) | `e20_valid_parentheses` | 左括号入栈，右括号匹配 |
| 练习 | [155. 最小栈](https://leetcode.com/problems/min-stack/) | `m155_min_stack` | 数据结构设计 |
| 练习 | [739. 每日温度](https://leetcode.com/problems/daily-temperatures/) | `m739_daily_temperatures` | 单调栈（下一个更大） |

---

## 阶段三：二分与链表

### 6. 二分查找

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [704. 二分查找](https://leetcode.com/problems/binary-search/) | `e704_binary_search` | `left`, `right`, 中点与区间缩小 |
| 练习 | [35. 搜索插入位置](https://leetcode.com/problems/search-insert-position/) | `e35_search_insert_position` | 同模板 |
| 练习 | [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | `m34_find_first_and_last_position` | 左右边界二分 |

### 7. 链表

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [206. 反转链表](https://leetcode.com/problems/reverse-linked-list/) | `e206_reverse_linked_list` | 三指针迭代 / 递归 |
| 练习 | [21. 合并两个有序链表](https://leetcode.com/problems/merge-two-sorted-lists/) | `e21_merge_two_sorted_lists` |  dummy 头结点 |
| 练习 | [141. 环形链表](https://leetcode.com/problems/linked-list-cycle/) | `e141_linked_list_cycle` | 快慢指针 |

---

## 阶段四：二叉树

### 8. 树 — DFS（递归）

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [104. 二叉树的最大深度](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | `e104_maximum_depth_of_binary_tree` | 后序：深度 = max(左,右)+1 |
| 练习 | [100. 相同的树](https://leetcode.com/problems/same-tree/) | `e100_same_tree` | 同步递归 |
| 练习 | [226. 翻转二叉树](https://leetcode.com/problems/invert-binary-tree/) | `e226_invert_binary_tree` | 交换左右递归 |

### 9. 树 — BFS（层序）

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [102. 二叉树的层序遍历](https://leetcode.com/problems/binary-tree-level-order-traversal/) | `m102_binary_tree_level_order_traversal` | 队列按层 |
| 练习 | [199. 二叉树的右视图](https://leetcode.com/problems/binary-tree-right-side-view/) | `m199_binary_tree_right_side_view` | 每层最后一个 |
| 练习 | [637. 二叉树的层平均值](https://leetcode.com/problems/average-of-levels-in-binary-tree/) | `e637_average_of_levels_in_binary_tree` | 层内聚合 |

---

## 阶段五：堆、图、回溯、DP、贪心

### 10. 堆（优先队列）

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [703. 数据流中的第 K 大元素](https://leetcode.com/problems/kth-largest-element-in-a-stream/) | `e703_kth_largest_element_in_a_stream` | `heapq` 小根堆维护 K 个 |
| 练习 | [215. 数组中的第 K 个最大元素](https://leetcode.com/problems/kth-largest-element-in-an-array/) | `m215_kth_largest_element_in_an_array` | 快选 / 堆 |
| 练习 | [347. 前 K 个高频元素](https://leetcode.com/problems/top-k-frequent-elements/) | `m347_top_k_frequent_elements` | 频次 + 堆 |

### 11. 图 — DFS/BFS

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [200. 岛屿数量](https://leetcode.com/problems/number-of-islands/) | `m200_number_of_islands` | 网格 DFS/BFS 连通块 |
| 练习 | [133. 克隆图](https://leetcode.com/problems/clone-graph/) | `m133_clone_graph` | 邻接表 + 访问标记 |
| 练习 | [417. 太平洋大西洋水流问题](https://leetcode.com/problems/pacific-atlantic-water-flow/) | `m417_pacific_atlantic_water_flow` | 多源 DFS |

### 12. 回溯

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [78. 子集](https://leetcode.com/problems/subsets/) | `m78_subsets` | 选 / 不选，递归树 |
| 练习 | [46. 全排列](https://leetcode.com/problems/permutations/) | `m46_permutations` | 用 `used` 标记 |
| 练习 | [39. 组合总和](https://leetcode.com/problems/combination-sum/) | `m39_combination_sum` | 可重复选，剪枝 |

### 13. 一维动态规划

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [70. 爬楼梯](https://leetcode.com/problems/climbing-stairs/) | `e70_climbing_stairs` | `dp[i]` 从前面状态转移 |
| 练习 | [198. 打家劫舍](https://leetcode.com/problems/house-robber/) | `m198_house_robber` | 抢 / 不抢 |
| 练习 | [322. 零钱兑换](https://leetcode.com/problems/coin-change/) | `m322_coin_change` | 完全背包最值 |

### 14. 贪心

| 角色 | 题号 | 目录名 | 要点 |
| --- | --- | --- | --- |
| 讲解 | [121. 买卖股票的最佳时机](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | `e121_best_time_to_buy_and_sell_stock` | 维护最低买入价 |
| 练习 | [55. 跳跃游戏](https://leetcode.com/problems/jump-game/) | `m55_jump_game` | 最远可达 |
| 练习 | [45. 跳跃游戏 II](https://leetcode.com/problems/jump-game-ii/) | `m45_jump_game_ii` | 最少步数贪心 |

---

## 执行顺序（一张表）

按行从上到下，**同一行内先讲解后两道练习**；上一题型三道都毕业再进下一题型。

```
1  同向双指针     283 → 27 → 26          [283,27 已完成，可选补 26]
2  滑动窗口       209 → 3 → 643          [209 已完成]
3  对撞双指针     167 → 11 → 15
4  哈希           1 → 217 → 242          [当前：1]
5  栈             20 → 155 → 739
6  二分           704 → 35 → 34
7  链表           206 → 21 → 141
8  树 DFS         104 → 100 → 226
9  树 BFS         102 → 199 → 637
10 堆             703 → 215 → 347
11 图             200 → 133 → 417
12 回溯           78 → 46 → 39
13 一维 DP        70 → 198 → 322
14 贪心           121 → 55 → 45
```

共 **14 个题型 × 3 题 ≈ 42 道核心题**。按每周在新题型上推进约 1 个「讲解 + 部分练习」，**大约 10～14 个月** 走完（含默写与复习）；忙季只维持复习池 + 当前一道新题即可。

---

## 和 NeetCode / 150 的关系

本计划覆盖 [NeetCode Roadmap](https://neetcode.io/roadmap) 与 LeetCode Top Interview **大部分高频模式**。roadmap 上同类型的其它题，当作 **第四、五道** 可选加练，不必纳入毕业清单。

---

## 新增题目时

在 `leetcode/` 下建目录：`{e|m|h}{题号}_{slug}/`，内含 `solution.py`、`test_solution.py`。  
讲解题卡住超过两次 30 分钟，可以问 AI 讲不变量；**仍须默写 AC** 才算过。
