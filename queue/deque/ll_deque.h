#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LinkedDeque LinkedDeque;

LinkedDeque *ld_create();
void ld_destroy(LinkedDeque *deque);

void ld_push_front(LinkedDeque *deque, int value);
void ld_push_back(LinkedDeque *deque, int value);

int ld_pop_front(LinkedDeque *deque);
int ld_pop_back(LinkedDeque *deque);

int ld_peek_front(LinkedDeque *deque);
int ld_peek_back(LinkedDeque *deque);

void ld_print(LinkedDeque *deque);

#endif
