from leetcode.m155_min_stack.solution import MinStack


def test_min_stack_example():
    st = MinStack()
    st.push(-2)
    st.push(0)
    st.push(-3)
    assert st.get_min() == -3
    st.pop()
    assert st.top() == 0
    assert st.get_min() == -2


def test_min_stack_single():
    st = MinStack()
    st.push(5)
    assert st.top() == 5
    assert st.get_min() == 5
