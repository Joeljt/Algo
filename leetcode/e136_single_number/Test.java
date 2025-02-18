package e136_single_number;

public class Test {
    private static void test(Solution solution, int[] input, int expected) {
        int result = solution.singleNumber(input);
        assert result == expected : String.format("Test failed: expected %d, got %d", expected, result);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        test(solution, new int[] { 2, 2, 1 }, 1);
        test(solution, new int[] { 4, 1, 2, 1, 2 }, 4);
        test(solution, new int[] { 1 }, 1);
        test(solution, new int[] { -1, -1, 2 }, 2);

        System.out.println("[PASS] " + Test.class.getPackage().getName());
    }
}