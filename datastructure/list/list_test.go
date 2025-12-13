package list

import (
	"testing"
)

// 测试 New
func TestNew(t *testing.T) {
	l := New()
	if l == nil {
		t.Fatal("New() 返回 nil")
	}
	if !l.IsEmpty() {
		t.Error("新创建的链表应该为空")
	}
	if l.GetSize() != 0 {
		t.Errorf("新创建的链表大小应该是 0，实际是 %d", l.GetSize())
	}
	if l.Dummy == nil {
		t.Error("Dummy 节点不应该为 nil")
	}
	if l.Dummy.Next != nil {
		t.Error("新链表的 Dummy.Next 应该为 nil")
	}
	if l.Dummy.Prev != nil {
		t.Error("新链表的 Dummy.Prev 应该为 nil")
	}
}

// 测试 AddFirst
func TestAddFirst(t *testing.T) {
	l := New()

	l.AddFirst(1)
	if l.GetSize() != 1 {
		t.Errorf("添加一个元素后，大小应该是 1，实际是 %d", l.GetSize())
	}
	if l.IsEmpty() {
		t.Error("添加元素后，链表不应该为空")
	}

	value, err := l.Get(0)
	if err != nil {
		t.Fatalf("获取元素失败: %v", err)
	}
	if value != 1 {
		t.Errorf("期望值 1，实际值 %v", value)
	}

	// 测试在头部插入多个元素
	l.AddFirst(2)
	l.AddFirst(3)
	if l.GetSize() != 3 {
		t.Errorf("添加三个元素后，大小应该是 3，实际是 %d", l.GetSize())
	}

	// 验证顺序：应该是 3, 2, 1
	first, _ := l.Get(0)
	if first != 3 {
		t.Errorf("第一个元素应该是 3，实际是 %v", first)
	}

	// 验证 Dummy.Prev 指向最后一个节点
	if l.Dummy.Prev == nil {
		t.Error("Dummy.Prev 应该指向最后一个节点")
	}
	if l.Dummy.Prev.Value != 1 {
		t.Errorf("Dummy.Prev 应该指向值为 1 的节点，实际是 %v", l.Dummy.Prev.Value)
	}
}

// 测试 AddLast
func TestAddLast(t *testing.T) {
	l := New()

	l.AddLast(1)
	if l.GetSize() != 1 {
		t.Errorf("添加一个元素后，大小应该是 1，实际是 %d", l.GetSize())
	}

	l.AddLast(2)
	l.AddLast(3)
	if l.GetSize() != 3 {
		t.Errorf("添加三个元素后，大小应该是 3，实际是 %d", l.GetSize())
	}

	// 验证顺序：应该是 1, 2, 3
	first, _ := l.Get(0)
	if first != 1 {
		t.Errorf("第一个元素应该是 1，实际是 %v", first)
	}
	last, _ := l.Get(2)
	if last != 3 {
		t.Errorf("最后一个元素应该是 3，实际是 %v", last)
	}

	// 验证 Dummy.Prev 指向最后一个节点
	if l.Dummy.Prev == nil {
		t.Error("Dummy.Prev 应该指向最后一个节点")
	}
	if l.Dummy.Prev.Value != 3 {
		t.Errorf("Dummy.Prev 应该指向值为 3 的节点，实际是 %v", l.Dummy.Prev.Value)
	}
}

// 测试 AddAt
func TestAddAt(t *testing.T) {
	l := New()

	// 测试在空链表插入
	err := l.AddAt(0, 1)
	if err != nil {
		t.Fatalf("在索引0插入失败: %v", err)
	}

	// 测试在中间插入
	l.AddLast(2)
	l.AddLast(3)
	err = l.AddAt(1, 99)
	if err != nil {
		t.Fatalf("在索引1插入失败: %v", err)
	}

	// 验证：应该是 1, 99, 2, 3
	value, _ := l.Get(1)
	if value != 99 {
		t.Errorf("索引1的元素应该是 99，实际是 %v", value)
	}

	// 验证 Dummy.Prev 仍然指向最后一个节点
	if l.Dummy.Prev.Value != 3 {
		t.Errorf("Dummy.Prev 应该指向值为 3 的节点，实际是 %v", l.Dummy.Prev.Value)
	}

	// 测试在末尾插入
	err = l.AddAt(l.GetSize(), 100)
	if err != nil {
		t.Fatalf("在末尾插入失败: %v", err)
	}
	if l.Dummy.Prev.Value != 100 {
		t.Errorf("Dummy.Prev 应该指向值为 100 的节点，实际是 %v", l.Dummy.Prev.Value)
	}

	// 测试非法索引
	err = l.AddAt(-1, 0)
	if err == nil {
		t.Error("在索引-1插入应该返回错误")
	}
	err = l.AddAt(100, 0)
	if err == nil {
		t.Error("在索引100插入应该返回错误")
	}
}

// 测试 Get
func TestGet(t *testing.T) {
	l := New()

	// 测试空链表
	_, err := l.Get(0)
	if err == nil {
		t.Error("从空链表获取元素应该返回错误")
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)

	// 测试正常获取
	value, err := l.Get(1)
	if err != nil {
		t.Fatalf("获取元素失败: %v", err)
	}
	if value != 2 {
		t.Errorf("期望值 2，实际值 %v", value)
	}

	// 测试非法索引
	_, err = l.Get(-1)
	if err == nil {
		t.Error("获取索引-1应该返回错误")
	}
	_, err = l.Get(100)
	if err == nil {
		t.Error("获取索引100应该返回错误")
	}
}

// 测试 Set
func TestSet(t *testing.T) {
	l := New()

	// 测试空链表
	err := l.Set(0, 1)
	if err == nil {
		t.Error("在空链表设置元素应该返回错误")
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)
	l.AddLast(4)
	l.AddLast(5)

	// 测试设置前半部分的元素（从前向后遍历）
	err = l.Set(1, 99)
	if err != nil {
		t.Fatalf("设置元素失败: %v", err)
	}
	value, _ := l.Get(1)
	if value != 99 {
		t.Errorf("索引1的元素应该是 99，实际是 %v", value)
	}

	// 测试设置后半部分的元素（从后向前遍历）
	err = l.Set(4, 100)
	if err != nil {
		t.Fatalf("设置元素失败: %v", err)
	}
	value, _ = l.Get(4)
	if value != 100 {
		t.Errorf("索引4的元素应该是 100，实际是 %v", value)
	}

	// 测试设置中间元素（边界情况）
	err = l.Set(2, 200)
	if err != nil {
		t.Fatalf("设置元素失败: %v", err)
	}
	value, _ = l.Get(2)
	if value != 200 {
		t.Errorf("索引2的元素应该是 200，实际是 %v", value)
	}

	// 测试非法索引
	err = l.Set(-1, 0)
	if err == nil {
		t.Error("设置索引-1应该返回错误")
	}
	err = l.Set(100, 0)
	if err == nil {
		t.Error("设置索引100应该返回错误")
	}
}

// 测试 RemoveFirst
func TestRemoveFirst(t *testing.T) {
	l := New()

	// 测试空链表
	_, err := l.RemoveFirst()
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)

	// 测试删除
	value, err := l.RemoveFirst()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}
	if l.GetSize() != 2 {
		t.Errorf("删除后大小应该是 2，实际是 %d", l.GetSize())
	}

	// 验证剩余元素
	first, _ := l.Get(0)
	if first != 2 {
		t.Errorf("删除后第一个元素应该是 2，实际是 %v", first)
	}
}

// 测试 RemoveLast
func TestRemoveLast(t *testing.T) {
	l := New()

	// 测试空链表
	_, err := l.RemoveLast()
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}

	// 测试单个元素
	l.AddLast(1)
	value, err := l.RemoveLast()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}
	if !l.IsEmpty() {
		t.Error("删除后链表应该为空")
	}
	// 验证 Dummy.Prev 应该为 nil
	if l.Dummy.Prev != nil {
		t.Error("删除最后一个节点后，Dummy.Prev 应该为 nil")
	}

	// 测试多个元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)
	value, err = l.RemoveLast()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if l.GetSize() != 2 {
		t.Errorf("删除后大小应该是 2，实际是 %d", l.GetSize())
	}
	// 验证 Dummy.Prev 指向新的最后一个节点
	if l.Dummy.Prev.Value != 2 {
		t.Errorf("Dummy.Prev 应该指向值为 2 的节点，实际是 %v", l.Dummy.Prev.Value)
	}
}

// 测试 RemoveAt
func TestRemoveAt(t *testing.T) {
	l := New()

	// 测试空链表
	_, err := l.RemoveAt(0)
	if err == nil {
		t.Error("从空链表删除应该返回错误")
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)
	l.AddLast(4)

	// 测试删除中间元素
	value, err := l.RemoveAt(2)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if l.GetSize() != 3 {
		t.Errorf("删除后大小应该是 3，实际是 %d", l.GetSize())
	}

	// 测试删除头节点
	value, err = l.RemoveAt(0)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 1 {
		t.Errorf("删除的值应该是 1，实际是 %v", value)
	}

	// 测试删除尾节点
	value, err = l.RemoveAt(l.GetSize() - 1)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 4 {
		t.Errorf("删除的值应该是 4，实际是 %v", value)
	}
	// 验证 Dummy.Prev 指向新的最后一个节点
	if l.Dummy.Prev.Value != 2 {
		t.Errorf("Dummy.Prev 应该指向值为 2 的节点，实际是 %v", l.Dummy.Prev.Value)
	}

	// 测试删除最后一个节点（链表变为空）
	value, err = l.RemoveAt(0)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 2 {
		t.Errorf("删除的值应该是 2，实际是 %v", value)
	}
	if l.GetSize() != 0 {
		t.Errorf("删除后大小应该是 0，实际是 %d", l.GetSize())
	}
	// 验证 Dummy.Prev 应该为 nil
	if l.Dummy.Prev != nil {
		t.Error("删除最后一个节点后，Dummy.Prev 应该为 nil")
	}

	// 测试非法索引
	l.AddLast(1)
	_, err = l.RemoveAt(-1)
	if err == nil {
		t.Error("删除索引-1应该返回错误")
	}
	_, err = l.RemoveAt(100)
	if err == nil {
		t.Error("删除索引100应该返回错误")
	}
}

// 测试 Clear
func TestClear(t *testing.T) {
	l := New()

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)

	// 清空
	l.Clear()

	if !l.IsEmpty() {
		t.Error("清空后链表应该为空")
	}
	if l.GetSize() != 0 {
		t.Errorf("清空后大小应该是 0，实际是 %d", l.GetSize())
	}
	if l.Dummy.Next != nil {
		t.Error("清空后 Dummy.Next 应该为 nil")
	}
	if l.Dummy.Prev != nil {
		t.Error("清空后 Dummy.Prev 应该为 nil")
	}
}

// 测试 ToSlice
func TestToSlice(t *testing.T) {
	l := New()

	// 测试空链表
	slice := l.ToSlice()
	if len(slice) != 0 {
		t.Errorf("空链表的切片长度应该是 0，实际是 %d", len(slice))
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)

	slice = l.ToSlice()
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
	l := New()

	// 测试空链表
	str := l.String()
	if str == "" {
		t.Error("String() 不应该返回空字符串")
	}

	// 添加元素
	l.AddLast(1)
	l.AddLast(2)
	l.AddLast(3)

	str = l.String()
	if str == "" {
		t.Error("String() 不应该返回空字符串")
	}
	// 验证字符串包含正确的信息
	if len(str) == 0 {
		t.Error("String() 应该返回非空字符串")
	}
}

// 测试 Dummy.Prev 的维护
func TestDummyPrevMaintenance(t *testing.T) {
	l := New()

	// 空链表时 Dummy.Prev 应该为 nil
	if l.Dummy.Prev != nil {
		t.Error("空链表时 Dummy.Prev 应该为 nil")
	}

	// 添加第一个节点
	l.AddFirst(1)
	if l.Dummy.Prev == nil || l.Dummy.Prev.Value != 1 {
		t.Error("添加第一个节点后，Dummy.Prev 应该指向该节点")
	}

	// 在头部添加节点（Dummy.Prev 应该不变）
	l.AddFirst(2)
	if l.Dummy.Prev.Value != 1 {
		t.Error("在头部添加节点后，Dummy.Prev 应该仍然指向最后一个节点")
	}

	// 在尾部添加节点（Dummy.Prev 应该更新）
	l.AddLast(3)
	if l.Dummy.Prev.Value != 3 {
		t.Error("在尾部添加节点后，Dummy.Prev 应该指向新节点")
	}

	// 删除最后一个节点
	l.RemoveLast()
	if l.Dummy.Prev.Value != 1 {
		t.Error("删除最后一个节点后，Dummy.Prev 应该指向新的最后一个节点")
	}

	// 删除所有节点
	l.RemoveLast()
	l.RemoveLast()
	if l.Dummy.Prev != nil {
		t.Error("删除所有节点后，Dummy.Prev 应该为 nil")
	}
}

// 综合测试：测试各种操作的组合
func TestIntegration(t *testing.T) {
	l := New()

	// 添加元素
	for i := 0; i < 10; i++ {
		l.AddLast(i)
	}

	if l.GetSize() != 10 {
		t.Errorf("期望大小 10，实际 %d", l.GetSize())
	}

	// 验证 Dummy.Prev
	if l.Dummy.Prev.Value != 9 {
		t.Errorf("Dummy.Prev 应该指向值为 9 的节点，实际是 %v", l.Dummy.Prev.Value)
	}

	// 删除一些元素
	for i := 0; i < 3; i++ {
		_, err := l.RemoveFirst()
		if err != nil {
			t.Fatalf("删除失败: %v", err)
		}
	}

	if l.GetSize() != 7 {
		t.Errorf("删除后期望大小 7，实际 %d", l.GetSize())
	}

	// 在中间插入
	err := l.AddAt(3, 99)
	if err != nil {
		t.Fatalf("插入失败: %v", err)
	}

	if l.GetSize() != 8 {
		t.Errorf("插入后期望大小 8，实际 %d", l.GetSize())
	}

	// 验证元素
	value, _ := l.Get(3)
	if value != 99 {
		t.Errorf("索引3的元素应该是 99，实际是 %v", value)
	}

	// 测试 Set 的双向遍历优化
	err = l.Set(1, 100) // 前半部分
	if err != nil {
		t.Fatalf("设置失败: %v", err)
	}
	value, _ = l.Get(1)
	if value != 100 {
		t.Errorf("索引1的元素应该是 100，实际是 %v", value)
	}

	err = l.Set(6, 200) // 后半部分
	if err != nil {
		t.Fatalf("设置失败: %v", err)
	}
	value, _ = l.Get(6)
	if value != 200 {
		t.Errorf("索引6的元素应该是 200，实际是 %v", value)
	}

	// 清空
	l.Clear()
	if !l.IsEmpty() {
		t.Error("清空后链表应该为空")
	}
	if l.Dummy.Prev != nil {
		t.Error("清空后 Dummy.Prev 应该为 nil")
	}
}
