## 快速排序

快速排序与归并排序类似，都是基于分治思想的排序算法。时间复杂度为 $O(n\log n)$。

与归并排序先拆分后合并，在合并的过程中进行排序的逻辑不同，快速排序是先排序，再拆分，等完成拆分后，整个数组也就排序完成了。

快排的实现逻辑是：

1. 选定一个基准元素 pivot；
2. 将数组中所有小于 pivot 的元素放在 pivot 的左边，大于 pivot 的元素放在 pivot 的右边；
3. 此时 pivot 就处在了它应该在的位置上；
4. 然后以 pivot 为分界线，将所有两侧的子数组进行递归重复上述步骤。

由于快速排序的核心逻辑在于 partition 操作，递归部分没什么新意，所以重点介绍 partition 操作的实现，只在开始简单介绍下快排的实现。

```c
void quickSort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
}
```

### 第一版

按照上述思路，最简单的方式可以考虑引入两个辅助数组，分别存放小于 pivot 和大于等于 pivot 的元素，然后合并这两个数组。

```c
int partition(int* arr, int left, int right) {
    int pivot = arr[left];
    int* leftArr = (int*)malloc(sizeof(int) * (right - left + 1));
    int* rightArr = (int*)malloc(sizeof(int) * (right - left + 1));
    int leftIndex = 0, rightIndex = 0;
    
    // 修改判断条件，将等于 pivot 的元素放到右边
    for (int i = left + 1; i <= right; i++) {  // 从 left + 1 开始，因为 left 是 pivot
        if (arr[i] < pivot) {
            leftArr[leftIndex++] = arr[i];
        } else {  // arr[i] >= pivot
            rightArr[rightIndex++] = arr[i];
        }
    }
    
    // 合并数组时的顺序：左数组 -> pivot -> 右数组
    int k = left;
    for (int i = 0; i < leftIndex; i++) {
        arr[k++] = leftArr[i];
    }
    int pivotPos = k;
    arr[k++] = pivot;
    for (int i = 0; i < rightIndex; i++) {
        arr[k++] = rightArr[i];
    }
    
    free(leftArr);
    free(rightArr);
    return pivotPos;  // 返回 pivot 的实际位置
}
```

这个实现虽然直观，但需要额外的空间复杂度 O(n)，所以不是快速排序的常用实现。通常的快排实现会使用原地分区（in-place partition）来避免额外的内存分配。

### 第二版

下面是单路快排的实现，它通过一个指针将数组分成两部分，左边全部小于等于 pivot，右边全部大于 pivot：

循环不变量是：arr[left + 1, i) <= pivot，arr[i, right] > pivot。

```c
int partition(int* arr, int left, int right) {
    // 选择第一个元素作为 pivot
    int pivot = arr[left];
    // 初始化指针 i，指向 pivot 的下一个元素
    int i = left + 1;
    // 遍历数组，将小于 pivot 的元素放到左侧
    for (int j = left + 1; j <= right; j++) {
        // 如果当前元素小于 pivot，则交换 arr[i] 和 arr[j]
        if (arr[j] < pivot) {
            swap(arr, i, j);
            // 指针 i 向后移动一位
            i++;
        }
    }
    // 将 pivot 放到它应该在的位置
    swap(arr, left, i - 1);
    // 返回 pivot 的实际位置
    return i - 1;
}
```

虽然这个版本的 partition 操作是正确的，但存在一个问题：对于完全有序的数组，该版本的时间复杂度会退化到 O(n^2)。

因为每次遍历都会将数组分为两部分，但是左侧子数组永远为空，右侧子数组永远为 n-1 个元素，最终导致遍历次数为 n-1 次，总的时间复杂度为 O(n^2)。

### 第三版

为了解决这个问题，可以引入随机化，随机选择 pivot 来避免最坏情况的发生。

```c
int partition(int* arr, int left, int right) {
    // 随机选择 pivot
    int pivotIndex = rand() % (right - left + 1) + left;
    swap(arr, left, pivotIndex);
    // 重复之前单路快排的逻辑
    int pivot = arr[left];
    int i = left + 1;
    for (int j = left + 1; j <= right; j++) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, left, i - 1);
    return i - 1;
}
```

这个版本的时间复杂度为 O(n)，但仍然存在问题：对于包含大量重复元素的数组，性能仍然不佳。

拿极端情况举例，如果数组中所有元素都相同，那么每次 partition 操作都会将数组分为两部分，但是左侧子数组永远为空，右侧子数组永远为 n-1 个元素，最终时间复杂度再次退化为 O(n^2)。

### 第四版

为了解决这个问题，可以引入双路快排，将数组分成三部分：小于 pivot、等于 pivot 和大于 pivot。

循环不变量是：arr[left + 1, i) <= pivot，arr[j, right] >= pivot。

```c
int partition(int* arr, int left, int right) {
    int pivot = arr[left];
    // 初始化两个指针，分别指向数组的左右两端
    int i = left + 1, j = right;
    // 当两个指针没有相遇时，继续遍历
    while (i <= j) {
        // 从左到右找到第一个大于等于 pivot 的元素
        while (i <= j && arr[i] < pivot) i++;
        // 从右到左找到第一个小于等于 pivot 的元素
        while (i <= j && arr[j] >= pivot) j--;
        // 如果 i 和 j 没有相遇，则交换 arr[i] 和 arr[j]
        if (i <= j) swap(arr, i, j);
    }
    // 将 pivot 放到它应该在的位置
    swap(arr, left, j);
    return j;
}
```

这个版本通过双路遍历，将等于 pivot 的元素均匀分布在两侧，从而避免了大量重复元素导致的性能退化。

但是如果数组中包含大量重复元素，这个版本仍然会有一些浪费，因为等于 pivot 的元素会被交换到两侧，而实际上这些元素已经是有序的，不需要再进行交换。

### 第五版

为了解决这个问题，可以引入三路快排，将数组分成三部分：小于 pivot、等于 pivot 和大于 pivot。

循环不变量是：arr[left + 1, lt) < pivot，arr[lt, i) = pivot，arr[gt, right] > pivot。

在循环过程中，arr[i, gt) 是待处理的元素，arr[left, lt) 是小于 pivot 的元素，arr[lt, i) 是等于 pivot 的元素，arr[gt, right] 是大于 pivot 的元素。

```c
int partition(int* arr, int left, int right) {
    // 选择第一个元素作为 pivot
    int pivot = arr[left];
    // 初始化三个指针，分别指向数组的左右两端
    int lt = left, i = left + 1, gt = right + 1;
    // 当指针 i 小于 gt 时，继续遍历
    while (i < gt) {
        // 如果当前元素小于 pivot，则交换 arr[i] 和 arr[lt + 1]
        // 这是因为 arr[left + 1, lt) 是小于 pivot 的元素
        // 交换后，arr[left + 1, lt] 仍然是小于 pivot 的元素
        // 并且 arr[lt + 1] 是等于 pivot 的元素
        if (arr[i] < pivot) {
            swap(arr, i, lt + 1);
            // 指针 lt 向后移动一位
            lt++;
            // 指针 i 向后移动一位
            i++;
        }
        // 如果当前元素等于 pivot，则指针 i 向后移动一位
        else if (arr[i] == pivot) {
            i++;
        }
        // 如果当前元素大于 pivot，则交换 arr[i] 和 arr[gt - 1]
        else {
            swap(arr, i, gt - 1);
            gt--;
        }
    }
    // 将 pivot 放到它应该在的位置
    swap(arr, left, lt);
    // 返回 pivot 的实际位置
    return lt;
}
```

这个版本通过三路遍历，将等于 pivot 的元素均匀分布在两侧，从而避免了大量重复元素导致的性能退化。

