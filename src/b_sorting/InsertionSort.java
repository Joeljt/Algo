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

    public static <E extends Comparable<E>> void sortBySwap(E[] data) {
        for (int i = 1; i < data.length; i++) {
            for (int j = i; j - 1 >= 0; j--) {
                if (data[j - 1].compareTo(data[j]) > 0) {
                    SortHelper.swap(data, j, j - 1);
                } else {
                    break;
                }
            }
        }
    }

    public static <E extends Comparable<E>> void wrongSort2(E[] data) {
        for (int i = 1; i < data.length; i++) {
            E target = data[i];
            int j;
            for (j = i; j - 1 >= 0; j--) {
                if (data[j - 1].compareTo(data[j]) > 0) {
                    data[j] = data[j - 1];
                } else
                    break;
            }
            data[j] = target;
        }
    }

    public static <E extends Comparable<E>> void wrongSort(E[] data) {
        for (int i = 1; i < data.length; i++) {
            E target = data[i];
            for (int j = i; j - 1 >= 0; j--) {
                while (data[j - 1].compareTo(data[j]) > 0) {
                    data[j] = data[j - 1];
                    j--;
                }
                data[j] = target;
            }
        }
    }

}
