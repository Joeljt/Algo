import pytest

from leetcode.e283_move_zeros.solution import move_zeroes


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([0, 1, 0, 3, 12], [1, 3, 12, 0, 0]),
        ([0], [0]),
        ([0, 0, 1], [1, 0, 0]),
        ([1, 2, 3], [1, 2, 3]),
        ([0, 0, 0], [0, 0, 0]),
        ([1, 0, 2, 0, 3], [1, 2, 3, 0, 0]),
    ],
)
def test_move_zeroes(nums, expected):
    move_zeroes(nums)
    assert nums == expected
