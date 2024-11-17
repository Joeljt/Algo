package Java.src.e_stack.quiz;

import Java.src.e_stack.Stack;
import Java.src.f_queue.Queue;
import Java.src.f_queue.quiz.LoopQueue3;

public class StackByQueue<E> implements Stack<E> {
    
    private Queue<E> queue;
    
    public StackByQueue() {
        queue = new LoopQueue3<>();
    }
    
    @Override
    public int getSize() {
        return queue.getSize();
    }
    
    @Override
    public boolean isEmpty() {
        return queue.isEmpty();
    }
    
    @Override
    public void push(E e) {
        queue.enqueue(e);
    }
    
    @Override
    public E pop() {
        if (isEmpty()) {
            throw new RuntimeException("Stack is empty.");
        }
        
        // 将除了最后一个元素外的所有元素重新入队
        int size = getSize();
        for (int i = 0; i < size - 1; i++) {
            queue.enqueue(queue.dequeue());
        }
        
        // 返回最后一个元素
        return queue.dequeue();
    }
    
    @Override
    public E peek() {
        if (isEmpty()) {
            throw new RuntimeException("Stack is empty.");
        }
        
        // 将所有元素重新入队，并在过程中保存最后一个元素
        int size = getSize();
        for (int i = 0; i < size - 1; i++) {
            queue.enqueue(queue.dequeue());
        }
        
        // 保存最后一个元素
        E ret = queue.dequeue();
        // 将最后一个元素也重新入队
        queue.enqueue(ret);
        
        return ret;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("StackByQueue: [");
        
        // 保存当前状态
        int size = getSize();
        for (int i = 0; i < size; i++) {
            E e = queue.dequeue();
            sb.append(e);
            if (i != size - 1) {
                sb.append(", ");
            }
            queue.enqueue(e);
        }
        
        sb.append("] top");
        return sb.toString();
    }
}