import pytest

from leetcode.e643_max_average_subarray_i.solution import find_max_average


@pytest.mark.parametrize(
    "nums, k, expected",
    [
        ([1, 12, -5, -6, 50, 3], 4, 12.75),
        ([5], 1, 5.0),
        ([0, 1, 1, 3, 2], 3, 2.0),
    ],
)
def test_find_max_average(nums, k, expected):
    assert find_max_average(nums, k) == pytest.approx(expected)
