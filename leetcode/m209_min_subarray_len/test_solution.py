import pytest

from leetcode.m209_min_subarray_len.solution import min_subarray_len


@pytest.mark.parametrize(
    "target, nums, expected",
    [
        (7, [2, 3, 1, 2, 4, 3], 2),
        (4, [1, 4, 4], 1),
        (11, [1, 1, 1, 1, 1, 1, 1, 1], 0),
        (15, [1, 2, 3, 4, 5], 5),
    ],
)
def test_min_subarray_len(target, nums, expected):
    assert min_subarray_len(target, nums) == expected
