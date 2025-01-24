#include "arr_deque.h"

struct ArrDeque {
    void* data;
    int count;
    int size;
    // 除了数组，还需要两个指针来表示队首和队尾
    int front; // 队首指针，指向队首元素
    int tail; // 队尾指针，指向队尾元素的下一个位置
};

static void resize(ArrDeque *deque, int new_size) {
    void **new_data = malloc(sizeof(void*) * (new_size + 1));
    for (int i = 0; i < deque->count; i++) {
        new_data[i] = ((void**)deque->data)[(deque->front + i) % deque->size];
    }
    free(deque->data);
    deque->data = new_data;
    deque->size = new_size + 1;
    deque->front = 0;
    deque->tail = deque->count;
}

ArrDeque *ad_create(int size) {
    ArrDeque *deque = (ArrDeque *)malloc(sizeof(ArrDeque));
    // 数组大小需要比实际大小大 1，因为需要空出一个位置来区分队空和队满
    deque->data = malloc(sizeof(void*) * (size + 1));
    deque->size = size + 1;
    deque->count = 0;
    deque->front = 0;
    deque->tail = 0;
    return deque;
}

void ad_destroy(ArrDeque *deque) {
    free(deque->data);
    free(deque);
}

// 从队首删除元素
void* ad_pop_front(ArrDeque *deque) {
    void* ret = ((void**)deque->data)[deque->front];
    // 从队首出队元素是简单的，只需要把 front 指针后移一位即可
    deque->front = (deque->front + 1) % deque->size;
    deque->count--;

    // 如果元素数量小于数组容量的四分之一，则进行缩容
    if (deque->count == deque->size / 4 && deque->size / 2 != 0) {
        resize(deque, deque->size / 2);
    }
    return ret;
}

// 在队尾添加元素
void ad_push_back(ArrDeque *deque, void* value) {
    if (deque->count == deque->size - 1) {
        resize(deque, 2 * deque->size);
    }
    
    // 在队尾添加元素，同时维护尾指针
    ((void**)deque->data)[deque->tail] = value;
    // 这里实际上就是 ++ 操作，只不过循环数组里需要通过 % 操作来实现下标的循环
    // tail 指向队尾元素的下一个元素，始终指向一个空位置
    deque->tail = (deque->tail + 1) % deque->size;
    deque->count++;
}

// 在队首添加元素
void ad_push_front(ArrDeque *deque, void* value) {
    if (deque->count == deque->size - 1) {
        resize(deque, 2 * deque->size);
    }

    // 在队首添加元素，同时维护头指针
    // 在队首添加元素，需要将 front 指针前移一位
    // 1. 如果 front > 0，直接 -- 即可
    // 2. 如果 front == 0，则需要将 front 指针指向数组尾部
    // 可以通过简单的判断手动进行矫正：front == 0 ? deque->size - 1 : deque->front - 1
    // 但是这里可以利用循环数组的特性，通过取模操作来实现
    deque->front = (deque->front - 1 + deque->size) % deque->size;
    ((void**)deque->data)[deque->front] = value;
    deque->count++;
}

// 从队尾删除元素
void* ad_pop_back(ArrDeque *deque) {
    void* ret = ((void**)deque->data)[deque->tail - 1];
    // 从队尾删除元素并维护尾指针
    // 这里和队首删除元素不一样，因为队首删除是 front 指针后移，指针角标不可能为负
    // 而队尾删除是 tail 指针前移，指针角标可能为负，所以需要进行矫正处理
    // 这里就和队首插入的逻辑一样：手动矫正或者取模矫正
    deque->tail = (deque->tail - 1 + deque->size) % deque->size;
    deque->count--;

    // 缩容处理
    if (deque->count == deque->size / 4 && deque->size / 2 != 0) {
        resize(deque, deque->size / 2);
    }
    return ret;
}

void* ad_peek_front(ArrDeque *deque) {
    return ((void**)deque->data)[deque->front];
}

void* ad_peek_back(ArrDeque *deque) {
    return ((void**)deque->data)[deque->tail - 1];
}

bool ad_is_empty(ArrDeque *deque) {
    return deque->count == 0;
}

int ad_size(ArrDeque *deque) {
    return deque->count;
}

void ad_print(ArrDeque *deque) {
    printf("ArrDeque: front [");
    for (int i = deque->front; i != deque->tail; i = (i + 1) % deque->size) {
        printf("%d(%d)", ((int*)deque->data)[i], i);
        if ((i + 1) % deque->size != deque->tail) {
            printf(", ");
        }
    }
    printf("] tail\n");
}