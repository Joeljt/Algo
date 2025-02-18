package m260_single_number_iii;

public class Test {
    private static void test(Solution solution, int[] input, int[] expected) {
        int[] result = solution.singleNumber(input);
        assert (result[0] == expected[0] && result[1] == expected[1]) ||
                (result[0] == expected[1] && result[1] == expected[0])
                : String.format("Test failed: expected [%d,%d] or [%d,%d], got [%d,%d]",
                        expected[0], expected[1], expected[1], expected[0], result[0], result[1]);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        test(solution, new int[] { 1, 2, 1, 3, 2, 5 }, new int[] { 3, 5 });
        test(solution, new int[] { -1, 0 }, new int[] { -1, 0 });
        test(solution, new int[] { 1, 1, 2, 3, 2, 4 }, new int[] { 3, 4 });

        System.out.println("[PASS] " + Test.class.getPackage().getName());
    }
}