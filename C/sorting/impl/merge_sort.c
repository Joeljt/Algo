
void merge(int* arr, int* temp, int l, int m, int r) {
  int i = l, j = m + 1, k = 0;
  while(i <= m && j <= r) {
    if (arr[i] < arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }
  while (i <= m) temp[k++] = arr[i++];
  while (j <= r) temp[k++] = arr[j++];

  for (int i = 0; i < r - l + 1; i++) {
    arr[i + l] = temp[i];
  }
}

void divide(int* arr, int*temp, int l, int r) {
  if (l >= r) return;
  int m = l + (r - l) / 2; // 避免溢出
  divide(arr, temp, l, m);
  divide(arr, temp, m + 1, r);

  if (arr[m] <= arr[m + 1]) return;

  merge(arr, temp, l, m, r);
}

void mergeSort(int* arr, int size) {
  int* temp = malloc(sizeof(int) * size);
  divide(arr, temp, 0, size - 1);
  free(temp);
}