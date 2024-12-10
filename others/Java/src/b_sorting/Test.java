package others.Java.src.b_sorting;


import java.util.Arrays;

import others.Java.src.utils.ArrayGenerator;
import others.Java.src.utils.SortHelper;

public class Test {

  public static void main(String[] args) {
  
    int[] dataSize = {10000, 100000}; 
    for (int n : dataSize) {
      Integer[] data = ArrayGenerator.generateRandomArray(n);
      Integer[] copiedData = Arrays.copyOf(data, data.length);
      Integer[] copiedData2 = Arrays.copyOf(data, data.length);

      SortHelper.testSort("SelectionSort", data);
      SortHelper.testSort("InsertionSort", copiedData);
      SortHelper.testSort("InsertionSortBySwap", copiedData2);
    }
  
  }

}
