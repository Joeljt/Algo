package src.a_linearsearch;

import src.utils.ArrayGenerator;

public class LinearSearch {
    
    public static <E> int search(E[] arr, E target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(target)) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {

        int[] dataSize = {100000, 1000000};

        for (int n : dataSize) {
            Integer[] arr = ArrayGenerator.generateOrderedArray(n);

            long startTime = System.nanoTime();
            for (int i = 0; i < 1000; i++) {
                LinearSearch.search(arr, n);
            }
            long endTime = System.nanoTime();

            System.out.println("n = " + n + ", 100 runs: " + (endTime - startTime) / 1000000000.0 + " s");
        }   
    }
}
