package e3340_check_balanced_string;


public class Test {
    private static void test(Solution solution) {
        assert solution.isBalanced("1234") == false : "failed";
        assert solution.isBalanced("24123") == true : "failed";
    }
    
    public static void main(String[] args) {
        Solution solution = new Solution();

        test(solution);

        System.out.println("[PASS] " + Test.class.getPackage().getName());
    }
}
