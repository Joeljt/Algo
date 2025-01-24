package others.Java.src.utils;

import others.Java.src.b_sorting.InsertionSort;
import others.Java.src.b_sorting.SelectionSort;

public class SortHelper {

    private SortHelper() {}
    
    public static <E> void swap(E[] data, int a, int b) {
        if (data != null && a != b) {
            E temp = data[a];
            data[a] = data[b];
            data[b] = temp;
        }
    }

    public static <E extends Comparable<E>> boolean isSorted(E[] data) {
        for (int i = 1; i < data.length; i++) {
            if (data[i - 1].compareTo(data[i]) > 0) {
                return false;
            }
        }
        return true;
    }

    public static <E extends Comparable<E>> void testSort(String sortName, E[] data) {
        long startTime = System.nanoTime();
        switch (sortName) {
            case "SelectionSort": SelectionSort.sort(data); break;
            case "InsertionSort": InsertionSort.sort(data); break;
            case "InsertionSortBySwap": InsertionSort.sortBySwap(data); break;
            default: throw new IllegalArgumentException("Sort " + sortName + " not found");
        }
        long endTime = System.nanoTime();
        if (!isSorted(data)) {
            throw new RuntimeException(sortName + " failed");
        }
        System.out.println(sortName + " : " + (endTime - startTime) / 1000000000.0 + " s");
    }

}
