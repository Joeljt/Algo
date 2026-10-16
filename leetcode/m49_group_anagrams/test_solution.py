import pytest

from leetcode.m49_group_anagrams.solution import group_anagrams


def _normalize(groups: list) -> list:
    return sorted(sorted(g) for g in groups)


@pytest.mark.parametrize(
    "strs, expected",
    [
        (
            ["eat", "tea", "tan", "ate", "nat", "bat"],
            [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]],
        ),
        ([""], [[""]]),
        (["a"], [["a"]]),
    ],
)
def test_group_anagrams(strs, expected):
    assert _normalize(group_anagrams(strs)) == _normalize(expected)
