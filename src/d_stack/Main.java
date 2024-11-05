package src.d_stack;

public class Main {
    public static void main(String[] args) {
       ArrayStack<Integer> stack = new ArrayStack<>(); 

       for (int i = 0; i < 10; i++) {
        stack.push(i);
        System.out.println(stack);
        if (i % 3 == 0) {
            stack.pop();
            System.out.println(stack);
        }
       }

    }
}
