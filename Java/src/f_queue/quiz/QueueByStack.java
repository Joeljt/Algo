package Java.src.f_queue.quiz;

import java.util.Stack;

import Java.src.f_queue.Queue;

public class QueueByStack<E> implements Queue<E> {

    private Stack<E> stackIn;
    private Stack<E> stackOut;

    public QueueByStack() {
        stackIn = new Stack<>();
        stackOut = new Stack<>();
    }

    @Override
    public boolean isEmpty() {
        return stackIn.isEmpty() && stackOut.isEmpty();
    }

    @Override
    public int getSize() {
        return stackIn.size() + stackOut.size();
    }

    @Override
    public void enqueue(E e) {
       stackIn.push(e); 
    }

    @Override
    public E getFront() {
        if (isEmpty()) {
            throw new RuntimeException("Queue is empty");
        }
        if (stackOut.isEmpty()) {
            while (!stackIn.isEmpty()) {
               stackOut.push(stackIn.pop()); 
            }
        }
        return stackOut.peek();
    }

    @Override
    public E dequeue() {
        if (isEmpty()) {
            throw new RuntimeException("Queue is empty");
        }
        if (stackOut.isEmpty()) {
            while (!stackIn.isEmpty()) {
               stackOut.push(stackIn.pop()); 
            }
        }
        return stackOut.pop();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("QueueByStack: front [");
        
        // 先添加 stackOut 的元素（从栈顶到栈底）
        for (int i = stackOut.size() - 1; i >= 0; i--) {
            sb.append(stackOut.get(i));
            if (i != 0 || !stackIn.isEmpty()) sb.append(", ");
        }
        
        // 再添加 stackIn 的元素（从栈底到栈顶）
        for (int i = 0; i < stackIn.size(); i++) {
            sb.append(stackIn.get(i));
            if (i != stackIn.size() - 1) sb.append(", ");
        }
        
        sb.append("] tail");
        return sb.toString();
    }
}
