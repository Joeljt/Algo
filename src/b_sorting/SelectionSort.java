package src.b_sorting;

import src.utils.SortHelper;

public class SelectionSort {

    private SelectionSort() {}

    /**
     * 选择排序
     * 
     * O(n^2)
     * 外层循环保证每个元素都能访问到，内层循环负责找到最值并与当前选中元素交换从而实现排序。
     * 
     * 核心思路：
     * 1. 在逻辑上将整个数组划分为 已排序 {data[0, i)} 和 未排序 {data[i, len)} 两部分；
     * 2. 外层循环从 0 开始依次向后遍历，内层循环从外层循环的下一位（i + 1）开始先后遍历； 
     * 3. 默认当前位置的元素的排序正确，如果后面发现有比当前元素更合适的值，则记录对应的下标；
     *    3.1 注意这里不能找到一个满足条件的就退出，因为后面可能还有更小或者更大的值，需要遍历到数组末尾
     * 4. 如果下标有变化，则对二者进行交换，从而实现排序；
     * 
     * 注意点：
     * 1. 内层循环的判断条件应该是 j 和 minIndex 的比较，而不是 j 和 i 的比较； 
     * 2. 内层循环 j 的起始值是 i 或者 i + 1 都是正确的，不影响排序结果；
     *    2.1 j = i 时，对于 i = 0 和 i = len - 1 这两个元素会进行两次多余的比较；
     *    2.2 当 i = len - 1 时，minIndex 默认就指向最后一个元素，即使无法进入内存循环也是没有影响的 
     */
    public static <E extends Comparable<E>> void sort(E[] data) {
        for (int i = 0; i < data.length; i++) {
            int minIndex = i;
            for (int j = i + 1; j < data.length; j++) {
                if (data[j].compareTo(data[minIndex]) < 0) {
                    minIndex = j;
                }
            }
            SortHelper.swap(data, i, minIndex);
        }
    }
    
    public static <E extends Comparable<E>> void wrongSort(E[] data) {
        for (int i = 0; i < data.length; i++) {
            int minIndex = i;
            for (int j = i + 1; j < data.length; j++) {
                // 错误点：
                // 内层循环的判断条件应该是 j 和 minIndex 的比较，而不是 j 和 i 的比较；
                // 因为选择排序的核心在于寻找未排序部分里的最小值
                // 而 minIndex 的值会在内层循环中被更新为未排序部分的最小值的下标
                // 就相当于只要当前值比 data[i] 小就更新 minIndex
                // 比如： 4, 1, 2, 3
                // i = 0, minIndex = 0
                // j = 1, 1 < 4, minIndex = 1
                // j = 2, 2 < 4, minIndex = 2
                // 这里的最小值应该为 1，但是因为和 i 比较，导致 minIndex 继续被更新为 2
                if (data[j].compareTo(data[i]) < 0) {
                    minIndex = j;
                }
            }
            SortHelper.swap(data, i, minIndex);
        }
    }

    public static <E extends Comparable<E>> void wrongSort2(E[] data) {
        for (int i = 0; i < data.length; i++) {
            int minIndex = i;
            // 错误点：
            // 内层循环的终止条件应该是 data.length，而不是 data.length - 1
            // 这样会导致每次内层循环都漏掉最后一个元素，最终导致排序失败
            for (int j = i + 1; j < data.length - 1; j++) {
                if (data[j].compareTo(data[minIndex]) < 0) {
                    minIndex = j;
                }
            }
            SortHelper.swap(data, i, minIndex);
        }
    }
}
