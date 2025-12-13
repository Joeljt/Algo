package list

import (
	"errors"
	"fmt"
)

// 定义链表节点
type Node struct {
	Value any
	Prev  *Node // 指向上一节点的指针
	Next  *Node // 指向下一节点的指针
}

type List struct {
	Dummy *Node // 虚拟头节点
	Size  int   // 链表大小
}

func New() *List {
	return &List{
		Dummy: &Node{
			Value: any(nil),
			Prev:  nil,
			Next:  nil,
		},
		Size: 0,
	}
}

func (l *List) GetSize() int {
	return l.Size
}

func (l *List) IsEmpty() bool {
	return l.Size == 0
}

// 在指定位置插入节点
func (l *List) AddAt(index int, value any) error {
	// 检查索引
	if index < 0 || index > l.Size {
		return errors.New("index out of range")
	}

	// 创建要插入的新节点
	node := &Node{}
	node.Value = value

	// 找到目前位置的前一个节点
	// dummy 节点天然作为头节点的前一个节点
	prev := l.Dummy
	for i := 0; i < index; i++ {
		prev = prev.Next
	}

	// 找到前一个节点以后，先将目标节点存起来备用，即 prev.Next
	next := prev.Next

	// 将新节点插入到 prev 和 next 之间，并维护好新节点的指向关系
	node.Prev = prev
	node.Next = next

	// 然后更新 prev 的 next 指向新节点
	prev.Next = node

	// 最后更新 next 的 prev 指向新节点，但是 next 有可能是尾节点，需要判空
	if next != nil {
		next.Prev = node
	}

	// 如果 next 为空，说明这是新添加的尾节点
	// 更新 dummy 的 prev 指向新节点，让整个链表形成一个闭环，方便后续的遍历操作
	if next == nil {
		l.Dummy.Prev = node
	}

	// 维护链表大小
	l.Size++

	return nil
}

// 添加头节点
func (l *List) AddFirst(value any) {
	l.AddAt(0, value)
}

// 添加尾节点
func (l *List) AddLast(value any) {
	l.AddAt(l.Size, value)
}

// 删除指定位置的节点
func (l *List) RemoveAt(index int) (any, error) {
	if index < 0 || index >= l.Size {
		return nil, errors.New("index out of range")
	}

	// 同样从 dummy 节点开始，向后找到待删除节点的前一个节点
	prev := l.Dummy
	for i := 0; i < index; i++ {
		prev = prev.Next
	}

	// 先把要删掉的节点取出来备用（注意这里 prev 永远不会为空）
	target := prev.Next

	// 获取要删除的节点的值
	value := target.Value

	// 让要删除的节点的前后节点相连，跳过该节点
	prev.Next = target.Next
	// 下一个节点也需要更新自己的前驱节点，跳过被删除的节点，指向 prev 节点，但是下一个节点有可能是尾节点，需要判空
	if target.Next != nil {
		target.Next.Prev = prev
	}

	// 如果 target.Next 为空，说明这是要删除的尾节点
	// 更新 dummy 的 prev 指向 prev 节点，让整个链表形成一个闭环，方便后续的遍历操作
	if target.Next == nil {
		if l.Size == 1 {
			l.Dummy.Prev = nil // 删除后链表为空
		} else {
			l.Dummy.Prev = prev // prev 是新的最后一个节点
		}
	}

	// 断开被删除节点的指向，帮助 GC 回收
	target.Prev = nil
	target.Next = nil

	// 维护链表大小
	l.Size--

	// 返回删除节点的值
	return value, nil
}

// 删除头节点
func (l *List) RemoveFirst() (any, error) {
	if l.IsEmpty() {
		return nil, errors.New("list is empty")
	}
	return l.RemoveAt(0)
}

// 删除尾节点
func (l *List) RemoveLast() (any, error) {
	if l.IsEmpty() {
		return nil, errors.New("list is empty")
	}
	return l.RemoveAt(l.Size - 1)
}

// 获取指定位置的节点
func (l *List) Get(index int) (any, error) {
	if index < 0 || index >= l.Size {
		return nil, errors.New("index out of range")
	}

	// dummy 节点天然作为头节点的前一个节点，所以从 dummy.Next 开始遍历
	// 如果这里是从 dummy 开始遍历，那实际上就多判断了一个节点，index 实际上会比 size 多 1
	cur := l.Dummy.Next
	for i := 0; i < index; i++ {
		cur = cur.Next
	}

	// 因为我们从 dummy.Next 开始遍历，所以 cur 最远也只能指向最后一个节点
	// 所以这里我们可以放心地直接访问 value 而不必担心越界问题
	return cur.Value, nil
}

// 设置指定位置的节点
func (l *List) Set(index int, value any) error {
	// 检查索引
	if index < 0 || index >= l.Size {
		return errors.New("index out of range")
	}

	// 利用双链表的性质，可以根据 index 与 list.Size 的大小，确定目标位置
	// 这样在链表很长的时候，可以减少遍历次数，提高效率

	var cur *Node = nil

	// 目标在链表前半部分，从前向后找
	if index < l.Size/2 {
		cur = l.Dummy.Next
		for i := 0; i < index; i++ {
			cur = cur.Next
		}
	} else {
		// 目标在链表后半部分，从后向前找
		cur = l.Dummy.Prev
		for i := l.Size - 1; i > index; i-- {
			cur = cur.Prev
		}
	}

	cur.Value = value
	return nil
}

// 清空链表
func (l *List) Clear() {
	l.Dummy.Next = nil
	l.Dummy.Prev = nil
	l.Size = 0
}

// 转换为切片
func (l *List) ToSlice() []any {
	result := make([]any, l.Size)
	cur := l.Dummy.Next
	for i := 0; i < l.Size; i++ {
		result[i] = cur.Value
		cur = cur.Next
	}
	return result
}

// 实现 String 方法
func (l *List) String() string {
	if l.IsEmpty() {
		return "List{size: 0, values: []}"
	}

	// 从 dummy.Next 开始遍历，因为 dummy 节点本身不存储数据
	result := ""
	cur := l.Dummy.Next
	for i := 0; i < l.Size; i++ {
		if result != "" {
			result += "->"
		}
		result += fmt.Sprintf("%v", cur.Value)
		cur = cur.Next
	}

	return fmt.Sprintf("List{size: %d, values: [%s]}", l.Size, result)
}
