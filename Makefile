include datastruct/Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined -fstack-protector-all -I.

# 创建 _dist 目录
$(shell mkdir -p _dist)

# 定义所有数据结构
TARGETS = sorting 

sorting: $(wildcard sorting/*.c) $(wildcard sorting/*/*.c) $(wildcard datastruct/heap/*/*.c)
	@$(CC) $(CFLAGS) -DTEST_SORTING -o _dist/test_$@ $^
	@./_dist/test_$@
	@echo "\n"
	
clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS)
