import pytest

from leetcode.e217_contains_duplicate.solution import contains_duplicate


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([1, 2, 3, 1], True),
        ([1, 2, 3, 4], False),
        ([1, 1, 1, 3, 3, 4, 3, 2, 4, 2], True),
        ([], False),
    ],
)
def test_contains_duplicate(nums, expected):
    assert contains_duplicate(nums) == expected
