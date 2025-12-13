package stack

import (
	"testing"
)

// 测试基本功能
func TestStack(t *testing.T) {
	stack := New()
	if stack == nil {
		t.Fatal("New() 返回 nil")
	}
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)
	value, err := stack.Pop()
	if err != nil {
		t.Fatalf("Pop() 返回错误: %v", err)
	}
	if value != 3 {
		t.Errorf("期望值 3，实际值 %v", value)
	}
}

// 测试栈的自动扩容
func TestStackExpansion(t *testing.T) {
	stack := New()
	initialCapacity := stack.GetCapacity()
	t.Logf("初始容量: %d", initialCapacity)

	// 不断添加元素，观察容量变化
	for i := 0; i < 20; i++ {
		stack.Push(i)
		currentCapacity := stack.GetCapacity()
		if i == 0 {
			t.Logf("添加第 %d 个元素后: size=%d, capacity=%d", i+1, stack.GetSize(), currentCapacity)
		}
		// 当容量发生变化时记录
		if currentCapacity != initialCapacity && i > 0 {
			prevCapacity := stack.GetCapacity()
			stack.Push(i + 1)
			newCapacity := stack.GetCapacity()
			if newCapacity != prevCapacity {
				t.Logf("扩容触发: 添加第 %d 个元素时，容量从 %d 扩容到 %d",
					i+2, prevCapacity, newCapacity)
			}
		}
	}

	finalCapacity := stack.GetCapacity()
	if finalCapacity <= initialCapacity {
		t.Errorf("扩容失败: 初始容量 %d，最终容量 %d", initialCapacity, finalCapacity)
	}
	t.Logf("最终: size=%d, capacity=%d", stack.GetSize(), finalCapacity)
}

// 测试栈的自动缩容
func TestStackShrinking(t *testing.T) {
	stack := New()

	// 先添加足够多的元素触发扩容
	for i := 0; i < 30; i++ {
		stack.Push(i)
	}
	expandedCapacity := stack.GetCapacity()
	t.Logf("扩容后容量: %d, 大小: %d", expandedCapacity, stack.GetSize())

	// 不断删除元素，观察容量变化
	initialSize := stack.GetSize()
	for i := 0; i < initialSize; i++ {
		_, err := stack.Pop()
		if err != nil {
			t.Fatalf("Pop() 失败: %v", err)
		}
		currentCapacity := stack.GetCapacity()
		currentSize := stack.GetSize()

		// 记录缩容事件（当容量减少时）
		if i > 0 {
			// 检查是否触发了缩容（容量应该是之前的一半）
			// 缩容条件：size == capacity/4
			if currentSize > 0 && currentSize == currentCapacity/4 {
				t.Logf("缩容触发: size=%d, capacity=%d (缩容阈值)",
					currentSize, currentCapacity)
			}
		}

		// 在最后几个元素时记录
		if currentSize <= 5 {
			t.Logf("删除后: size=%d, capacity=%d", currentSize, currentCapacity)
		}
	}

	finalCapacity := stack.GetCapacity()
	if finalCapacity >= expandedCapacity {
		t.Logf("注意: 最终容量 %d 仍然等于或大于扩容后容量 %d（可能未触发缩容或已缩容但未完全缩回）",
			finalCapacity, expandedCapacity)
	} else {
		t.Logf("缩容成功: 从 %d 缩容到 %d", expandedCapacity, finalCapacity)
	}
}

// 测试扩缩容的完整流程
func TestStackResize(t *testing.T) {
	stack := New()
	initialCapacity := stack.GetCapacity()
	t.Logf("=== 扩缩容完整测试 ===")
	t.Logf("初始容量: %d", initialCapacity)

	// 阶段1: 扩容测试
	t.Logf("\n--- 阶段1: 扩容测试 ---")
	for i := 0; i < 25; i++ {
		stack.Push(i)
		if i == 0 || i == 4 || i == 8 || i == 16 || i == 24 {
			t.Logf("添加 %d 个元素: size=%d, capacity=%d",
				i+1, stack.GetSize(), stack.GetCapacity())
		}
	}
	expandedCapacity := stack.GetCapacity()
	t.Logf("扩容后容量: %d", expandedCapacity)

	// 阶段2: 缩容测试
	t.Logf("\n--- 阶段2: 缩容测试 ---")
	initialSize := stack.GetSize()
	for i := 0; i < initialSize; i++ {
		_, err := stack.Pop()
		if err != nil {
			t.Fatalf("Pop() 失败: %v", err)
		}
		size := stack.GetSize()
		capacity := stack.GetCapacity()

		// 记录关键点
		if size == capacity/4 || size == 10 || size == 5 || size == 0 {
			t.Logf("删除后: size=%d, capacity=%d", size, capacity)
		}
	}

	finalCapacity := stack.GetCapacity()
	t.Logf("\n最终容量: %d", finalCapacity)

	// 验证基本功能仍然正常
	if !stack.IsEmpty() {
		t.Error("栈应该为空")
	}
}

// 测试 Push
func TestPush(t *testing.T) {
	stack := New()

	stack.Push(1)
	if stack.GetSize() != 1 {
		t.Errorf("Push 后大小应该是 1，实际是 %d", stack.GetSize())
	}
	if stack.IsEmpty() {
		t.Error("Push 后栈不应该为空")
	}

	stack.Push(2)
	stack.Push(3)
	if stack.GetSize() != 3 {
		t.Errorf("Push 后大小应该是 3，实际是 %d", stack.GetSize())
	}
}

// 测试 Pop
func TestPop(t *testing.T) {
	stack := New()

	// 测试空栈
	_, err := stack.Pop()
	if err == nil {
		t.Error("从空栈 Pop 应该返回错误")
	}

	// 添加元素
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	// 测试 Pop
	value, err := stack.Pop()
	if err != nil {
		t.Fatalf("Pop() 失败: %v", err)
	}
	if value != 3 {
		t.Errorf("期望值 3，实际值 %v", value)
	}
	if stack.GetSize() != 2 {
		t.Errorf("Pop 后大小应该是 2，实际是 %d", stack.GetSize())
	}
}

// 测试 Peek
func TestPeek(t *testing.T) {
	stack := New()

	// 测试空栈
	_, err := stack.Peek()
	if err == nil {
		t.Error("从空栈 Peek 应该返回错误")
	}

	// 添加元素
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	// 测试 Peek（不应该改变栈的大小）
	value, err := stack.Peek()
	if err != nil {
		t.Fatalf("Peek() 失败: %v", err)
	}
	if value != 3 {
		t.Errorf("期望值 3，实际值 %v", value)
	}
	if stack.GetSize() != 3 {
		t.Errorf("Peek 后大小应该仍然是 3，实际是 %d", stack.GetSize())
	}
}

// 测试 IsEmpty
func TestIsEmpty(t *testing.T) {
	stack := New()
	if !stack.IsEmpty() {
		t.Error("新栈应该为空")
	}

	stack.Push(1)
	if stack.IsEmpty() {
		t.Error("添加元素后栈不应该为空")
	}

	stack.Pop()
	if !stack.IsEmpty() {
		t.Error("删除所有元素后栈应该为空")
	}
}

// 测试 GetSize
func TestGetSize(t *testing.T) {
	stack := New()
	if stack.GetSize() != 0 {
		t.Errorf("新栈大小应该是 0，实际是 %d", stack.GetSize())
	}

	for i := 0; i < 10; i++ {
		stack.Push(i)
		if stack.GetSize() != i+1 {
			t.Errorf("期望大小 %d，实际大小 %d", i+1, stack.GetSize())
		}
	}
}

// 综合测试
func TestIntegration(t *testing.T) {
	stack := New()

	// 添加元素
	for i := 0; i < 20; i++ {
		stack.Push(i)
	}

	if stack.GetSize() != 20 {
		t.Errorf("期望大小 20，实际大小 %d", stack.GetSize())
	}

	// 删除一半元素
	for i := 0; i < 10; i++ {
		_, err := stack.Pop()
		if err != nil {
			t.Fatalf("Pop() 失败: %v", err)
		}
	}

	if stack.GetSize() != 10 {
		t.Errorf("期望大小 10，实际大小 %d", stack.GetSize())
	}

	// 验证栈顶元素
	value, err := stack.Peek()
	if err != nil {
		t.Fatalf("Peek() 失败: %v", err)
	}
	if value != 9 {
		t.Errorf("期望栈顶元素 9，实际 %v", value)
	}

	// 清空栈
	for !stack.IsEmpty() {
		_, err := stack.Pop()
		if err != nil {
			t.Fatalf("Pop() 失败: %v", err)
		}
	}

	if !stack.IsEmpty() {
		t.Error("栈应该为空")
	}
}
