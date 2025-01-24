## 选择排序

### Java 实现

```java
public static void sort(int[] data) {
    for (int i = 0; i < data.length; i++) {
        int minIndex = i;
        for (int j = i + 1; j < data.length; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        swap(data, i, minIndex);
    }
}
```

### 思路

- 外层循环遍历数组，依次访问每个元素
- 内层循环从当前元素的下一个元素开始，向后遍历，找到比当前元素更小的元素，并更新最小元素的下标
- 内层循环结束后，将当前元素和最小元素交换位置

### 特点

- 平均时间复杂度是 O(n^2)，最坏时间复杂度是 O(n^2)
- 原地排序算法，不需要额外的内存空间
- 不是稳定排序算法，相同元素的相对位置在排序前后可能会发生变化
- 不是自适应排序，无论输入数据是否有序，都需要进行完整的两层循环


## 插入排序

### Java 实现

```java
public static void sort(int[] data) {
    for (int i = 1; i < data.length; i++) {
        int current = data[i];
        int j = i;
        while (j - 1 >= 0 && data[j - 1] > current) {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = current;
    }
}
```

### 思路

- 外层循环遍历数组，依次访问每个元素
- 内层循环从当前元素的下一个元素开始，向前遍历，寻找当前元素的正确位置，过程中不断将元素向后移动，给当前元素腾出空间
- 找到正确位置后，将当前元素插入到对应的位置

### 特点

- 平均时间复杂度是 O(n^2)，最坏时间复杂度是 O(n^2)
- 自适应排序算法，对于近乎有序的数组可以达到 O(n) 的时间复杂度
- 原地排序算法，不需要额外的内存空间
- 稳定排序算法，相同元素的相对位置在排序前后不会发生变化
- 在数据量小的时候表现优异，常作为高阶排序算法的优化手段



