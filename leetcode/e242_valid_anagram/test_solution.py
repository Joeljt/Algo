import pytest

from leetcode.e242_valid_anagram.solution import is_anagram


@pytest.mark.parametrize(
    "s, t, expected",
    [
        ("anagram", "nagaram", True),
        ("rat", "car", False),
        ("a", "a", True),
        ("ab", "a", False),
    ],
)
def test_is_anagram(s, t, expected):
    assert is_anagram(s, t) == expected
