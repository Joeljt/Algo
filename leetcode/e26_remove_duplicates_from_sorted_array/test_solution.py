import pytest

from leetcode.e26_remove_duplicates_from_sorted_array.solution import remove_duplicates


@pytest.mark.parametrize(
    "nums, expected_k, expected_prefix",
    [
        ([1, 1, 2], 2, [1, 2]),
        ([0, 0, 1, 1, 1, 2, 2, 3, 3, 4], 5, [0, 1, 2, 3, 4]),
        ([1], 1, [1]),
        ([], 0, []),
    ],
)
def test_remove_duplicates(nums, expected_k, expected_prefix):
    k = remove_duplicates(nums)
    assert k == expected_k
    assert nums[:k] == expected_prefix
