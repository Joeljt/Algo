# Makefile for Data Structure and Algorithm Project

# 定义目录
DATASOURCE_DIR = datastructure
ALGORITHM_DIR = algorithm
LEETCODE_DIR = leetcode
EXAMPLES_DIR = examples

# 默认目标
.PHONY: all
all: help

# Help information
.PHONY: help
help:
	@echo "Available commands:"
	@echo ""
	@echo "Run example programs:"
	@echo "  make run              - Run all examples"
	@echo "  make run-array        - Run array example"
	@echo "  make run-list         - Run list example"
	@echo "  make run-stack        - Run stack example"
	@echo ""
	@echo "Testing:"
	@echo "  make test             - Run all unit tests (excluding examples)"
	@echo "  make test-array       - Run array unit tests"
	@echo "  make test-list        - Run list unit tests"
	@echo "  make test-leetcode    - Run LeetCode tests"
	@echo "  make test-coverage    - Run tests and generate coverage report"
	@echo ""
	@echo "Other:"
	@echo "  make fmt              - Format all Go code"
	@echo "  make clean            - Clean test files"

# ==================== 运行示例程序 ====================

# Run array example program
.PHONY: run-array
run-array:
	@echo "=== Running array example ==="
	@cd $(EXAMPLES_DIR)/array && go run main.go

# Run list example program
.PHONY: run-list
run-list:
	@echo "=== Running list example ==="
	@cd $(EXAMPLES_DIR)/list && go run main.go

# Run stack example program
.PHONY: run-stack
run-stack:
	@echo "=== Running stack example ==="
	@cd $(EXAMPLES_DIR)/stack && go run main.go

# Run all example programs
.PHONY: run
run: run-array run-list run-stack
	@echo "=== All example programs completed ==="

# ==================== 测试 ====================

# Run all unit tests (excluding examples directory)
.PHONY: test
test:
	@echo "=== Running all unit tests ==="
	@go test ./$(DATASOURCE_DIR)/... 
	@go test ./$(ALGORITHM_DIR)/... 2>/dev/null || true
	@go test ./$(LEETCODE_DIR)/... 2>/dev/null || true

# Run array unit tests
.PHONY: test-array
test-array:
	@echo "=== Running array unit tests ==="
	@go test ./$(DATASOURCE_DIR)/array

# Run list unit tests
.PHONY: test-list
test-list:
	@echo "=== Running list unit tests ==="
	@go test ./$(DATASOURCE_DIR)/list

# Run stack unit tests
.PHONY: test-stack
test-stack:
	@echo "=== Running stack unit tests ==="
	@go test ./$(DATASOURCE_DIR)/stack

# Run LeetCode tests
.PHONY: test-leetcode
test-leetcode:
	@echo "=== Running LeetCode tests ==="
	@go test ./$(LEETCODE_DIR)/... 

# Run tests and show coverage
.PHONY: test-coverage
test-coverage:
	@echo "=== Running tests and generating coverage report ==="
	@go test ./$(DATASOURCE_DIR)/... -coverprofile=coverage.out
	@go tool cover -html=coverage.out -o coverage.html
	@echo "Coverage report generated: coverage.html"

# ==================== Other Tools ====================

# Format code
.PHONY: fmt
fmt:
	@echo "=== Formatting code ==="
	@go fmt ./...
	@echo "Formatting completed"

# Clean test files
.PHONY: clean
clean:
	@echo "=== Cleaning test files ==="
	@rm -f coverage.out coverage.html
	@echo "Cleanup completed"
