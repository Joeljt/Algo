import pytest

from leetcode.m435_non_overlapping_intervals.solution import (
    erase_overlap_intervals,
)


@pytest.mark.parametrize(
    "intervals, expected",
    [
        ([[1, 2], [2, 3], [3, 4], [1, 3]], 1),
        ([[1, 2], [1, 2], [1, 2]], 2),
        ([[1, 2], [2, 3]], 0),
        ([[1, 100], [11, 22], [1, 11], [2, 12]], 2),
    ],
)
def test_erase_overlap_intervals(intervals, expected):
    assert erase_overlap_intervals(intervals) == expected
