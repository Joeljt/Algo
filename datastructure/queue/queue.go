package queue

import "errors"

type Queue struct {
	data     []any
	front    int
	rear     int
	size     int
	capacity int
}

func New() *Queue {
	return &Queue{
		data:     make([]any, 10),
		front:    0,
		rear:     0,
		size:     0,
		capacity: 10,
	}
}

// IsEmpty 首尾指针重叠
func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

// IsFull
// 队列初始状态下，首尾指针都指向队首，插入一条数据以后，尾指针向后移动，首指针不动，相当于首指针始终指向队首元素，而尾指针始终指向队尾元素的下一个元素。
// 在这种情况下，如果队尾指针指向的元素已经是队列中最后一个空位，就说明一旦插入当前元素到这个位置，那队首指针和队尾指针就会再次重叠，与队列为空的情况相同，就需要额外引入一个 size 字段用来区分队列为空或者队列为满。
// 所以这里有两种方式实现：
//  1. size == capacity，最直观，当前总数与容量相同，说明队列已满；
//  2. 或者主动浪费一个空间，但是可以放弃 size 字段的维护，完全依赖 front 和 rear 的相对位置来实现；
//     front < rear 时，说明队列顺序正常，没有开启循环状态，队列元素个数为：rear - front
//     front > rear 时，说明尾指针转了一圈回到了数组头部，处于循环状态，这时候队列元素个数为：(size - front) + rear
//     即末尾元素+开头的元素，或者可以理解成数组中间部分是空的，首尾都有数据，把中间的数据减掉就是元素数量，即 size - (front - rear)
//     所以判断条件为：(rear+1)%capacity == front
func (q *Queue) IsFull() bool {
	return q.size == q.capacity
}

func (q *Queue) Enqueue(value any) error {
	if q.IsFull() {
		return errors.New("queue is full")
	}
	// 当前 rear 指向空白位置，直接在对应位置赋值即可
	q.data[q.rear] = value
	// 向后移动 rear 的时候需要对容量取模，保证超出末尾角标的时候能转回去
	q.rear = (q.rear + 1) % q.capacity
	// 更新 size
	q.size++
	return nil
}

// 出队
func (q *Queue) Dequeue() (any, error) {
	if q.IsEmpty() {
		return nil, errors.New("empty queue")
	}
	// 取出来队首的元素
	value := q.data[q.front]
	// 维护队首指针
	q.front = (q.front + 1) % q.capacity
	// 维护 size
	q.size--
	return value, nil
}

// Peek 直接返回队首元素即可，不需要更新状态
func (q *Queue) Peek() (any, error) {
	if q.IsEmpty() {
		return nil, errors.New("empty queue")
	}
	return q.data[q.front], nil
}

func (q *Queue) GetSize() int {
	return q.size
}

func (q *Queue) GetCapacity() int {
	return q.capacity
}

func (q *Queue) Clear() {
	q.front = 0
	q.rear = 0
	q.size = 0
	// 清空数据，帮助 gc
	for i := range q.data {
		q.data[i] = nil
	}
}
