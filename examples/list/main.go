package main

import (
	"fmt"
	"joseph/algo/datastructure/list"
)

// 双链表示例程序
func main() {
	// 创建双链表
	ll := list.New()
	fmt.Println("初始链表:", ll)
	fmt.Println("是否为空:", ll.IsEmpty())
	fmt.Println("链表大小:", ll.GetSize())
	fmt.Println()

	// 测试 AddFirst - 在头部插入
	fmt.Println("=== 测试 AddFirst ===")
	for i := 0; i < 5; i++ {
		ll.AddFirst(i * 10)
		fmt.Printf("在头部插入 %d, 链表: %s\n", i*10, ll)
	}
	fmt.Println()

	// 测试 AddLast - 在尾部插入
	fmt.Println("=== 测试 AddLast ===")
	for i := 5; i < 10; i++ {
		ll.AddLast(i * 10)
		fmt.Printf("在尾部插入 %d, 链表大小: %d\n", i*10, ll.GetSize())
	}
	fmt.Println("插入后链表:", ll)
	fmt.Println()

	// 测试 AddAt - 在指定位置插入
	fmt.Println("=== 测试 AddAt ===")
	ll.AddAt(3, 999)
	fmt.Println("在索引3插入999后:", ll)
	ll.AddAt(0, 111)
	fmt.Println("在索引0插入111后:", ll)
	ll.AddAt(ll.GetSize(), 888)
	fmt.Println("在末尾插入888后:", ll)
	fmt.Println()

	// 测试 Get - 获取元素
	fmt.Println("=== 测试 Get ===")
	for i := 0; i < 3; i++ {
		value, err := ll.Get(i)
		if err != nil {
			fmt.Printf("获取索引%d失败: %v\n", i, err)
		} else {
			fmt.Printf("索引%d的元素: %v\n", i, value)
		}
	}
	fmt.Println()

	// 测试 Set - 设置元素（双链表特有，支持双向遍历优化）
	fmt.Println("=== 测试 Set（双链表特有） ===")
	fmt.Println("设置前链表:", ll)
	// 设置前半部分的元素（从前向后遍历）
	err := ll.Set(1, 777)
	if err != nil {
		fmt.Printf("设置失败: %v\n", err)
	} else {
		value, _ := ll.Get(1)
		fmt.Printf("设置索引1为777后，索引1的值: %v\n", value)
	}
	// 设置后半部分的元素（从后向前遍历，利用双向遍历优化）
	err = ll.Set(ll.GetSize()-1, 666)
	if err != nil {
		fmt.Printf("设置失败: %v\n", err)
	} else {
		value, _ := ll.Get(ll.GetSize() - 1)
		fmt.Printf("设置最后一个元素为666后，最后一个元素的值: %v\n", value)
	}
	fmt.Println("设置后链表:", ll)
	fmt.Println()

	// 测试 RemoveFirst - 删除头节点
	fmt.Println("=== 测试 RemoveFirst ===")
	for i := 0; i < 3; i++ {
		removed, err := ll.RemoveFirst()
		if err != nil {
			fmt.Printf("删除失败: %v\n", err)
		} else {
			fmt.Printf("删除头节点: %v, 删除后链表: %s\n", removed, ll)
		}
	}
	fmt.Println()

	// 测试 RemoveLast - 删除尾节点
	fmt.Println("=== 测试 RemoveLast ===")
	for i := 0; i < 3; i++ {
		removed, err := ll.RemoveLast()
		if err != nil {
			fmt.Printf("删除失败: %v\n", err)
		} else {
			fmt.Printf("删除尾节点: %v, 删除后链表大小: %d\n", removed, ll.GetSize())
		}
	}
	fmt.Println("删除后链表:", ll)
	fmt.Println()

	// 测试 RemoveAt - 按索引删除
	fmt.Println("=== 测试 RemoveAt ===")
	fmt.Println("删除前链表:", ll)
	removed, err := ll.RemoveAt(1)
	if err != nil {
		fmt.Printf("删除失败: %v\n", err)
	} else {
		fmt.Printf("删除索引1的元素: %v, 删除后链表: %s\n", removed, ll)
	}
	fmt.Println()

	// 测试 ToSlice - 转换为切片
	fmt.Println("=== 测试 ToSlice ===")
	slice := ll.ToSlice()
	fmt.Printf("链表转换为切片: %v\n", slice)
	fmt.Println()

	// 测试边界情况
	fmt.Println("=== 测试边界情况 ===")
	// 测试空链表删除
	emptyList := list.New()
	_, err = emptyList.RemoveFirst()
	if err != nil {
		fmt.Printf("空链表删除头节点（预期错误）: %v\n", err)
	}
	_, err = emptyList.RemoveLast()
	if err != nil {
		fmt.Printf("空链表删除尾节点（预期错误）: %v\n", err)
	}
	_, err = emptyList.Get(0)
	if err != nil {
		fmt.Printf("空链表获取元素（预期错误）: %v\n", err)
	}
	fmt.Println()

	// 测试非法索引
	fmt.Println("=== 测试非法索引 ===")
	_, err = ll.Get(-1)
	if err != nil {
		fmt.Printf("获取索引-1（预期错误）: %v\n", err)
	}
	_, err = ll.Get(100)
	if err != nil {
		fmt.Printf("获取索引100（预期错误）: %v\n", err)
	}
	err = ll.AddAt(-1, 999)
	if err != nil {
		fmt.Printf("在索引-1插入（预期错误）: %v\n", err)
	}
	err = ll.AddAt(100, 999)
	if err != nil {
		fmt.Printf("在索引100插入（预期错误）: %v\n", err)
	}
	fmt.Println()

	// 测试 Clear - 清空链表
	fmt.Println("=== 测试 Clear ===")
	fmt.Println("清空前链表:", ll)
	ll.Clear()
	fmt.Println("清空后链表:", ll)
	fmt.Println("清空后是否为空:", ll.IsEmpty())
	fmt.Println("清空后大小:", ll.GetSize())
	fmt.Println()

	// 测试单个节点的情况
	fmt.Println("=== 测试单个节点 ===")
	singleList := list.New()
	singleList.AddFirst(42)
	fmt.Println("单个节点链表:", singleList)
	removed, err = singleList.RemoveLast()
	if err != nil {
		fmt.Printf("删除失败: %v\n", err)
	} else {
		fmt.Printf("删除后: %v, 链表: %s\n", removed, singleList)
	}
	fmt.Println()

	// 测试双链表的双向遍历特性
	fmt.Println("=== 测试双链表的双向遍历特性 ===")
	testList := list.New()
	for i := 0; i < 10; i++ {
		testList.AddLast(i)
	}
	fmt.Println("创建包含10个元素的链表:", testList)

	// 测试 Set 方法的前半部分遍历（从前向后）
	fmt.Println("设置索引2（前半部分，从前向后遍历）:")
	err = testList.Set(2, 222)
	if err != nil {
		fmt.Printf("设置失败: %v\n", err)
	} else {
		value, _ := testList.Get(2)
		fmt.Printf("索引2的值: %v\n", value)
	}

	// 测试 Set 方法的后半部分遍历（从后向前）
	fmt.Println("设置索引7（后半部分，从后向前遍历）:")
	err = testList.Set(7, 777)
	if err != nil {
		fmt.Printf("设置失败: %v\n", err)
	} else {
		value, _ := testList.Get(7)
		fmt.Printf("索引7的值: %v\n", value)
	}
	fmt.Println("修改后链表:", testList)
	fmt.Println()

	// 测试 Dummy.Prev 的维护
	fmt.Println("=== 测试 Dummy.Prev 的维护 ===")
	fmt.Printf("当前链表大小: %d\n", testList.GetSize())
	fmt.Printf("Dummy.Prev 指向的节点值: %v\n", testList.Dummy.Prev.Value)
	fmt.Println("删除最后一个节点...")
	testList.RemoveLast()
	fmt.Printf("删除后链表大小: %d\n", testList.GetSize())
	fmt.Printf("删除后 Dummy.Prev 指向的节点值: %v\n", testList.Dummy.Prev.Value)
	fmt.Println()

	fmt.Println("=== 所有测试完成 ===")
}
