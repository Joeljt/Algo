package main

import "fmt"

// 示例使用
func main() {
	// 创建动态数组
	arr := NewArray(5)
	fmt.Println("初始数组:", arr)

	// 添加元素
	for i := 0; i < 15; i++ {
		arr.Add(i * 10)
		fmt.Printf("添加 %d, 大小: %d, 容量: %d\n", i*10, arr.Size(), arr.Capacity())
	}

	fmt.Println("添加后数组:", arr)

	// 插入元素
	arr.Insert(5, 999)
	fmt.Println("在索引5插入999后:", arr)

	// 获取元素
	element, _ := arr.Get(5)
	fmt.Println("索引5的元素:", element)

	// 删除元素
	removed, _ := arr.Remove(3)
	fmt.Printf("删除索引3的元素: %v, 删除后数组: %s\n", removed, arr)

	// 批量删除测试缩容
	for i := 0; i < 10; i++ {
		arr.RemoveLast()
		fmt.Printf("删除后 大小: %d, 容量: %d\n", arr.Size(), arr.Capacity())
	}

	// 测试包含和索引
	fmt.Println("是否包含50:", arr.Contains(50))
	fmt.Println("50的索引:", arr.IndexOf(50))

	// 清空数组
	arr.Clear()
	fmt.Println("清空后:", arr)
}
