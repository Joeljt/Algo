package e136_single_number;

/**
 * 136. Single Number
 * 
 * https://leetcode.cn/problems/single-number
 * 
 * 1. 利用异或运算的特性：a ^ 0 = a, a ^ a = 0；
 * 2. res 从 0 开始，任何数和 0 做异或都等于其自身；
 * 3. 循环数组不停异或，任何数和自己做异或都等于 0；
 * 4. 遍历到最后就是唯一的那个数异或 0，结果就是自身，也就是期望的结果。
 */

 public class Solution {
  public int singleNumber(int[] nums) {
      int res = 0;
      for (int i = 0; i < nums.length; i++) {
          res ^= nums[i];
      }
      return res;
  }
}