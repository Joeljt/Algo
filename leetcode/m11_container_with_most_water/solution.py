"""11. 盛最多水的容器

https://leetcode.com/problems/container-with-most-water/

非负整数数组 height，选两条竖线与 x 轴围成容器，求最大容积。

决定性条件：
- 容积 = min(左高, 右高) × 宽度。短边才能形成封闭容器，决定最终大小；宽度是两端下标之差。
- 两端向内移动时宽度一定变小。推进更高的一侧：短边还在，高度上限不变，面积只会不变或变小。
  所以只能推进更短的一侧，才可能换到更高的短边，有机会补回变窄的宽度。
- 两边一样高时推哪一侧都行，不会漏解。

不变量：
- left 在左端，right 在右端，始终 left < right。
- largest 记录到目前为止见过的最大面积。
- 当前面积用 min(height[left], height[right]) * (right - left) 更新。
- 推进的是更短的一侧；被丢掉的那一端，不可能再和另一端组成更大的容器。

步骤：
对撞指针，从两端开始向内。每次先用短边和宽度算出当前面积，更新最大值。
然后推进更短的那一侧：短边已经决定了容器的体积，只有换掉它才可能变大。
两边相等时走 else，右移右指针也可以。

假设 [1, 8, 6, 2, 5, 4, 8, 3, 7]：
- left=0, right=8，高 1 和 7，面积 min(1,7)×8=8。左边更短，left 右移；
- left=1, right=8，高 8 和 7，面积 min(8,7)×7=49。右边更短，right 左移；
- 继续向内，后面算出的面积都不超过 49，最终返回 49。

"""


def max_area(height: list) -> int:
    left = 0
    right = len(height) - 1
    largest = 0

    while left < right:
        l_val = height[left]
        r_val = height[right]

        # 记录当前已有的最大面积
        largest = max(largest, min(l_val, r_val) * (right - left))

        # 如果左值更小，就应该推进左值，去找更大的上限
        # 因为短边已经决定了容器的面积
        if l_val < r_val:
            left += 1
        else:
            right -= 1
    
    return largest

if __name__ == "__main__":
    max_area([1, 8, 6, 2, 5, 4, 8, 3, 7])


