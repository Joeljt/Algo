package linkedlist

import (
	"testing"
)

// 测试 NewLinkedList
func TestNewLinkedList(t *testing.T) {
	ll := NewLinkedList()
	if ll == nil {
		t.Fatal("NewLinkedList() 返回 nil")
	}
	if !ll.IsEmpty() {
		t.Error("新创建的链表应该为空")
	}
	if ll.GetSize() != 0 {
		t.Errorf("新创建的链表大小应该是 0，实际是 %d", ll.GetSize())
	}
}

// 测试 AddFirst
func TestAddFirst(t *testing.T) {
	ll := NewLinkedList()
	
	ll.AddFirst(1)
	if ll.GetSize() != 1 {
		t.Errorf("添加一个元素后，大小应该是 1，实际是 %d", ll.GetSize())
	}
	if ll.IsEmpty() {
		t.Error("添加元素后，链表不应该为空")
	}
	
	value, err := ll.Get(0)
	if err != nil {
		t.Fatalf("获取元素失败: %v", err)
	}
	if value != 1 {
		t.Errorf("期望值 1，实际值 %v", value)
	}
	
	// 测试在头部插入多个元素
	ll.AddFirst(2)
	ll.AddFirst(3)
	if ll.GetSize() != 3 {
		t.Errorf("添加三个元素后，大小应该是 3，实际是 %d", ll.GetSize())
	}
	
	// 验证顺序：应该是 3, 2, 1
	first, _ := ll.Get(0)
	if first != 3 {
		t.Errorf("第一个元素应该是 3，实际是 %v", first)
	}
}

// 测试 AddLast
func TestAddLast(t *testing.T) {
	ll := NewLinkedList()
	
	ll.AddLast(1)
	if ll.GetSize() != 1 {
		t.Errorf("添加一个元素后，大小应该是 1，实际是 %d", ll.GetSize())
	}
	
	ll.AddLast(2)
	ll.AddLast(3)
	if ll.GetSize() != 3 {
		t.Errorf("添加三个元素后，大小应该是 3，实际是 %d", ll.GetSize())
	}
	
	// 验证顺序：应该是 1, 2, 3
	first, _ := ll.Get(0)
	if first != 1 {
		t.Errorf("第一个元素应该是 1，实际是 %v", first)
	}
	last, _ := ll.Get(2)
	if last != 3 {
		t.Errorf("最后一个元素应该是 3，实际是 %v", last)
	}
}

// 测试 AddAt
func TestAddAt(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试在空链表插入
	err := ll.AddAt(0, 1)
	if err != nil {
		t.Fatalf("在索引0插入失败: %v", err)
	}
	
	// 测试在中间插入
	ll.AddLast(2)
	ll.AddLast(3)
	err = ll.AddAt(1, 99)
	if err != nil {
		t.Fatalf("在索引1插入失败: %v", err)
	}
	
	// 验证：应该是 1, 99, 2, 3
	value, _ := ll.Get(1)
	if value != 99 {
		t.Errorf("索引1的元素应该是 99，实际是 %v", value)
	}
	
	// 测试非法索引
	err = ll.AddAt(-1, 0)
	if err == nil {
		t.Error("在索引-1插入应该返回错误")
	}
	err = ll.AddAt(100, 0)
	if err == nil {
		t.Error("在索引100插入应该返回错误")
	}
}

// 测试 Get
func TestGet(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	_, err := ll.Get(0)
	if err == nil {
		t.Error("从空链表获取元素应该返回错误")
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	// 测试正常获取
	value, err := ll.Get(1)
	if err != nil {
		t.Fatalf("获取元素失败: %v", err)
	}
	if value != 2 {
		t.Errorf("期望值 2，实际值 %v", value)
	}
	
	// 测试非法索引
	_, err = ll.Get(-1)
	if err == nil {
		t.Error("获取索引-1应该返回错误")
	}
	_, err = ll.Get(100)
	if err == nil {
		t.Error("获取索引100应该返回错误")
	}
}

// 测试 RemoveFirst
func TestRemoveFirst(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	_, err := ll.RemoveFirst()
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	// 测试删除
	value, err := ll.RemoveFirst()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}
	if ll.GetSize() != 2 {
		t.Errorf("删除后大小应该是 2，实际是 %d", ll.GetSize())
	}
	
	// 验证剩余元素
	first, _ := ll.Get(0)
	if first != 2 {
		t.Errorf("删除后第一个元素应该是 2，实际是 %v", first)
	}
}

// 测试 RemoveLast
func TestRemoveLast(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	_, err := ll.RemoveLast()
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}
	
	// 测试单个元素
	ll.AddLast(1)
	value, err := ll.RemoveLast()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}
	if !ll.IsEmpty() {
		t.Error("删除后链表应该为空")
	}
	
	// 测试多个元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	value, err = ll.RemoveLast()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if ll.GetSize() != 2 {
		t.Errorf("删除后大小应该是 2，实际是 %d", ll.GetSize())
	}
}

// 测试 RemoveAt
func TestRemoveAt(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	_, err := ll.RemoveAt(0)
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	ll.AddLast(4)
	
	// 测试删除中间元素
	value, err := ll.RemoveAt(2)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if ll.GetSize() != 3 {
		t.Errorf("删除后大小应该是 3，实际是 %d", ll.GetSize())
	}
	
	// 测试删除头节点
	value, err = ll.RemoveAt(0)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}
	
	// 测试删除尾节点
	value, err = ll.RemoveAt(ll.GetSize() - 1)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 4 {
		t.Errorf("删除的值应该是 4，实际是 %v", value)
	}
	
	// 测试非法索引
	_, err = ll.RemoveAt(-1)
	if err == nil {
		t.Error("删除索引-1应该返回错误")
	}
	_, err = ll.RemoveAt(100)
	if err == nil {
		t.Error("删除索引100应该返回错误")
	}
}

// 测试 IndexOf
func TestIndexOf(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	index := ll.IndexOf(1)
	if index != -1 {
		t.Errorf("空链表中查找应该返回 -1，实际是 %d", index)
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	ll.AddLast(2) // 重复元素
	
	// 测试查找存在的元素
	index = ll.IndexOf(2)
	if index != 1 {
		t.Errorf("元素2的索引应该是 1，实际是 %d", index)
	}
	
	// 测试查找不存在的元素
	index = ll.IndexOf(99)
	if index != -1 {
		t.Errorf("不存在的元素应该返回 -1，实际是 %d", index)
	}
}

// 测试 Contains
func TestContains(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	if ll.Contains(1) {
		t.Error("空链表不应该包含任何元素")
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	// 测试包含的元素
	if !ll.Contains(2) {
		t.Error("链表应该包含元素 2")
	}
	
	// 测试不包含的元素
	if ll.Contains(99) {
		t.Error("链表不应该包含元素 99")
	}
}

// 测试 Clear
func TestClear(t *testing.T) {
	ll := NewLinkedList()
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	// 清空
	ll.Clear()
	
	if !ll.IsEmpty() {
		t.Error("清空后链表应该为空")
	}
	if ll.GetSize() != 0 {
		t.Errorf("清空后大小应该是 0，实际是 %d", ll.GetSize())
	}
}

// 测试 ToSlice
func TestToSlice(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	slice := ll.ToSlice()
	if len(slice) != 0 {
		t.Errorf("空链表的切片长度应该是 0，实际是 %d", len(slice))
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	slice = ll.ToSlice()
	if len(slice) != 3 {
		t.Errorf("切片长度应该是 3，实际是 %d", len(slice))
	}
	
	// 验证元素
	if slice[0] != 1 || slice[1] != 2 || slice[2] != 3 {
		t.Errorf("切片元素不正确，期望 [1, 2, 3]，实际 %v", slice)
	}
}

// 测试 String
func TestString(t *testing.T) {
	ll := NewLinkedList()
	
	// 测试空链表
	str := ll.String()
	if str == "" {
		t.Error("String() 不应该返回空字符串")
	}
	
	// 添加元素
	ll.AddLast(1)
	ll.AddLast(2)
	ll.AddLast(3)
	
	str = ll.String()
	if str == "" {
		t.Error("String() 不应该返回空字符串")
	}
}

// 综合测试：测试各种操作的组合
func TestIntegration(t *testing.T) {
	ll := NewLinkedList()
	
	// 添加元素
	for i := 0; i < 10; i++ {
		ll.AddLast(i)
	}
	
	if ll.GetSize() != 10 {
		t.Errorf("期望大小 10，实际 %d", ll.GetSize())
	}
	
	// 删除一些元素
	for i := 0; i < 3; i++ {
		_, err := ll.RemoveFirst()
		if err != nil {
			t.Fatalf("删除失败: %v", err)
		}
	}
	
	if ll.GetSize() != 7 {
		t.Errorf("删除后期望大小 7，实际 %d", ll.GetSize())
	}
	
	// 在中间插入
	err := ll.AddAt(3, 99)
	if err != nil {
		t.Fatalf("插入失败: %v", err)
	}
	
	if ll.GetSize() != 8 {
		t.Errorf("插入后期望大小 8，实际 %d", ll.GetSize())
	}
	
	// 验证元素
	value, _ := ll.Get(3)
	if value != 99 {
		t.Errorf("索引3的元素应该是 99，实际是 %v", value)
	}
	
	// 清空
	ll.Clear()
	if !ll.IsEmpty() {
		t.Error("清空后链表应该为空")
	}
}

