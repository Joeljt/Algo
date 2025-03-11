package e26_remove_duplicates_from_sorted_array;

public class Solution {
    public int removeDuplicates(int[] nums) {
        int slow = 0;
        for (int fast = 1; fast < nums.length; fast++) {
            // fast 指针完整遍历整个数组，过程中比对 slow 指针的指向
            // 给定的数组本身是有序的，只有 slow 和 fast 指向不同值的时候，说明遇到了一个不一样的值
            if (nums[fast] != nums[slow]) {
                // 维护指针
                slow = slow + 1;
                // 把遍历到的新值赋值到数组前面
                nums[slow] = nums[fast];
            }
        }
        // slow 是数组下表指向，即 len - 1，所以返回的时候需要 +1
        return slow + 1;
    }
}