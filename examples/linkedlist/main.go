package main

import (
	"fmt"
	"joseph/algo/datastructure/linkedlist"
)

// 链表示例程序
func main() {
	// 创建单链表
	ll := linkedlist.NewLinkedList()
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

	// 测试 IndexOf 和 Contains
	fmt.Println("=== 测试 IndexOf 和 Contains ===")
	testValues := []any{999, 50, 111, 9999}
	for _, val := range testValues {
		index := ll.IndexOf(val)
		contains := ll.Contains(val)
		if index != -1 {
			fmt.Printf("值 %v 的索引: %d, 是否包含: %v\n", val, index, contains)
		} else {
			fmt.Printf("值 %v 不存在, 是否包含: %v\n", val, contains)
		}
	}
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
	emptyList := linkedlist.NewLinkedList()
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
	singleList := linkedlist.NewLinkedList()
	singleList.AddFirst(42)
	fmt.Println("单个节点链表:", singleList)
	removed, err = singleList.RemoveLast()
	if err != nil {
		fmt.Printf("删除失败: %v\n", err)
	} else {
		fmt.Printf("删除后: %v, 链表: %s\n", removed, singleList)
	}
	fmt.Println()

	fmt.Println("=== 所有测试完成 ===")
}

