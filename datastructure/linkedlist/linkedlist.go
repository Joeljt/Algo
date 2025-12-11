package linkedlist

import (
	"errors"
	"fmt"
)

// 定义链表节点
// value 存储数据，next 指向下一节点
type Node struct {
	Value any
	Next  *Node // 指向下一节点的指针
}

// 定义单链表
type LinkedList struct {
	Head *Node
	Size int
}

// new()
func NewLinkedList() *LinkedList {
	return &LinkedList{
		Head: nil,
		Size: 0,
	}
}

// Size()
func (ll *LinkedList) GetSize() int {
	return ll.Size
}

// IsEmpty()
func (ll *LinkedList) IsEmpty() bool {
	return ll.Head == nil || ll.Size == 0
}

// AddFirst()
func (ll *LinkedList) AddFirst(value any) {
	// 创建新节点，并指向原来的头节点 -- addFirst
	newNode := &Node{
		Value: value,
		Next:  ll.Head,
	}
	// 更新链表的头节点为当前插入的新节点
	ll.Head = newNode
	// 维护元素数量
	ll.Size++
}

// AddLast()
func (ll *LinkedList) AddLast(value any) {
	// 如果链表为空，直接调用AddFirst()
	if ll.IsEmpty() {
		ll.AddFirst(value)
		return
	}
	// 创建新节点，遍历找到尾节点后插入
	newNode := &Node{
		Value: value,
		Next:  nil,
	}
	cur := ll.Head
	for cur.Next != nil {
		cur = cur.Next
	}
	cur.Next = newNode
	ll.Size++
}

// AddAt()
func (ll *LinkedList) AddAt(index int, value any) error {
	// 检查索引是否合法
	if index < 0 || index > ll.Size {
		return errors.New("index out of range")
	}
	// 如果索引为0，直接调用AddFirst()
	if index == 0 {
		ll.AddFirst(value)
		return nil
	}
	// 如果索引为链表长度，直接调用AddLast()
	if index == ll.Size {
		ll.AddLast(value)
		return nil
	}
	// 创建新节点，遍历找到插入位置前一个节点后插入
	newNode := &Node{
		Value: value,
		Next:  nil,
	}
	cur := ll.Head
	for i := 0; i < index-1; i++ {
		cur = cur.Next
	}
	newNode.Next = cur.Next
	cur.Next = newNode
	ll.Size++
	return nil
}

// RemoveFirst()
func (ll *LinkedList) RemoveFirst() (any, error) {
	if ll.IsEmpty() {
		return nil, errors.New("linked list is empty")
	}
	// 删除头节点
	remove := ll.Head
	// 将链表头跳过删除的节点，指向删除节点的下一个节点
	ll.Head = remove.Next
	// 断开与删除节点的连接并回收内存
	remove.Next = nil
	// 维护元素数量
	ll.Size--
	// 返回删除节点的值
	return remove.Value, nil
}

// RemoveLast()
func (ll *LinkedList) RemoveLast() (any, error) {
	if ll.IsEmpty() {
		return nil, errors.New("linked list is empty")
	}
	// 只有一个元素的时候复用 RemoveFirst
	if ll.Size == 1 {
		return ll.RemoveFirst()
	}
	// 遍历找到倒数第二个节点
	// 可以直接使用 cur.Next.Next 而不用担心空指针是因为上面有判断，走到这里至少有两个元素
	cur := ll.Head
	for cur.Next.Next != nil {
		cur = cur.Next
	}
	// 给倒数第二个节点的 next 赋值为 nil，删除该节点
	last := cur.Next
	last.Next = nil
	// 维护元素数量
	ll.Size--
	return last.Value, nil
}

// RemoveAt()
func (ll *LinkedList) RemoveAt(index int) (any, error) {
	// 合法性验证
	if index < 0 || index >= ll.Size {
		return nil, errors.New("index out of range")
	}

	// 非空判断
	if ll.IsEmpty() {
		return nil, errors.New("linked list is empty")
	}

	// 删除头指针
	if index == 0 {
		return ll.RemoveFirst()
	}

	// 删除尾指针
	if index == ll.Size-1 {
		return ll.RemoveLast()
	}

	// 找到 index 的前一个位置
	cur := ll.Head
	for i := 0; i < index-1; i++ {
		cur = cur.Next
	}
	// 跳过 index，直接连上下一个节点
	remove := cur.Next
	cur.Next = remove.Next
	// 断开删除节点的指向
	remove.Next = nil
	// 更新元素
	ll.Size--
	return remove.Value, nil
}

// Get()
func (ll *LinkedList) Get(index int) (any, error) {
	// 合法性验证
	if index < 0 || index >= ll.Size {
		return nil, errors.New("index out of range")
	}

	// 从头节点开始遍历到 index 就找到了目标节点
	cur := ll.Head
	for i := 0; i < index; i++ {
		cur = cur.Next
	}

	return cur.Value, nil
}

// IndexOf
func (ll *LinkedList) IndexOf(value any) int {
	// 非空判断
	if ll.IsEmpty() {
		return -1
	}
	cur := ll.Head
	for i := 0; i < ll.Size; i++ {
		if cur.Value == value {
			return i
		}
		cur = cur.Next
	}
	return -1
}

// Contains
func (ll *LinkedList) Contains(value any) bool {
	return ll.IndexOf(value) != -1
}

// Clear
func (ll *LinkedList) Clear() {
	ll.Head = nil // 直接设置为 nil 即可，gc 会自动回收
	ll.Size = 0
}

// ToSlice
func (ll *LinkedList) ToSlice() []any {
	// 创建一个长度为 n 的切片，初始值都是 nil
	result := make([]any, ll.Size)

	cur := ll.Head
	for i := 0; i < ll.Size; i++ {
		// 直接下标赋值即可
		result[i] = cur.Value
		cur = cur.Next
	}

	return result
}

// String
func (ll *LinkedList) String() string {
	if ll.IsEmpty() {
		return "LinkedList{size: 0, values: []}"
	}

	result := ""
	cur := ll.Head
	for cur != nil {
		if result != "" {
			result += "->"
		}
		result += fmt.Sprintf("%v", cur.Value)
		cur = cur.Next
	}

	return fmt.Sprintf("LinkedList{size: %d, values: [%s]}", ll.Size, result)
}
