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
	
# 获取所有 leetcode java 文件的基础名称（不含扩展名）
LC_SOURCES = $(wildcard leetcode/*/Solution.java)
LC_TARGETS = $(patsubst leetcode/%/Solution.java,%,$(LC_SOURCES))

# 为每个 leetcode 文件创建编译规则
define make-lc-target
$(1): $(wildcard leetcode/$(1)/*.java)
	@mkdir -p _dist/leetcode
	@javac -d _dist/leetcode $$^
	@java -ea -cp _dist/leetcode $(1).Test
endef

$(foreach target,$(LC_TARGETS),$(eval $(call make-lc-target,$(target))))

# leetcode 总目标，编译运行所有文件
lc: $(LC_TARGETS)

clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS)
