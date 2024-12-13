## 数组

数组是一种线性结构，内存地址连续，可以通过下标以 $O(1)$ 的时间复杂度访问元素。

数组效率极高，但是需要提前开辟固定的内存空间，需要自行实现动态扩容的能力来保证数组的可扩展性和易用性，但是往往会带来一定程度的浪费或性能损耗。

动态数组的实现重点关注以下几点即可：增删元素、动态扩容。

### 动态扩容

在新增元素之前或者删除元素之后，需要对数组元素做检查，然后进行相应的 resize 操作。

一般来讲，C 语言有两种处理扩容的方式：`realloc` 和 `malloc` + `memcpy`。

```c
// resize 方法更推荐的实践
// realloc 会直接在原内存块上进行扩展，并在必要时自动处理数据复制和原内存释放的问题
// realloc(NULL, new_size) 等价于 malloc()
// realloc(ptr, 0) 等价于 free(ptr)
static void resize(Array* array, int newCapacity) {
    int* newData = (int*)realloc(array->data, sizeof(int) * newCapacity);
    if(newData != NULL) {
        array->data = newData;
        array->capacity = newCapacity;
    }
}

// 重新申请内容空间，但是利用 memcpy 进行数据复制
static void resize(Array* array, int newCapacity) {
    int *newData = (int*)malloc(sizeof(int) * newCapacity);
    if (newData != NULL) {
        memcpy(newData, array->data, array->size * sizeof(int));
        free(array->data);
        array->data = newData;
        array->capacity = newCapacity; 
    }
}

// 重新申请内存空间并自己处理复制、内存释放等操作
// 性能不好，而且 array->data 的释放容易落下，更推荐 realloc 的做法
// 这里只是记录一下这种方式也可行
static void resize(Array* array, int newCapacity) {
    int *newData = (int*)malloc(sizeof(int) * newCapacity);
    if (newData != NULL) {
        for (int i = 0; i < array->size; i++) {
            newData[i] = array->data[i];
        }
        free(array->data);
        array->data = newData;
        array->capacity = newCapacity; 
    }
}
```

### 增删元素

根据下标在任意位置插入或删除元素，整体复杂度为 $O(n)$，因为需要像插入排序一样对数组元素进行整体的移动操作。

同时，要注意数组长度的判断，从而进行相应的 resize 操作。

```c
void addElement(Array* array, int index, int e) {
    assert(index >= 0 && index <= array->size);
    if (array->size == array->capacity) {
        resize(array, array->capacity * 2);
    }
    for (int i = array->size - 1; i >= index; i--) {
        array->data[i + 1] = array->data[i];
    }
    array->data[index] = e;
    array->size++;  
}

void removeElement(Array* array, int index) {
    assert(index >= 0 && index < array->size);
    int e = array->data[index];
    for (int i = index + 1; i < array->size; i++) {
        array->data[i - 1] = array->data[i];
    }
    array->size--;
    if (array->size == array->capacity / 4 && array->capacity / 2 != 0) {
        resize(array, array->capacity / 2);
    }
    return e;
}
```

注意移除元素后的缩容操作，如果缩容后数组长度小于 1/4，那么就进行缩小为原来容量的 1/2，从而避免复杂度震荡的问题。

同时，还要考虑到 1 / 2 = 0 的问题。
