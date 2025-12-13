package main

import (
	"fmt"
	"joseph/algo/datastructure/stack"
)

// 栈的示例程序
func main() {
	fmt.Println("=== 栈的基本操作示例 ===")

	// 创建栈
	s := stack.New()
	fmt.Printf("初始栈: size=%d, capacity=%d\n", s.GetSize(), s.GetCapacity())
	fmt.Println("是否为空:", s.IsEmpty())
	fmt.Println()

	// 测试 Push - 入栈
	fmt.Println("=== 测试 Push（入栈） ===")
	for i := 0; i < 10; i++ {
		s.Push(i * 10)
		fmt.Printf("Push %d: size=%d, capacity=%d\n", i*10, s.GetSize(), s.GetCapacity())
	}
	fmt.Println()

	// 测试 Peek - 查看栈顶元素
	fmt.Println("=== 测试 Peek（查看栈顶） ===")
	top, err := s.Peek()
	if err != nil {
		fmt.Printf("Peek 失败: %v\n", err)
	} else {
		fmt.Printf("栈顶元素: %v, size=%d\n", top, s.GetSize())
	}
	fmt.Println()

	// 测试 Pop - 出栈
	fmt.Println("=== 测试 Pop（出栈） ===")
	for i := 0; i < 5; i++ {
		value, err := s.Pop()
		if err != nil {
			fmt.Printf("Pop 失败: %v\n", err)
		} else {
			fmt.Printf("Pop %v: size=%d, capacity=%d\n", value, s.GetSize(), s.GetCapacity())
		}
	}
	fmt.Println()

	// 测试扩缩容
	fmt.Println("=== 测试栈的自动扩缩容 ===")
	testResize()
	fmt.Println()

	// 实际应用示例：括号匹配
	fmt.Println("=== 实际应用：括号匹配 ===")
	testBracketMatching()
	fmt.Println()

	// 实际应用示例：表达式求值（简单版）
	fmt.Println("=== 实际应用：后缀表达式求值 ===")
	testPostfixEvaluation()
	fmt.Println()

	fmt.Println("=== 所有测试完成 ===")
}

// 测试栈的自动扩缩容
func testResize() {
	s := stack.New()
	initialCapacity := s.GetCapacity()
	fmt.Printf("初始容量: %d\n", initialCapacity)

	// 扩容测试
	fmt.Println("\n--- 扩容测试 ---")
	for i := 0; i < 25; i++ {
		s.Push(i)
		capacity := s.GetCapacity()
		// 记录容量变化的关键点
		if i == 0 || i == 4 || i == 8 || i == 16 || i == 24 {
			fmt.Printf("添加第 %d 个元素: size=%d, capacity=%d\n",
				i+1, s.GetSize(), capacity)
		}
		// 检测扩容
		if i > 0 {
			prevSize := s.GetSize() - 1
			if prevSize > 0 && capacity > initialCapacity {
				// 检查是否刚刚扩容（容量翻倍）
				if i == 4 || i == 8 || i == 16 {
					fmt.Printf("  -> 触发扩容！容量从 %d 增加到 %d\n",
						initialCapacity, capacity)
				}
			}
		}
	}
	expandedCapacity := s.GetCapacity()
	fmt.Printf("扩容后最终容量: %d\n", expandedCapacity)

	// 缩容测试
	fmt.Println("\n--- 缩容测试 ---")
	initialSize := s.GetSize()
	fmt.Printf("开始删除，当前: size=%d, capacity=%d\n", initialSize, s.GetCapacity())

	for i := 0; i < initialSize; i++ {
		// 在 Pop 之前记录容量，用于检测缩容
		capacityBefore := s.GetCapacity()

		_, err := s.Pop()
		if err != nil {
			fmt.Printf("Pop 失败: %v\n", err)
			break
		}

		sizeAfter := s.GetSize()
		capacityAfter := s.GetCapacity()

		// 检测缩容：如果容量减少了，说明触发了缩容
		if capacityAfter < capacityBefore {
			fmt.Printf("删除后: size=%d, capacity=%d -> 触发缩容！(从 %d 缩容到 %d)\n",
				sizeAfter, capacityAfter, capacityBefore, capacityAfter)
		} else if sizeAfter <= 5 || sizeAfter == initialSize/2 || i == 0 {
			// 记录关键点：前几次删除、中间点、最后几个元素
			fmt.Printf("删除后: size=%d, capacity=%d\n", sizeAfter, capacityAfter)
		}
	}

	finalCapacity := s.GetCapacity()
	fmt.Printf("缩容后最终容量: %d\n", finalCapacity)

	if finalCapacity < expandedCapacity {
		fmt.Printf("✓ 缩容成功：从 %d 缩容到 %d\n", expandedCapacity, finalCapacity)
	} else {
		fmt.Printf("注意：容量未完全缩回（可能因为最小容量限制）\n")
	}
}

// 实际应用：括号匹配
func testBracketMatching() {
	testCases := []struct {
		name   string
		input  string
		expect bool
	}{
		{"匹配的括号", "()", true},
		{"匹配的嵌套括号", "((()))", true},
		{"匹配的混合括号", "()[]{}", true},
		{"不匹配的括号", "([)]", false},
		{"缺少右括号", "(()", false},
		{"缺少左括号", "())", false},
		{"空字符串", "", true},
	}

	for _, tc := range testCases {
		result := isValidParentheses(tc.input)
		status := "✓"
		if result != tc.expect {
			status = "✗"
		}
		fmt.Printf("%s %s: \"%s\" -> %v (期望: %v)\n",
			status, tc.name, tc.input, result, tc.expect)
	}
}

// 使用栈检查括号是否匹配
func isValidParentheses(s string) bool {
	st := stack.New()

	for _, char := range s {
		if char == '(' || char == '[' || char == '{' {
			st.Push(char)
		} else if char == ')' || char == ']' || char == '}' {
			if st.IsEmpty() {
				return false
			}
			top, err := st.Pop()
			if err != nil {
				return false
			}
			// 检查是否匹配
			if (char == ')' && top != '(') ||
				(char == ']' && top != '[') ||
				(char == '}' && top != '{') {
				return false
			}
		}
	}

	return st.IsEmpty()
}

// 实际应用：后缀表达式求值（简单版，只支持整数和 + - * /）
func testPostfixEvaluation() {
	testCases := []struct {
		expression string
		expect     int
	}{
		{"3 4 +", 7},
		{"5 2 -", 3},
		{"3 4 *", 12},
		{"15 3 /", 5},
		{"3 4 + 2 *", 14},      // (3+4)*2
		{"3 4 2 * +", 11},      // 3+4*2
		{"10 2 3 * + 4 -", 12}, // 10+2*3-4
	}

	for _, tc := range testCases {
		result, err := evaluatePostfix(tc.expression)
		if err != nil {
			fmt.Printf("✗ 表达式 \"%s\" 求值失败: %v\n", tc.expression, err)
		} else {
			status := "✓"
			if result != tc.expect {
				status = "✗"
			}
			fmt.Printf("%s \"%s\" = %d (期望: %d)\n",
				status, tc.expression, result, tc.expect)
		}
	}
}

// 使用栈计算后缀表达式
func evaluatePostfix(expression string) (int, error) {
	st := stack.New()

	// 简单的解析（实际应该用更完善的解析器）
	// 这里假设表达式格式正确，数字和运算符用空格分隔
	var num int
	var isNum bool

	for _, char := range expression {
		if char >= '0' && char <= '9' {
			if isNum {
				num = num*10 + int(char-'0')
			} else {
				num = int(char - '0')
				isNum = true
			}
		} else if char == ' ' {
			if isNum {
				st.Push(num)
				isNum = false
				num = 0
			}
		} else {
			// 运算符
			if st.GetSize() < 2 {
				return 0, fmt.Errorf("表达式错误：操作数不足")
			}

			b, _ := st.Pop()
			a, _ := st.Pop()

			bVal := b.(int)
			aVal := a.(int)

			var result int
			switch char {
			case '+':
				result = aVal + bVal
			case '-':
				result = aVal - bVal
			case '*':
				result = aVal * bVal
			case '/':
				if bVal == 0 {
					return 0, fmt.Errorf("除零错误")
				}
				result = aVal / bVal
			default:
				return 0, fmt.Errorf("未知运算符: %c", char)
			}

			st.Push(result)
		}
	}

	if st.GetSize() != 1 {
		return 0, fmt.Errorf("表达式错误：结果不唯一")
	}

	result, err := st.Pop()
	if err != nil {
		return 0, err
	}

	return result.(int), nil
}
