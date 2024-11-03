## 线性查找

线性查找就是遍历数组，逐个元素进行比较，直到找到目标元素或遍历完整个数组。

最好的情况下，第一个元素就是目标元素，这时线性查找的时间复杂度为 O(1)。

最坏的情况下，最后一个元素才是目标元素，这时线性查找的时间复杂度为 O(n)。

平均情况下，线性查找的时间复杂度为 O(n/2)，即 O(n)。

```java
public static <E> int search(E[] arr, E target) {
    for (int i = 0; i < arr.length; i++) {
        if (arr[i].equals(target)) {
            return i;
        }
    }
    return -1;
}
``` 

