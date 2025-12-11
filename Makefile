# Makefile for Data Structure and Algorithm Project

# 定义目录
DATASOURCE_DIR = datastructure
ALGORITHM_DIR = algorithm
LEETCODE_DIR = leetcode
EXAMPLES_DIR = examples

# 默认目标
.PHONY: all
all: help

# 帮助信息
.PHONY: help
help:
	@echo "可用的命令:"
	@echo ""
	@echo "运行示例程序:"
	@echo "  make run-array        - 运行数组示例程序"
	@echo "  make run-linkedlist   - 运行链表示例程序"
	@echo "  make run-leetcode    - 运行 LeetCode 示例"
	@echo "  make run-all          - 运行所有示例程序"
	@echo ""
	@echo "测试:"
	@echo "  make test             - 运行所有单元测试（不包括 examples）"
	@echo "  make test-array       - 运行数组单元测试"
	@echo "  make test-linkedlist  - 运行链表单元测试"
	@echo "  make test-coverage    - 运行测试并生成覆盖率报告"
	@echo ""
	@echo "其他:"
	@echo "  make fmt              - 格式化所有 Go 代码"
	@echo "  make clean            - 清理测试文件"

# ==================== 运行示例程序 ====================

# 运行数组示例程序
.PHONY: run-array
run-array:
	@echo "=== 运行数组示例程序 ==="
	@cd $(EXAMPLES_DIR)/array && go run main.go

# 运行链表示例程序
.PHONY: run-linkedlist
run-linkedlist:
	@echo "=== 运行链表示例程序 ==="
	@cd $(EXAMPLES_DIR)/linkedlist && go run main.go

# 运行 LeetCode 示例
.PHONY: run-leetcode
run-leetcode:
	@echo "=== 运行 LeetCode 示例 ==="
	@cd $(EXAMPLES_DIR)/leetcode && go run main.go

# 运行所有示例程序
.PHONY: run-all
run-all: run-array run-linkedlist run-leetcode
	@echo "=== 所有示例程序运行完成 ==="

# 快速运行（默认运行链表）
.PHONY: run
run: run-linkedlist

# ==================== 测试 ====================

# 运行所有单元测试（排除 examples 目录）
.PHONY: test
test:
	@echo "=== 运行所有单元测试 ==="
	@go test ./$(DATASOURCE_DIR)/... -v
	@go test ./$(ALGORITHM_DIR)/... -v 2>/dev/null || true
	@go test ./$(LEETCODE_DIR)/... -v 2>/dev/null || true

# 运行数组单元测试
.PHONY: test-array
test-array:
	@echo "=== 运行数组单元测试 ==="
	@go test ./$(DATASOURCE_DIR)/array -v

# 运行链表单元测试
.PHONY: test-linkedlist
test-linkedlist:
	@echo "=== 运行链表单元测试 ==="
	@go test ./$(DATASOURCE_DIR)/linkedlist -v

# 运行测试并显示覆盖率
.PHONY: test-coverage
test-coverage:
	@echo "=== 运行测试并生成覆盖率报告 ==="
	@go test ./$(DATASOURCE_DIR)/... -coverprofile=coverage.out
	@go tool cover -html=coverage.out -o coverage.html
	@echo "覆盖率报告已生成: coverage.html"

# ==================== 其他工具 ====================

# 格式化代码
.PHONY: fmt
fmt:
	@echo "=== 格式化代码 ==="
	@go fmt ./...
	@echo "格式化完成"

# 清理测试文件
.PHONY: clean
clean:
	@echo "=== 清理测试文件 ==="
	@rm -f coverage.out coverage.html
	@echo "清理完成"
