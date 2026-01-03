package utils

import (
	"reflect"
	"testing"
)

func TestSwap(t *testing.T) {
	tests := []struct {
		name     string
		slice    []int
		i        int
		j        int
		expected []int
	}{
		{
			name:     "Normal swap",
			slice:    []int{1, 2, 3, 4, 5},
			i:        0,
			j:        4,
			expected: []int{5, 2, 3, 4, 1},
		},
		{
			name:     "Swap adjacent",
			slice:    []int{1, 2, 3},
			i:        0,
			j:        1,
			expected: []int{2, 1, 3},
		},
		{
			name:     "Swap same index",
			slice:    []int{1, 2, 3},
			i:        1,
			j:        1,
			expected: []int{1, 2, 3},
		},
		{
			name:     "Out of range i",
			slice:    []int{1, 2, 3},
			i:        -1,
			j:        1,
			expected: []int{1, 2, 3},
		},
		{
			name:     "Out of range j",
			slice:    []int{1, 2, 3},
			i:        1,
			j:        10,
			expected: []int{1, 2, 3},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			slice := make([]int, len(tt.slice))
			copy(slice, tt.slice)
			Swap(slice, tt.i, tt.j)
			if !reflect.DeepEqual(slice, tt.expected) {
				t.Errorf("Swap() = %v, want %v", slice, tt.expected)
			}
		})
	}
}

func TestMax(t *testing.T) {
	tests := []struct {
		name     string
		a        int
		b        int
		expected int
	}{
		{"a > b", 5, 3, 5},
		{"a < b", 3, 5, 5},
		{"a == b", 5, 5, 5},
		{"negative", -1, -5, -1},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Max(tt.a, tt.b); got != tt.expected {
				t.Errorf("Max() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestMin(t *testing.T) {
	tests := []struct {
		name     string
		a        int
		b        int
		expected int
	}{
		{"a > b", 5, 3, 3},
		{"a < b", 3, 5, 3},
		{"a == b", 5, 5, 5},
		{"negative", -1, -5, -5},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Min(tt.a, tt.b); got != tt.expected {
				t.Errorf("Min() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestMaxOf(t *testing.T) {
	tests := []struct {
		name     string
		nums     []int
		expected int
	}{
		{"normal", []int{1, 5, 3, 9, 2}, 9},
		{"single", []int{5}, 5},
		{"empty", []int{}, 0},
		{"negative", []int{-1, -5, -3}, -1},
		{"mixed", []int{-1, 0, 5, -3}, 5},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := MaxOf(tt.nums); got != tt.expected {
				t.Errorf("MaxOf() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestMinOf(t *testing.T) {
	tests := []struct {
		name     string
		nums     []int
		expected int
	}{
		{"normal", []int{1, 5, 3, 9, 2}, 1},
		{"single", []int{5}, 5},
		{"empty", []int{}, 0},
		{"negative", []int{-1, -5, -3}, -5},
		{"mixed", []int{-1, 0, 5, -3}, -3},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := MinOf(tt.nums); got != tt.expected {
				t.Errorf("MinOf() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestReverse(t *testing.T) {
	tests := []struct {
		name     string
		slice    []int
		expected []int
	}{
		{"normal", []int{1, 2, 3, 4, 5}, []int{5, 4, 3, 2, 1}},
		{"even length", []int{1, 2, 3, 4}, []int{4, 3, 2, 1}},
		{"single", []int{1}, []int{1}},
		{"empty", []int{}, []int{}},
		{"two elements", []int{1, 2}, []int{2, 1}},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			slice := make([]int, len(tt.slice))
			copy(slice, tt.slice)
			Reverse(slice)
			if !reflect.DeepEqual(slice, tt.expected) {
				t.Errorf("Reverse() = %v, want %v", slice, tt.expected)
			}
		})
	}
}

func TestReverseRange(t *testing.T) {
	tests := []struct {
		name     string
		slice    []int
		start    int
		end      int
		expected []int
	}{
		{"normal", []int{1, 2, 3, 4, 5}, 1, 4, []int{1, 4, 3, 2, 5}},
		{"full range", []int{1, 2, 3}, 0, 3, []int{3, 2, 1}},
		{"invalid start", []int{1, 2, 3}, -1, 2, []int{1, 2, 3}},
		{"invalid end", []int{1, 2, 3}, 0, 10, []int{1, 2, 3}},
		{"start >= end", []int{1, 2, 3}, 2, 1, []int{1, 2, 3}},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			slice := make([]int, len(tt.slice))
			copy(slice, tt.slice)
			ReverseRange(slice, tt.start, tt.end)
			if !reflect.DeepEqual(slice, tt.expected) {
				t.Errorf("ReverseRange() = %v, want %v", slice, tt.expected)
			}
		})
	}
}

func TestIndexOf(t *testing.T) {
	tests := []struct {
		name     string
		slice    []int
		target   int
		expected int
	}{
		{"found", []int{1, 2, 3, 4, 5}, 3, 2},
		{"not found", []int{1, 2, 3, 4, 5}, 6, -1},
		{"first", []int{1, 2, 3}, 1, 0},
		{"last", []int{1, 2, 3}, 3, 2},
		{"duplicate", []int{1, 2, 2, 3}, 2, 1},
		{"empty", []int{}, 1, -1},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := IndexOf(tt.slice, tt.target); got != tt.expected {
				t.Errorf("IndexOf() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestLastIndexOf(t *testing.T) {
	tests := []struct {
		name     string
		slice    []int
		target   int
		expected int
	}{
		{"found", []int{1, 2, 3, 4, 5}, 3, 2},
		{"not found", []int{1, 2, 3, 4, 5}, 6, -1},
		{"first", []int{1, 2, 3}, 1, 0},
		{"last", []int{1, 2, 3}, 3, 2},
		{"duplicate", []int{1, 2, 2, 3}, 2, 2},
		{"empty", []int{}, 1, -1},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := LastIndexOf(tt.slice, tt.target); got != tt.expected {
				t.Errorf("LastIndexOf() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestEqual(t *testing.T) {
	tests := []struct {
		name     string
		a        []int
		b        []int
		expected bool
	}{
		{"equal", []int{1, 2, 3}, []int{1, 2, 3}, true},
		{"different length", []int{1, 2, 3}, []int{1, 2}, false},
		{"different elements", []int{1, 2, 3}, []int{1, 2, 4}, false},
		{"both empty", []int{}, []int{}, true},
		{"one empty", []int{1, 2, 3}, []int{}, false},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Equal(tt.a, tt.b); got != tt.expected {
				t.Errorf("Equal() = %v, want %v", got, tt.expected)
			}
		})
	}
}

func TestCopy(t *testing.T) {
	original := []int{1, 2, 3, 4, 5}
	copied := Copy(original)

	// 修改原切片，验证拷贝是独立的
	original[0] = 999

	if copied[0] == 999 {
		t.Error("Copy() should create an independent copy")
	}

	if !Equal(copied, []int{1, 2, 3, 4, 5}) {
		t.Errorf("Copy() = %v, want %v", copied, []int{1, 2, 3, 4, 5})
	}
}
