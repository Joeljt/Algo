CC = gcc
CFLAGS = -Wall -g

# 创建 _dist 目录
$(shell mkdir -p _dist)

# 定义所有数据结构
TARGETS = array linkedlist stack sorting

# 每个数据结构的编译规则
array: array/**/*.c
	@$(CC) $(CFLAGS) -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

linkedlist: linkedlist/**/*.c
	@$(CC) $(CFLAGS) -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

sorting: $(wildcard sorting/*.c) $(wildcard sorting/*/*.c)
	@$(CC) $(CFLAGS) -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"

# 编译所有
all: $(TARGETS)

# 清理
clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS)
