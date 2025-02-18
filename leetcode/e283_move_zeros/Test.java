package e283_move_zeros;

public class Test {
    private static void test(Solution solution, int[] input, int[] expected) {
        solution.moveZeroes(input);
        for (int i = 0; i < input.length; i++) {
            assert input[i] == expected[i] : "failed";
        }
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        test(solution, new int[] { 0,1,0,3,12 }, new int[] { 1,3,12,0,0 });

        System.out.println("[PASS] " + Test.class.getPackage().getName());
    }
}