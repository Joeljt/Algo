void selectionSortImpl(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    int minIndex = i;
    for (int j = i; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    swap(&arr[i], &arr[minIndex]);
  }
}