import pytest

from leetcode.m15_3sum.solution import three_sum


def _normalize(triplets: list) -> list:
    return sorted(sorted(t) for t in triplets)


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([-1, 0, 1, 2, -1, -4], [[-1, -1, 2], [-1, 0, 1]]),
        ([0, 1, 1], []),
        ([0, 0, 0], [[0, 0, 0]]),
    ],
)
def test_three_sum(nums, expected):
    assert _normalize(three_sum(nums)) == _normalize(expected)
