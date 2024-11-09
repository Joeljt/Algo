package src.f_queue.quiz;

/**
 * 双端队列
 */
public class Deque<E> {

  private E[] data;
  private int front, tail;
  private int size;

  public Deque(int capacity) {
    data = (E[])new Object[capacity];
    front = tail = size = 0;
  }

  public Deque() {
    this(10);
  }

  public int getCapacity() {
    return data.length;
  }

  public boolean isFull() {
    return size == getCapacity();
  }

  public boolean isEmpty() {
    return size == 0;
  }

  public int getSize() {
    return size;
  }

  public E getFront() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    return data[front];
  }

  public E getLast() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    return data[(tail - 1 + data.length) % data.length];
  }

  public void addFront(E e) {
    if (isFull()) resize(data.length * 2);
    int targetIndex = (front - 1 + data.length) % data.length;
    data[targetIndex] = e;
    front = targetIndex;
    size ++;
  }

  public E removeLast() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    int currentIndex = ((tail - 1) + data.length) % data.length;
    E ret = data[currentIndex];
    data[currentIndex] = null;
    tail = currentIndex;
    size --;
    if (size == data.length / 4 && data.length / 2 != 0) {
      resize(data.length / 2);
    }
    return ret;
  }

  public void addLast(E e) {
    if (isFull()) resize(data.length * 2);
    data[tail] = e;
    tail = (tail + 1) % data.length;
    size ++;
  }

  public E removeFront() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    E ret = data[front];
    data[front] = null;
    front = (front + 1) % data.length;
    size --;
    if (size == data.length / 4 && data.length / 2 != 0) {
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
