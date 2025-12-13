package array

import (
	"errors"
	"fmt"
)

// Array 动态数组结构体
type Array struct {
	data     []interface{} // 存储数据的切片
	size     int           // 当前元素数量
	capacity int           // 当前容量
}

// NewArray 创建新的动态数组
func New(initialCapacity int) *Array {
	if initialCapacity <= 0 {
		initialCapacity = 10 // 默认初始容量
	}
	return &Array{
		data:     make([]interface{}, initialCapacity),
		size:     0,
		capacity: initialCapacity,
	}
}

// Size 返回当前元素数量
func (da *Array) Size() int {
	return da.size
}

// Capacity 返回当前容量
func (da *Array) Capacity() int {
	return da.capacity
}

// IsEmpty 判断数组是否为空
func (da *Array) IsEmpty() bool {
	return da.size == 0
}

// Get 获取指定位置的元素
func (da *Array) Get(index int) (interface{}, error) {
	if index < 0 || index >= da.size {
		return nil, errors.New("index out of range")
	}
	return da.data[index], nil
}

// Set 设置指定位置的元素
func (da *Array) Set(index int, element interface{}) error {
	if index < 0 || index >= da.size {
		return errors.New("index out of range")
	}
	da.data[index] = element
	return nil
}

// Add 添加元素到数组末尾
func (da *Array) Add(element interface{}) {
	// 检查是否需要扩容
	if da.size == da.capacity {
		da.resize(da.capacity * 2)
	}
	da.data[da.size] = element
	da.size++
}

// Insert 在指定位置插入元素
func (da *Array) Insert(index int, element interface{}) error {
	if index < 0 || index > da.size {
		return errors.New("index out of range")
	}

	// 检查是否需要扩容
	if da.size == da.capacity {
		da.resize(da.capacity * 2)
	}

	// 将插入位置后的元素向后移动
	for i := da.size; i > index; i-- {
		da.data[i] = da.data[i-1]
	}

	da.data[index] = element
	da.size++
	return nil
}

// Remove 删除指定位置的元素
func (da *Array) Remove(index int) (interface{}, error) {
	if index < 0 || index >= da.size {
		return nil, errors.New("index out of range")
	}

	removedElement := da.data[index]

	// 将删除位置后的元素向前移动
	for i := index; i < da.size-1; i++ {
		da.data[i] = da.data[i+1]
	}

	da.size--
	da.data[da.size] = nil // 帮助垃圾回收

	// 检查是否需要缩容（当元素数量小于容量的1/4时）
	if da.size > 0 && da.size == da.capacity/4 {
		da.resize(da.capacity / 2)
	}

	return removedElement, nil
}

// RemoveLast 删除最后一个元素
func (da *Array) RemoveLast() (interface{}, error) {
	return da.Remove(da.size - 1)
}

// Contains 检查是否包含某个元素
func (da *Array) Contains(element interface{}) bool {
	for i := 0; i < da.size; i++ {
		if da.data[i] == element {
			return true
		}
	}
	return false
}

// IndexOf 返回元素的第一个索引，不存在则返回-1
func (da *Array) IndexOf(element interface{}) int {
	for i := 0; i < da.size; i++ {
		if da.data[i] == element {
			return i
		}
	}
	return -1
}

// Clear 清空数组
func (da *Array) Clear() {
	for i := 0; i < da.size; i++ {
		da.data[i] = nil
	}
	da.size = 0
	// 可以选择缩容到初始大小
	if da.capacity > 10 {
		da.resize(10)
	}
}

// resize 调整数组容量
func (da *Array) resize(newCapacity int) {
	if newCapacity < 10 { // 最小容量限制
		newCapacity = 10
	}

	newData := make([]interface{}, newCapacity)
	copy(newData, da.data[:da.size])
	da.data = newData
	da.capacity = newCapacity
}

// ToSlice 转换为切片
func (da *Array) ToSlice() []interface{} {
	result := make([]interface{}, da.size)
	copy(result, da.data[:da.size])
	return result
}

// String 实现Stringer接口
func (da *Array) String() string {
	return fmt.Sprintf("Array{size: %d, capacity: %d, data: %v}",
		da.size, da.capacity, da.data[:da.size])
}
