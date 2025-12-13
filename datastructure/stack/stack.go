package stack

import (
	"errors"
	"joseph/algo/datastructure/array"
)

type Stack struct {
	data *array.Array
	size int
}

func New() *Stack {
	return &Stack{
		data: array.New(10),
		size: 0,
	}
}

func (s *Stack) Push(value any) {
	s.data.Add(value)
	s.size++
}

func (s *Stack) Pop() (any, error) {
	if s.size == 0 {
		return nil, errors.New("stack is empty")
	}
	// 使用 RemoveLast 更简洁，并且会触发自动缩容
	value, err := s.data.RemoveLast()
	if err != nil {
		return nil, err
	}
	s.size--
	return value, nil
}

func (s *Stack) Peek() (any, error) {
	if s.size == 0 {
		return nil, errors.New("stack is empty")
	}
	value, err := s.data.Get(s.size - 1)
	if err != nil {
		return nil, err
	}
	return value, nil
}

func (s *Stack) IsEmpty() bool {
	return s.size == 0
}

func (s *Stack) GetSize() int {
	return s.size
}

// GetCapacity 返回栈的容量（用于测试扩缩容）
func (s *Stack) GetCapacity() int {
	return s.data.Capacity()
}
