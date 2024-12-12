## 冒泡排序

冒泡排序是一种 $O(n^2)$ 的排序算法。

它的基本思想是：每次遍历数组，将相邻的两个元素进行比较，如果前一个元素大于后一个元素，就交换它们的位置，直到整个数组都是有序的。

在这个过程中，会完成两件事情：

1. 将最大的元素放到数组的末尾;
2. 在冒泡的过程不停地在进行元素的交换，所以实际上也减少了很多逆序对的数量，也就可能在不经意间完成了多个元素的排序。

### 实现

#### 第一版

最简单的一版，就是粗暴遍历，每个元素都依次进行比较，只要后一个元素比前一个元素大，就给二者交换位置。

```c
void bubble_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr, j, j + 1);
      }
    }
  }
}
```

#### 第二版

第一版的问题是，我们明知道每轮循环实际上会把最大值放到最后一个位置，但是内层循环仍然会遍历到头，实际上后面的比较完全是浪费的，因为 if 是一定不成立的。

```c
void bubble_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr, j, j + 1);
      }
    }
  }
}
```

在第一版的基础上，调整了内层循环的终止条件，终止条件减去当前 i 的值，这样就可以利用末尾 i 个元素已经有序这个已知特性，避免了多余的比较。

#### 第三版

如前所述，冒泡的过程中实际上会消除多个逆序对，所以完全有可能在某次冒泡完成后，数组就是有序的，这时候就可以提前结束了。

```c
void bubble_sort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    bool isSorted = true;
    for (int j = 0; j < len - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr, j, j + 1);
        isSorted = false;
      }
    }
    if (isSorted) break;
  }
}
```

加入一个标记位，来标记某次冒泡之后是不是就没有任何交换操作了，如果是就说明当前数组已经有序了，提前结束即可。

#### 第四版

第三版考虑的场景比较极端，即数组经过某次冒泡后变得完全有序，但是还有一种可能性更大的情况是，单次冒泡消除了多个逆序对，导致下次再冒泡的时候，可以直接在有序区间的起始位置终止内层循环，从而省去多余的比较。

```c
  for (int i = 0; i < length - 1;) {
    int lastSwappedIndex = 0;
    for (int j = 0; j < length - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        lastSwappedIndex = j + 1;
      }
    }
    i = length - lastSwappedIndex;
  }
```

每次冒泡完成后，记录最后交换的位置，然后用 length - lastSwappedIndex 得到最后一个非有序元素的下标，并更新为下一次冒泡的起始位置，即 i。

1. 如果正常冒泡，lastSwappedIndex = length - 1 并逐个递减，length - lastSwappedIndex 也就逐个递增，所以对于 i 来说还是 i++ 的逻辑；
2. 但是如果数组部分有序，某次冒泡过程中交换后就不再需要继续了，记录的 lastSwappedIndex 就是最后一个有序元素的下标，那么 i = length - lastSwappedIndex 就是下一次冒泡的起始位置。
3. 如果数组完全有序，那么 lastSwappedIndex = 0，那么 i = length - 0 = length，不满足循环条件直接就结束了。

这个优化版本特别适合部分有序的数组，因为它能够利用数组中已经存在的有序部分，大幅减少比较和交换的次数。

#### 排序过程

假设数组：[5, 2, 3, 1, 4]

第一轮冒泡：

初始：[5, 2, 3, 1, 4], i = 0
j=0: 5>2, 交换：[2, 5, 3, 1, 4], lastSwappedIndex = 1
j=1: 5>3, 交换：[2, 3, 5, 1, 4], lastSwappedIndex = 2
j=2: 5>1, 交换：[2, 3, 1, 5, 4], lastSwappedIndex = 3
j=3: 5>4, 交换：[2, 3, 1, 4, 5], lastSwappedIndex = 4

轮次结束：i = length - lastSwappedIndex = 5 - 4 = 1
意味着：[2, 3, 1, 4 | 5] (竖线后面是已排序区域)

第二轮冒泡：

开始：[2, 3, 1, 4 | 5], i = 1
j=0: 2<3, 不交换
j=1: 3>1, 交换：[2, 1, 3, 4 | 5], lastSwappedIndex = 2
j=2: 3<4, 不交换

轮次结束：i = 5 - 2 = 3
意味着：[2, 1 | 3, 4, 5] (发现3,4已经在正确位置)

第三轮冒泡：

开始：[2, 1 | 3, 4, 5], i = 3
j=0: 2>1, 交换：[1, 2 | 3, 4, 5], lastSwappedIndex = 1

轮次结束：i = 5 - 1 = 4
数组已经完全有序：[1, 2, 3, 4, 5]
