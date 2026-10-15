import pytest

from leetcode.e1_two_sum.solution import two_sum


@pytest.mark.parametrize(
    "nums, target, expected",
    [
        ([2, 7, 11, 15], 9, [0, 1]),
        ([3, 2, 4], 6, [1, 2]),
        ([3, 3], 6, [0, 1]),
    ],
)
def test_two_sum(nums, target, expected):
    got = two_sum(nums, target)
    assert sorted(got) == sorted(expected)
    assert got[0] != got[1]
    assert nums[got[0]] + nums[got[1]] == target
