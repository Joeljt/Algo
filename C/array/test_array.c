#include <stdio.h>
#include "array.h"

int main() {
    // 创建数组
    Array* array = createArray(10);
    if (array == NULL) {
        printf("Array creation failed\n");
        return 1;
    }

    // 测试添加元素
    addLast(array, 1);
    addLast(array, 2);
    addLast(array, 3);
    printArray(array);  // 应该输出: [1, 2, 3]

    // 测试插入元素
    addElement(array, 1, 4);
    printArray(array);  // 应该输出: [1, 4, 2, 3]

    // 测试删除元素
    removeElement(array, 2);
    printArray(array);  // 应该输出: [1, 4, 3]

    // 测试首尾操作
    addFirst(array, 5);
    removeLast(array);
    printArray(array);  // 应该输出: [5, 1, 4]

    // 清理
    destroyArray(array);
    return 0;
}