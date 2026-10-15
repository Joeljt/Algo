import pytest

from leetcode.m11_container_with_most_water.solution import max_area


@pytest.mark.parametrize(
    "height, expected",
    [
        ([1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
        ([1, 1], 1),
        ([4, 3, 2, 1, 4], 16),
    ],
)
def test_max_area(height, expected):
    assert max_area(height) == expected
