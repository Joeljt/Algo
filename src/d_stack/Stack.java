package src.d_stack;

public interface Stack<E> {
    
    boolean isEmpty();
    int getSize();
    E peek();
    void push(E e);
    E pop();

}
