package queue

import (
	"testing"
)

// 测试基本功能
func TestQueue(t *testing.T) {
	queue := New()
	if queue == nil {
		t.Fatal("New() 返回 nil")
	}
	if !queue.IsEmpty() {
		t.Error("新队列应该为空")
	}

	// 测试入队
	err := queue.Enqueue(1)
	if err != nil {
		t.Fatalf("Enqueue() 返回错误: %v", err)
	}
	err = queue.Enqueue(2)
	if err != nil {
		t.Fatalf("Enqueue() 返回错误: %v", err)
	}
	err = queue.Enqueue(3)
	if err != nil {
		t.Fatalf("Enqueue() 返回错误: %v", err)
	}

	if queue.GetSize() != 3 {
		t.Errorf("期望大小 3，实际大小 %d", queue.GetSize())
	}

	// 测试出队（FIFO）
	value, err := queue.Dequeue()
	if err != nil {
		t.Fatalf("Dequeue() 返回错误: %v", err)
	}
	if value != 1 {
		t.Errorf("期望值 1（FIFO），实际值 %v", value)
	}

	value, err = queue.Dequeue()
	if err != nil {
		t.Fatalf("Dequeue() 返回错误: %v", err)
	}
	if value != 2 {
		t.Errorf("期望值 2，实际值 %v", value)
	}
}

// 测试队列为空的情况
func TestEmptyQueue(t *testing.T) {
	queue := New()

	// 测试从空队列出队
	_, err := queue.Dequeue()
	if err == nil {
		t.Error("从空队列 Dequeue 应该返回错误")
	}

	// 测试从空队列 Peek
	_, err = queue.Peek()
	if err == nil {
		t.Error("从空队列 Peek 应该返回错误")
	}

	if !queue.IsEmpty() {
		t.Error("空队列 IsEmpty() 应该返回 true")
	}
}

// 测试队列已满的情况（更新为支持扩容）
func TestFullQueue(t *testing.T) {
	queue := New()
	capacity := queue.GetCapacity()
	t.Logf("队列容量: %d", capacity)

	// 填满队列
	for i := 0; i < capacity; i++ {
		err := queue.Enqueue(i)
		if err != nil {
			t.Fatalf("Enqueue() 失败: %v", err)
		}
	}

	if !queue.IsFull() {
		t.Error("填满后队列应该已满")
	}

	if queue.GetSize() != capacity {
		t.Errorf("期望大小 %d，实际大小 %d", capacity, queue.GetSize())
	}

	// 测试在满队列中入队（现在应该自动扩容，不应该返回错误）
	err := queue.Enqueue(999)
	if err != nil {
		t.Errorf("在满队列中 Enqueue 应该自动扩容，不应该返回错误: %v", err)
	}

	// 验证扩容成功
	if queue.GetCapacity() <= capacity {
		t.Errorf("应该发生扩容，期望容量 > %d，实际容量 %d", capacity, queue.GetCapacity())
	}

	// 验证元素正确
	if queue.GetSize() != capacity+1 {
		t.Errorf("期望大小 %d，实际大小 %d", capacity+1, queue.GetSize())
	}
}

// 测试循环特性 - 这是循环队列的核心
func TestCircularBehavior(t *testing.T) {
	queue := New()
	capacity := queue.GetCapacity()
	t.Logf("=== 循环特性测试，容量: %d ===", capacity)

	// 阶段1: 填满队列
	t.Logf("\n--- 阶段1: 填满队列 ---")
	for i := 0; i < capacity; i++ {
		err := queue.Enqueue(i)
		if err != nil {
			t.Fatalf("Enqueue() 失败: %v", err)
		}
		t.Logf("入队 %d: size=%d", i, queue.GetSize())
	}

	if !queue.IsFull() {
		t.Error("填满后队列应该已满")
	}

	// 阶段2: 出队几个元素，让 front 移动
	t.Logf("\n--- 阶段2: 出队部分元素 ---")
	for i := 0; i < 3; i++ {
		value, err := queue.Dequeue()
		if err != nil {
			t.Fatalf("Dequeue() 失败: %v", err)
		}
		t.Logf("出队 %v: size=%d", value, queue.GetSize())
	}

	// 阶段3: 继续入队，验证 rear 循环回到数组开头
	t.Logf("\n--- 阶段3: 继续入队，验证循环 ---")
	for i := 0; i < 3; i++ {
		newValue := 100 + i
		err := queue.Enqueue(newValue)
		if err != nil {
			t.Fatalf("Enqueue() 失败: %v", err)
		}
		t.Logf("入队 %d: size=%d", newValue, queue.GetSize())
	}

	// 阶段4: 验证元素顺序（FIFO）
	t.Logf("\n--- 阶段4: 验证元素顺序 ---")
	expectedOrder := []int{3, 4, 5, 6, 7, 8, 9, 100, 101, 102}
	for i, expected := range expectedOrder {
		value, err := queue.Dequeue()
		if err != nil {
			t.Fatalf("Dequeue() 失败: %v", err)
		}
		if value != expected {
			t.Errorf("位置 %d: 期望值 %d，实际值 %v", i, expected, value)
		}
		t.Logf("出队 %v: size=%d", value, queue.GetSize())
	}

	if !queue.IsEmpty() {
		t.Error("所有元素出队后队列应该为空")
	}
}

// 测试 Peek
func TestPeek(t *testing.T) {
	queue := New()

	// 测试空队列
	_, err := queue.Peek()
	if err == nil {
		t.Error("从空队列 Peek 应该返回错误")
	}

	// 添加元素
	queue.Enqueue(1)
	queue.Enqueue(2)
	queue.Enqueue(3)

	// 测试 Peek（不应该改变队列的大小）
	value, err := queue.Peek()
	if err != nil {
		t.Fatalf("Peek() 失败: %v", err)
	}
	if value != 1 {
		t.Errorf("期望值 1（队首），实际值 %v", value)
	}
	if queue.GetSize() != 3 {
		t.Errorf("Peek 后大小应该仍然是 3，实际是 %d", queue.GetSize())
	}

	// 再次 Peek 应该返回相同的值
	value2, err := queue.Peek()
	if err != nil {
		t.Fatalf("Peek() 失败: %v", err)
	}
	if value2 != 1 {
		t.Errorf("再次 Peek 应该返回相同的值 1，实际值 %v", value2)
	}
}

// 测试 IsEmpty
func TestIsEmpty(t *testing.T) {
	queue := New()
	if !queue.IsEmpty() {
		t.Error("新队列应该为空")
	}

	queue.Enqueue(1)
	if queue.IsEmpty() {
		t.Error("添加元素后队列不应该为空")
	}

	queue.Dequeue()
	if !queue.IsEmpty() {
		t.Error("删除所有元素后队列应该为空")
	}
}

// 测试 IsFull
func TestIsFull(t *testing.T) {
	queue := New()
	capacity := queue.GetCapacity()

	if queue.IsFull() {
		t.Error("新队列不应该已满")
	}

	// 填满队列
	for i := 0; i < capacity; i++ {
		queue.Enqueue(i)
	}

	if !queue.IsFull() {
		t.Error("填满后队列应该已满")
	}

	// 出队一个元素
	queue.Dequeue()
	if queue.IsFull() {
		t.Error("出队后队列不应该已满")
	}
}

// 测试 GetSize
func TestGetSize(t *testing.T) {
	queue := New()
	if queue.GetSize() != 0 {
		t.Errorf("新队列大小应该是 0，实际是 %d", queue.GetSize())
	}

	for i := 0; i < 5; i++ {
		queue.Enqueue(i)
		if queue.GetSize() != i+1 {
			t.Errorf("期望大小 %d，实际大小 %d", i+1, queue.GetSize())
		}
	}

	for i := 4; i >= 0; i-- {
		queue.Dequeue()
		if queue.GetSize() != i {
			t.Errorf("期望大小 %d，实际大小 %d", i, queue.GetSize())
		}
	}
}

// 测试 GetCapacity
func TestGetCapacity(t *testing.T) {
	queue := New()
	expectedCapacity := 10
	if queue.GetCapacity() != expectedCapacity {
		t.Errorf("期望容量 %d，实际容量 %d", expectedCapacity, queue.GetCapacity())
	}
}

// 测试 Clear
func TestClear(t *testing.T) {
	queue := New()

	// 添加一些元素
	for i := 0; i < 5; i++ {
		queue.Enqueue(i)
	}

	if queue.GetSize() != 5 {
		t.Errorf("期望大小 5，实际大小 %d", queue.GetSize())
	}

	// 清空队列
	queue.Clear()

	if !queue.IsEmpty() {
		t.Error("Clear 后队列应该为空")
	}

	if queue.GetSize() != 0 {
		t.Errorf("Clear 后期望大小 0，实际大小 %d", queue.GetSize())
	}

	// 清空后应该可以正常使用
	err := queue.Enqueue(100)
	if err != nil {
		t.Fatalf("Clear 后 Enqueue 失败: %v", err)
	}

	value, err := queue.Dequeue()
	if err != nil {
		t.Fatalf("Clear 后 Dequeue 失败: %v", err)
	}
	if value != 100 {
		t.Errorf("期望值 100，实际值 %v", value)
	}
}

// 综合测试
func TestIntegration(t *testing.T) {
	queue := New()
	capacity := queue.GetCapacity()

	// 阶段1: 填满队列
	for i := 0; i < capacity; i++ {
		err := queue.Enqueue(i)
		if err != nil {
			t.Fatalf("Enqueue() 失败: %v", err)
		}
	}

	if queue.GetSize() != capacity {
		t.Errorf("期望大小 %d，实际大小 %d", capacity, queue.GetSize())
	}

	// 阶段2: 出队一半
	for i := 0; i < capacity/2; i++ {
		value, err := queue.Dequeue()
		if err != nil {
			t.Fatalf("Dequeue() 失败: %v", err)
		}
		if value != i {
			t.Errorf("期望值 %d，实际值 %v", i, value)
		}
	}

	// 阶段3: 继续入队，验证循环
	for i := 0; i < capacity/2; i++ {
		err := queue.Enqueue(100 + i)
		if err != nil {
			t.Fatalf("Enqueue() 失败: %v", err)
		}
	}

	if queue.GetSize() != capacity {
		t.Errorf("期望大小 %d，实际大小 %d", capacity, queue.GetSize())
	}

	// 阶段4: 验证所有元素顺序
	expectedOrder := make([]int, 0, capacity)
	for i := capacity / 2; i < capacity; i++ {
		expectedOrder = append(expectedOrder, i)
	}
	for i := 0; i < capacity/2; i++ {
		expectedOrder = append(expectedOrder, 100+i)
	}

	for i, expected := range expectedOrder {
		value, err := queue.Dequeue()
		if err != nil {
			t.Fatalf("Dequeue() 失败: %v", err)
		}
		if value != expected {
			t.Errorf("位置 %d: 期望值 %d，实际值 %v", i, expected, value)
		}
	}

	if !queue.IsEmpty() {
		t.Error("所有元素出队后队列应该为空")
	}
}

// 测试边界情况：多次循环
func TestMultipleCycles(t *testing.T) {
	queue := New()
	capacity := queue.GetCapacity()

	// 进行多轮完整的入队和出队，验证循环稳定性
	for cycle := 0; cycle < 3; cycle++ {
		t.Logf("\n--- 循环轮次 %d ---", cycle+1)

		// 填满
		for i := 0; i < capacity; i++ {
			value := cycle*capacity + i
			err := queue.Enqueue(value)
			if err != nil {
				t.Fatalf("Enqueue() 失败: %v", err)
			}
		}

		// 全部出队
		for i := 0; i < capacity; i++ {
			expectedValue := cycle*capacity + i
			value, err := queue.Dequeue()
			if err != nil {
				t.Fatalf("Dequeue() 失败: %v", err)
			}
			if value != expectedValue {
				t.Errorf("循环 %d，位置 %d: 期望值 %d，实际值 %v", cycle+1, i, expectedValue, value)
			}
		}

		if !queue.IsEmpty() {
			t.Errorf("循环 %d 后队列应该为空", cycle+1)
		}
	}
}
