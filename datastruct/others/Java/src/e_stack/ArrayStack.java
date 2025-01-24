package others.Java.src.e_stack;

import others.Java.src.c_array.Array;

public class ArrayStack<E> implements Stack<E> {

    private Array<E> array;

    public ArrayStack(int capacity) {
        array = new Array<>(capacity);
    }

    public ArrayStack() {
        this(10);
    }

    @Override
    public int getSize() {
        return array.getSize();
    }

    public int getCapacity() {
        return array.getCapacity();
    }

    @Override
    public boolean isEmpty() {
        return array.isEmpty();
    }

    @Override
    public E peek() {
        return array.getLast();
    }

    @Override
    public void push(E e) {
       array.addLast(e); 
    }

    @Override
    public E pop() {
        return array.removeLast();
    } 

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("Stack: [");
        for (int i = 0; i < array.getSize(); i++) {
           builder.append(i);
           if (i != array.getSize() - 1) {
            builder.append(", ");
           } 
        }
        builder.append("] top");
        return builder.toString();
    }
    
}
