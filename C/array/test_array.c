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
    for (int i = 0; i < 10; i++) {
        addLast(array, i);
    }
    printArray(array); 

    // 测试插入元素后动态扩容
    addElement(array, 3, -1);
    printArray(array);  

    // 测试删除元素
    removeLast(array);
    printArray(array);  

    // 测试动态缩容量
    for (int i = 0; i < 8; i++)
    {
        removeFirst(array);
    }
    printArray(array);  

    // 清理
    destroyArray(array);
    return 0;
}