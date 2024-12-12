## 归并排序

归并排序是一种基于分治法的 $O(n\log n)$ 时间复杂度的排序算法，它是一种稳定的排序算法，适用于大量数据的排序。

### 思路

归并排序的基本思想是将数组拆分为两个子数组，然后递归向下对子数组进行归并排序，直到子数组只剩一个元素，只有一个元素的子数组是有序的。然后在将子数组合并成一个有序的数组的过程中完成整个数组的排序。

由于每次都是将数组拆分为两个子数组，所以整个递归树的深度是 $log_2 n$；每层递归在合并子数组的过程中都会遍历子数组，遍历次数从底向上递增，最后一层递归只需要遍历一个元素，最顶部递归需要遍历 $n$ 次。

因此整个归并排序的时间复杂度为 $O(n \log n)$。

### 实现（divide and conquer）

```c
void merge_sort(int *arr, int n) {
  merge_sort(arr, 0, n - 1);
}

void merge_sort(int *arr, int l, int r) {
  // 递归终止条件：如果左右指针重合，说明子数组只剩一个元素
  if (l >= r) return;
  // 找到中间位置，拆分子数组，l + (r - l) / 2 的写法是为了避免整数溢出
  int mid = l + (r - l) / 2;

  // 递归处理左右两个子数组
  merge_sort(arr, l, mid);
  merge_sort(arr, mid + 1, r);

  // 合并子数组
  // 执行到这里的时候，l 和 r 不可能是相等的，一定存在两个子数组可以合并
  merge(arr, l, mid, r);
}

void merge(int *arr, int l, int mid, int r) {
  // 需要使用一个临时数组来存储合并后的结果，大小就是当前这一轮的左右子数组的和
  int temp[r - l + 1];
  // 三个指针，一个是左子数组的指针，一个是右子数组的指针，一个是临时数组的指针
  int i = l, j = mid + 1, k = 0;
  // 依次比较左右子数组的元素，将较小的元素放入临时数组，并维护对应的指针
  while (i <= mid && j <= r) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  // 左右子数组容量不一定是相等的，可能只有一个子数组剩余，需要将剩余的元素全部放入临时数组
  while (i <= mid) arr[k++] = arr[i++];
  while (j <= r) arr[k++] = arr[j++];

  // 将临时数组的元素复制回原数组，但是要注意这里有 l 个元素的偏移
  // 因为当前是在合并 [l, r] 这个区间的子数组，所以对应到原数组来说，这个区间的起始位置是 l
  for (int i = 0; i < r - l + 1; i++) {
    arr[i + l] = temp[i];
  }
}
```

递归版本的归并排序比较好理解，核心就是分治后合并，处理好左右子数组，理解 merge 函数的逻辑即可。

但是这个版本有几个问题可以优化：

1. 数组数量少于 15 时，使用插入排序;
2. arr[mid] < arr[mid + 1] 时说明整个数据已经有序，可以直接跳过 merge 过程;
3. 单独声明一个 temp 数组并传入 merge 函数，优化内存空间，避免频繁申请释放内存。

### 实现（iterative）

```c
void merge_sort(int *arr, int n) {
  for (int size = 1; size <= n - 1; size = size * 2) {
    for (int left = 0; left + size <= n - 1; left += size * 2) {
      int mid = left + size - 1;
      int right = MIN(left + size * 2 - 1, n - 1);
      merge(arr, left, mid, right);
    }
  }
}
```


