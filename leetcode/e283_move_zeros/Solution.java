package e283_move_zeros;

public class Solution {
  public void moveZeroes(int[] nums) {
    for (int i = 1; i < nums.length; i++) {
      for (int j = i; j >= 1; j--) {
        if (nums[j - 1] == 0) {
          swap(nums, j, j - 1);
        }
      }
    }
  }

  private void swap(int[] nums, int a, int b) {
    int temp = nums[a];
    nums[a] = nums[b];
    nums[b] = temp;
  }
}
