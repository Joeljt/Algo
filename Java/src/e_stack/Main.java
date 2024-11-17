package Java.src.e_stack;

import Java.src.e_stack.quiz.StackByQueue;

public class Main {
    public static void main(String[] args) {
       testStackByQueue();
    }

    private static void testArrayStack() {
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

    private static void testStackByQueue() {
        StackByQueue<Integer> stackByQueue = new StackByQueue<>();
        for (int i = 0; i < 10; i++) {
            stackByQueue.push(i);
            System.out.println(stackByQueue);
        }
        System.out.println(stackByQueue.pop());
        System.out.println(stackByQueue.peek());
    }

}
