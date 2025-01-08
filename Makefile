CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined -fstack-protector-all -I.

# 创建 _dist 目录
$(shell mkdir -p _dist)

# 定义所有数据结构
TARGETS = array linkedlist stack queue sorting bst heap map set hashtable trie uf graph mst ssp

# 每个数据结构的编译规则
array: array/*.c
	@$(CC) $(CFLAGS) -DTEST_ARRAY -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

linkedlist: $(wildcard linkedlist/*.c) $(wildcard linkedlist/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_LINKEDLIST -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

stack: $(wildcard stack/*.c) $(wildcard stack/*/*.c) array/*.c linkedlist/*/*.c
	@$(CC) $(CFLAGS) -DTEST_STACK -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

queue: $(wildcard queue/*.c) $(wildcard queue/*/*.c) array/*.c $(wildcard heap/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_QUEUE -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

sorting: $(wildcard sorting/*.c) $(wildcard sorting/*/*.c) $(wildcard heap/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_SORTING -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

bst: $(wildcard bst/*.c) $(wildcard bst/*/*.c) $(wildcard queue/*/*.c) array/*.c
	@$(CC) $(CFLAGS) -DTEST_BST -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

heap: $(wildcard heap/*.c) $(wildcard heap/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_HEAP -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

map: $(wildcard map/*.c) $(wildcard map/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_MAP -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

set: $(wildcard set/*.c) $(wildcard set/*/*.c) $(wildcard map/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_SET -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

trie: $(wildcard trie/*.c)
	@$(CC) $(CFLAGS) -DTEST_TRIE -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

hashtable: $(wildcard hashtable/*.c) $(wildcard hashtable/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_HASHTABLE -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

uf: $(wildcard uf/*.c) $(wildcard uf/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_UF -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

graph: $(wildcard graph/*.c) $(wildcard graph/*/*.c) $(wildcard queue/*/*.c) array/*.c $(wildcard heap/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_GRAPH -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

mst: $(wildcard graph/mst/*.c) $(wildcard graph/mst/*/*.c) $(wildcard graph/*/*.c) $(wildcard uf/*/*.c) $(wildcard queue/*/*.c) $(wildcard heap/*/*.c) array/*.c
	@$(CC) $(CFLAGS) -DTEST_MST -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

ssp: $(wildcard graph/ssp/*.c) $(wildcard graph/ssp/*/*.c) $(wildcard graph/*/*.c) $(wildcard queue/*/*.c) $(wildcard heap/*/*.c) array/*.c
	@$(CC) $(CFLAGS) -DTEST_SSP -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

# 编译所有
all: $(TARGETS)

# 清理
clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS)
