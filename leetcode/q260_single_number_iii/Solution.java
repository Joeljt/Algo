package q260_single_number_iii;
/**
 * 260. Single Number III
 * 
 * https://leetcode.cn/problems/single-number-iii/
 */
public class Solution {
    public int[] singleNumber(int[] nums) {
        // 和 136 类似，把所有数字都依次异或，得到的结果是那两个唯一的值的异或结果
        int xor = 0;
        for (int num : nums) xor ^= num;

        // 根据异或的特性，不相等的两个元素
        // 必然有一个元素的二进制至少包含一个 1，而且另一个元素对应的是 0
        // 用 n & (-n) 取出最后一个 1
        // 然后让数组中的每个元素都和这最后一个 1 做 &，就可以把这两个唯一的值分为两个不同的组
        // 然后在组中重新做异或
        // 剩下的元素必然属于两组中的一个，在异或的过程中也会消失
        int lastOne = xor & (-xor);

        // 相较于声明 x 和 y 两个变量，只声明一个变量求出其中一个值就够了
        // 另一个值可以和之前两个元素的异或结果再求一次异或得到
        // 这样可以在省掉一半的循环以及异或开销
        int x = 0;
        for (int num : nums) {
            if ((lastOne & num) == 0) {
                x ^= num;
            }
        }
        return new int[]{x, x ^ xor};
    }
}