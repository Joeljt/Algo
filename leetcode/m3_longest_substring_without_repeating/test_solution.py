import pytest

from leetcode.m3_longest_substring_without_repeating.solution import length_of_longest_substring


@pytest.mark.parametrize(
    "s, expected",
    [
        ("abcabcbb", 3),
        ("bbbbb", 1),
        ("pwwkew", 3),
        ("", 0),
        (" ", 1),
    ],
)
def test_length_of_longest_substring(s, expected):
    assert length_of_longest_substring(s) == expected
