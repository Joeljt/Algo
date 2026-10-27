import pytest

from leetcode.m128_longest_consecutive_sequence.solution import (
    longest_consecutive,
)


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([100, 4, 200, 1, 3, 2], 4),
        ([0, 3, 7, 2, 5, 8, 4, 6, 0, 1], 9),
        ([1, 2, 0, 1], 3),
        ([1], 1),
        ([0, 0], 1),
        ([1, 100], 1),
        ([], 0),
    ],
)
def test_longest_consecutive(nums, expected):
    assert longest_consecutive(nums) == expected
