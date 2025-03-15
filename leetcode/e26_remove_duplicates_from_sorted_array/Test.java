package e26_remove_duplicates_from_sorted_array;

public class Test {
    private static void test(Solution solution) {
        int[] nums = {1, 1, 2};
        int[] expected = {1, 2};
        int result = solution.removeDuplicates(nums);
        assert result == expected.length : "failed";
        for (int i = 0; i < result; i++) {
            assert nums[i] == expected[i] : "failed";
        }
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        test(solution);

        System.out.println("[PASS] " + Test.class.getPackage().getName());
    }
}
