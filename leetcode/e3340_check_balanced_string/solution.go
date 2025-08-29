package main

func isBalanced(s string) bool {
	odd := 0
	even := 0
	for i := 0; i < len(s); i++ {
		if i%2 == 0 {
			even += int(s[i] - '0')
		} else {
			odd += int(s[i] - '0')
		}
	}
	return odd == even
}
