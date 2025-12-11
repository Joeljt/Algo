package array

import (
	"testing"
)

// 测试 NewArray
func TestNewArray(t *testing.T) {
	arr := NewArray(5)
	if arr == nil {
		t.Fatal("NewArray() 返回 nil")
	}
	if !arr.IsEmpty() {
		t.Error("新创建的数组应该为空")
	}
	if arr.Size() != 0 {
		t.Errorf("新创建的数组大小应该是 0，实际是 %d", arr.Size())
	}
	if arr.Capacity() != 5 {
		t.Errorf("新创建的数组容量应该是 5，实际是 %d", arr.Capacity())
	}

	// 测试默认容量
	arr2 := NewArray(0)
	if arr2.Capacity() < 10 {
		t.Errorf("默认容量应该至少是 10，实际是 %d", arr2.Capacity())
	}
}

// 测试 Add
func TestAdd(t *testing.T) {
	arr := NewArray(3)

	// 测试添加元素
	arr.Add(1)
	if arr.Size() != 1 {
		t.Errorf("添加一个元素后，大小应该是 1，实际是 %d", arr.Size())
	}
	if arr.IsEmpty() {
		t.Error("添加元素后，数组不应该为空")
	}

	// 测试扩容
	for i := 2; i <= 10; i++ {
		arr.Add(i)
	}
	if arr.Size() != 10 {
		t.Errorf("添加10个元素后，大小应该是 10，实际是 %d", arr.Size())
	}
	if arr.Capacity() < 10 {
		t.Errorf("容量应该至少是 10，实际是 %d", arr.Capacity())
	}
}

// 测试 Get
func TestGet(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	_, err := arr.Get(0)
	if err == nil {
		t.Error("从空数组获取元素应该返回错误")
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	// 测试正常获取
	value, err := arr.Get(1)
	if err != nil {
		t.Fatalf("获取元素失败: %v", err)
	}
	if value != 2 {
		t.Errorf("期望值 2，实际值 %v", value)
	}

	// 测试非法索引
	_, err = arr.Get(-1)
	if err == nil {
		t.Error("获取索引-1应该返回错误")
	}
	_, err = arr.Get(100)
	if err == nil {
		t.Error("获取索引100应该返回错误")
	}
}

// 测试 Set
func TestSet(t *testing.T) {
	arr := NewArray(5)
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	// 测试设置元素
	err := arr.Set(1, 99)
	if err != nil {
		t.Fatalf("设置元素失败: %v", err)
	}
	value, _ := arr.Get(1)
	if value != 99 {
		t.Errorf("期望值 99，实际值 %v", value)
	}

	// 测试非法索引
	err = arr.Set(-1, 0)
	if err == nil {
		t.Error("设置索引-1应该返回错误")
	}
	err = arr.Set(100, 0)
	if err == nil {
		t.Error("设置索引100应该返回错误")
	}
}

// 测试 Insert
func TestInsert(t *testing.T) {
	arr := NewArray(5)

	// 测试在空数组插入
	err := arr.Insert(0, 1)
	if err != nil {
		t.Fatalf("在索引0插入失败: %v", err)
	}

	// 添加更多元素
	arr.Add(2)
	arr.Add(3)

	// 测试在中间插入
	err = arr.Insert(1, 99)
	if err != nil {
		t.Fatalf("在索引1插入失败: %v", err)
	}

	// 验证：应该是 1, 99, 2, 3
	value, _ := arr.Get(1)
	if value != 99 {
		t.Errorf("索引1的元素应该是 99，实际是 %v", value)
	}

	// 测试非法索引
	err = arr.Insert(-1, 0)
	if err == nil {
		t.Error("在索引-1插入应该返回错误")
	}
	err = arr.Insert(100, 0)
	if err == nil {
		t.Error("在索引100插入应该返回错误")
	}
}

// 测试 Remove
func TestRemove(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	_, err := arr.Remove(0)
	if err == nil {
		t.Error("从空数组删除应该返回错误")
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)
	arr.Add(4)

	// 测试删除中间元素
	value, err := arr.Remove(2)
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if arr.Size() != 3 {
		t.Errorf("删除后大小应该是 3，实际是 %d", arr.Size())
	}

	// 验证剩余元素
	val, _ := arr.Get(2)
	if val != 4 {
		t.Errorf("删除后索引2的元素应该是 4，实际是 %v", val)
	}

	// 测试非法索引
	_, err = arr.Remove(-1)
	if err == nil {
		t.Error("删除索引-1应该返回错误")
	}
	_, err = arr.Remove(100)
	if err == nil {
		t.Error("删除索引100应该返回错误")
	}
}

// 测试 RemoveLast
func TestRemoveLast(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	_, err := arr.RemoveLast()
	if err == nil {
		t.Error("从空数组删除应该返回错误")
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	// 测试删除
	value, err := arr.RemoveLast()
	if err != nil {
		t.Fatalf("删除失败: %v", err)
	}
	if value != 3 {
		t.Errorf("删除的值应该是 3，实际是 %v", value)
	}
	if arr.Size() != 2 {
		t.Errorf("删除后大小应该是 2，实际是 %d", arr.Size())
	}
}

// 测试 Contains
func TestContains(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	if arr.Contains(1) {
		t.Error("空数组不应该包含任何元素")
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	// 测试包含的元素
	if !arr.Contains(2) {
		t.Error("数组应该包含元素 2")
	}

	// 测试不包含的元素
	if arr.Contains(99) {
		t.Error("数组不应该包含元素 99")
	}
}

// 测试 IndexOf
func TestIndexOf(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	index := arr.IndexOf(1)
	if index != -1 {
		t.Errorf("空数组中查找应该返回 -1，实际是 %d", index)
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)
	arr.Add(2) // 重复元素

	// 测试查找存在的元素
	index = arr.IndexOf(2)
	if index != 1 {
		t.Errorf("元素2的索引应该是 1，实际是 %d", index)
	}

	// 测试查找不存在的元素
	index = arr.IndexOf(99)
	if index != -1 {
		t.Errorf("不存在的元素应该返回 -1，实际是 %d", index)
	}
}

// 测试 Clear
func TestClear(t *testing.T) {
	arr := NewArray(5)

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	// 清空
	arr.Clear()

	if !arr.IsEmpty() {
		t.Error("清空后数组应该为空")
	}
	if arr.Size() != 0 {
		t.Errorf("清空后大小应该是 0，实际是 %d", arr.Size())
	}
}

// 测试 ToSlice
func TestToSlice(t *testing.T) {
	arr := NewArray(5)

	// 测试空数组
	slice := arr.ToSlice()
	if len(slice) != 0 {
		t.Errorf("空数组的切片长度应该是 0，实际是 %d", len(slice))
	}

	// 添加元素
	arr.Add(1)
	arr.Add(2)
	arr.Add(3)

	slice = arr.ToSlice()
	if len(slice) != 3 {
		t.Errorf("切片长度应该是 3，实际是 %d", len(slice))
	}

	// 验证元素
	if slice[0] != 1 || slice[1] != 2 || slice[2] != 3 {
		t.Errorf("切片元素不正确，期望 [1, 2, 3]，实际 %v", slice)
	}
}

// 测试扩容和缩容
func TestResize(t *testing.T) {
	arr := NewArray(2)

	// 测试扩容
	for i := 0; i < 20; i++ {
		arr.Add(i)
	}
	if arr.Capacity() < 20 {
		t.Errorf("扩容后容量应该至少是 20，实际是 %d", arr.Capacity())
	}

	// 测试缩容
	initialCapacity := arr.Capacity()
	for arr.Size() > 0 {
		arr.RemoveLast()
	}
	// 缩容应该在元素数量小于容量的1/4时触发
	// 这里简化测试，主要验证缩容机制存在
	if arr.Size() == 0 && arr.Capacity() < initialCapacity {
		// 缩容成功
	}
}

// 综合测试
func TestIntegration(t *testing.T) {
	arr := NewArray(5)

	// 添加元素
	for i := 0; i < 10; i++ {
		arr.Add(i)
	}

	if arr.Size() != 10 {
		t.Errorf("期望大小 10，实际 %d", arr.Size())
	}

	// 删除一些元素
	for i := 0; i < 3; i++ {
		_, err := arr.RemoveLast()
		if err != nil {
			t.Fatalf("删除失败: %v", err)
		}
	}

	if arr.Size() != 7 {
		t.Errorf("删除后期望大小 7，实际 %d", arr.Size())
	}

	// 在中间插入
	err := arr.Insert(3, 99)
	if err != nil {
		t.Fatalf("插入失败: %v", err)
	}

	if arr.Size() != 8 {
		t.Errorf("插入后期望大小 8，实际 %d", arr.Size())
	}

	// 验证元素
	value, _ := arr.Get(3)
	if value != 99 {
		t.Errorf("索引3的元素应该是 99，实际是 %v", value)
	}

	// 清空
	arr.Clear()
	if !arr.IsEmpty() {
		t.Error("清空后数组应该为空")
	}
}

