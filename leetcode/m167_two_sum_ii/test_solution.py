import pytest

from leetcode.m167_two_sum_ii.solution import two_sum


@pytest.mark.parametrize(
    "numbers, target, expected",
    [
        ([2, 7, 11, 15], 9, [1, 2]),
        ([2, 3, 4], 6, [1, 3]),
        ([-1, 0], -1, [1, 2]),
    ],
)
def test_two_sum(numbers, target, expected):
    assert two_sum(numbers, target) == expected
