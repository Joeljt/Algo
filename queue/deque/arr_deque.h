#ifndef _ARR_DEQUE_H_
#define _ARR_DEQUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ArrDeque ArrDeque;

ArrDeque *ad_create(int size);
void ad_destroy(ArrDeque* deque);

void ad_push_front(ArrDeque* deque, int value);
void ad_push_back(ArrDeque* deque, int value);

int ad_pop_front(ArrDeque* deque);
int ad_pop_back(ArrDeque* deque);

int ad_peek_front(ArrDeque* deque);
int ad_peek_back(ArrDeque* deque);

void ad_print(ArrDeque* deque);

#endif
