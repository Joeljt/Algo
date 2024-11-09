package src.f_queue.quiz;

import src.f_queue.Queue;

/**
 * 不浪费空间，但是需要主动维护当前队列 size 的大小，从而有效区分队列空和队列满
 */
public class LoopQueue3<E> implements Queue<E> {

  private E[] data;
  private int front, tail;
  private int size;

  public LoopQueue3(int capacity) {
    data = (E[])new Object[capacity];
    front = tail = size = 0;
  }

  public LoopQueue3() {
    this(10);
  }

  public int getCapacity() {
    return data.length;
  }

  public boolean isFull() {
    return size == getCapacity();
  }

  @Override
  public boolean isEmpty() {
    // 不主动浪费空间的前提下就不能用 tail == front 来判断数组空，
    // 也不能用 (tail + 1) % data.length == front 来判断数组满
    return size == 0;
  }

  @Override
  public int getSize() {
    return size;
  }

  @Override
  public E getFront() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    return data[front];
  }

  @Override
  public void enqueue(E e) {
    if (isFull()) {
      resize(data.length * 2);
    }
    data[tail] = e;
    tail = (tail + 1) % data.length;
    size ++;
  }

  @Override
  public E dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    E ret = data[front];
    data[front] = null;
    front = (front + 1) % data.length;
    size --;

    if (getSize() == data.length / 4 && data.length / 2 != 0) {
      resize(data.length / 2);
    }

    return ret;
  }

  private void resize(int newCapacity) {
    E[] newData = (E[])new Object[newCapacity];
    int size = getSize();
    for (int i = 0; i < size; i++) {
      newData[i] = data[(i + front) % data.length];
    }
    data = newData;
    front = 0;
    tail = size;
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();

    sb.append("Queue: front: [");
    for (int i = front; i != tail; i = (i + 1) % data.length) {
      sb.append(data[i]);
      if ((i + 1) % data.length != tail) {
        sb.append(", ");
      }
    }
    sb.append("] tail");
    return sb.toString();
  }

}
