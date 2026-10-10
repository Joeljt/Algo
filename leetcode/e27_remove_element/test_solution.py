import pytest

from leetcode.e27_remove_element.solution import remove_element


@pytest.mark.parametrize(
    "nums, val, expected",
    [
        ([3, 2, 2, 3], 3, [2, 2]),
        ([0, 1, 2, 2, 3, 0, 4, 2], 2, [0, 1, 3, 0, 4]),
        ([1, 2, 3, 4], 5, [1, 2, 3, 4]),
        ([2, 2, 2, 2], 2, []),
        ([], 1, []),
        ([1], 1, []),
        ([1], 2, [1]),
    ],
)
def test_remove_element(nums, val, expected):
    k = remove_element(nums, val)
    assert k == len(expected)
    assert sorted(nums[:k]) == sorted(expected)
