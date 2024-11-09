package src.f_queue.quiz;

import src.f_queue.Queue;

/**
 * 不使用 size，但是浪费一个空间，用来区分空队列和满队列状态
 */
public class LoopQueue2<E> implements Queue<E> {

  private E[] data;
  private int front, tail;

  public LoopQueue2(int capacity) {
    data = (E[])new Object[capacity + 1];
    front = tail = 0;
  }

  public LoopQueue2() {
    this(10);
  }

  public int getCapacity() {
    return data.length;
  }

  public boolean isFull() {
    return (tail + 1) % data.length == front;
  }

  @Override
  public boolean isEmpty() {
    return front == tail;
  }

  @Override
  public int getSize() {
    if (tail > front) {
      return tail - front;
    }
    return data.length - front + tail;
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
  }

  @Override
  public E dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    E ret = data[front];
    data[front] = null;
    front = (front + 1) % data.length;

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
