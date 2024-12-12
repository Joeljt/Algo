CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined -fstack-protector-all -I.

# 创建 _dist 目录
$(shell mkdir -p _dist)

# 定义所有数据结构
TARGETS = array linkedlist stack queue sorting bst heap

# 每个数据结构的编译规则
array: array/*.c
	@$(CC) $(CFLAGS) -DTEST_ARRAY -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

linkedlist: linkedlist/**/*.c
	@$(CC) $(CFLAGS) -DTEST_LINKEDLIST -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

stack: stack/*.c array/*.c
	@$(CC) $(CFLAGS) -DTEST_STACK -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

queue: queue/*.c array/*.c
	@$(CC) $(CFLAGS) -DTEST_QUEUE -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

sorting: $(wildcard sorting/*.c) $(wildcard sorting/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_SORTING -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

bst: bst/*.c
	@$(CC) $(CFLAGS) -DTEST_BST -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

heap: heap/*.c
	@$(CC) $(CFLAGS) -DTEST_HEAP -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

# 编译所有
all: $(TARGETS)

# 清理
clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS)
