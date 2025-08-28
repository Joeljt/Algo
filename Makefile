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
	
# 获取所有 leetcode go 测试文件（test.go）对应的目标名
LC_SOURCES = $(wildcard leetcode/*/test.go)
LC_TARGETS = $(patsubst leetcode/%/test.go,%,$(LC_SOURCES))

# 为每个 leetcode 目录创建运行规则（使用 go run 执行 test.go 和 solution.go）
define make-lc-target
$(1): leetcode/$(1)/test.go leetcode/$(1)/solution.go
	@cd leetcode/$(1) && go run test.go solution.go
endef

$(foreach target,$(LC_TARGETS),$(eval $(call make-lc-target,$(target))))

# leetcode 总目标，运行所有 go 题目
lc: $(LC_TARGETS)

# 创建 leetcode 模板
new:
	@mkdir -p leetcode/$(q)
	@sed "s/{{name}}/$(q)/g" leetcode/templates/Solution.template > leetcode/$(q)/Solution.java
	@sed "s/{{name}}/$(q)/g" leetcode/templates/Test.template > leetcode/$(q)/Test.java
	@sed "s/{{name}}/$(q)/g" leetcode/templates/README.template > leetcode/$(q)/README.md

clean:
	@rm -rf _dist

.PHONY: all clean $(TARGETS) lc
