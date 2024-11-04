package src.b_sorting;

import src.utils.SortHelper;

public class InsertionSort {

    private InsertionSort() {
    }

    /**
     * 插入排序
     * 
     * O(n^2)
     * 外层循环确保访问到数组的每个元素，内层循环负责从 i + 1 开始倒序向前查找，找到合适的位置并插入
     * 
     * 核心思路：
     * 1. 将数组在逻辑上划分为 data[0, i) 已排序区间和 data[i, len - 1] 未排序区间；
     * 2. 外层循环从 0 开始向后遍历，依次访问每个元素，确保每个元素都可以被访问到；
     * 3. 外层循环将当前遍历到的元素取出来备用，以免在内层循环中丢失（是否会丢失取决于实现方式）；
     * 4. 内层循环从当前位置 i 开始倒序向前，寻找该元素应该在的位置；
     * 4.1 交换（swap，选择排序的最后一步，在这里需要每次都进行）
     * 在寻找的过程中实时进行元素的交换，过程类似冒泡，将当前元素不停地冒泡到正确的位置；
     * 4.2 移动（数组赋值操作，在动态数组的添加和删除方法中也有应用）
     * 在寻找的比对过程中，只要发现前一个元素不满足条件，就将其向后移动一个位置，给待插入的元素腾出空间；
     * 找到合适的位置，或者遍历到数组头部，把第三步缓存的目标元素直接赋值到对应的位置，完成插入；
     * 
     * 注意点：
     * 1. 提前把当前遍历到的元素缓存下来（也就是 data[i]，即未排序区间的第一个值）
     *      因为向前比对的过程中会不停向后移动元素，给当前元素腾出位置准备插入，如果不提前缓存就会导致：
     *        a) 无法有效对比，因为没有基准值，data 的元素因为赋值的原因在不停地变化
     *        b) 无法插入，首先根本找不到正确的位置，就算找到了也没有当前元素，因为已经被覆盖了
     * 2. 内存循环的比较过程是从 i - 1 开始倒序向前，每个值都和 i 的值做对比，而不是 j，因为 j 一直在变化
     * 3. 最后跳出循环，把 target 赋值给 data[j] 时，有两种情况：
     *     a) 找到了目标位置，即 j - 1 不再比 target 更小，直接赋值给 data[j] 即可完成插入；
     *     b) 遍历结束，整个已排序区间都整体向后移动了一位，也没有找到比 target 更小的值，也就是说 target 本身就是最小值（此时 j = 0）；
     * 
     */
    public static <E extends Comparable<E>> void sort(E[] data) {
        for (int i = 1; i < data.length; i++) {
            E target = data[i];
            int j = i;

            // while 循环的写法，不用 else break，更直观一些
            // 注意 j >= 1 的条件，因为每次都需要比较当前位置的前一个元素
            while (j - 1 >= 0 && data[j - 1].compareTo(target) > 0) {
                data[j] = data[j - 1];
                j--;
            }

            // for 循环的写法，要注意 break 的位置，否则找到位置后不退出循环，后面的遍历操作都是多余的
            // for (; j - 1 >= 0; j--) {
            //     if (data[j - 1].compareTo(target) > 0) {
            //         data[j] = data[j - 1];
            //     } else break;
            // }
            data[j] = target;
        }
    }

    // 基于交换实现的插入排序，实际上是插入排序+冒泡排序的变体
    // 由于涉及到的操作比较多（数组寻址、三次赋值操作、引入额外的变量等），实际上的运行效率要比选择排序或者插入排序低
    public static <E extends Comparable<E>> void sortBySwap(E[] data) {
        for (int i = 1; i < data.length; i++) {
            for (int j = i; j - 1 >= 0; j--) {
                if (data[j - 1].compareTo(data[j]) > 0) {
                    SortHelper.swap(data, j, j - 1);
                }
            }
        }
    }

    public static <E extends Comparable<E>> void wrongSort(E[] data) {
        for (int i = 1; i < data.length; i++) {
            // 
            E target = data[i];
            int j;
            for (j = i; j - 1 >= 0; j--) {
                // 错误点：
                // 与选择排序需要在遍历过程中不断更新最小值的 minIndex，从而找到真正的最小值不同，
                // 插入排序在向前倒序遍历的过程中，就是要为当前选定的元素寻找正确位置，所以当前元素是不变量
                // 也就是说，在倒序向前查找的时候，始终是当前值在和已排序区间的值一个个做对比（data[j - 1] VS target），而不是 data[j] 或者 data[i]
                // 1. 不能是 data[i] 是因为 data[i] 的值也会变化，一旦进入 if 条件，原本的 data[i] 就会被 data[i - 1] 覆盖掉；
                // 2. 不能是 data[j] 是因为在移动元素的过程中 data[j] 的值会不断变化，无法保持正确的比较基准；
                if (data[j - 1].compareTo(data[j]) > 0) {
                    data[j] = data[j - 1];
                } else
                    break;
            }
            data[j] = target;
        }
    }

}
